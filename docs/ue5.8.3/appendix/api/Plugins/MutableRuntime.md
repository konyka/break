# Plugins / MutableRuntime

- module root: `Plugins/Mutable/Source/MutableRuntime`
- headers: 108; symbols: 4178
- symbol kinds: class=83, enum=48, enumerator=498, function=722, macro=47, member=971, namespace=345, prototype=1153, struct=218, typedef=78, union=8, variable=7
- PrivateDependencyModuleNames: GeometryCore, TraceLog
- PublicDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, Engine, ImageCore

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/BlockCompression/Miro/Miro.h` (Internal)


#### Free symbols / members of external scopes

- L12 _macro_ `#define MIRO_INCLUDE_BC 1`
- L17 _macro_ `#define MIRO_INCLUDE_ASTC 1`
- L22 _macro_ `#define MIRO_EXCLUDE_QUALITY_ABOVE 4`
- L26 _namespace_ `namespace miro`
- L37 _typedef_ `using FImageSize = UE::Math::TIntVector2<uint16>;` (scope `miro`)
- L39 _prototype_ `extern void initialize();` (scope `miro`)
- L40 _prototype_ `extern void finalize();` (scope `miro`)
- L45 _prototype_ `extern void RGB_to_BC1( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — BC1 support
- L46 _prototype_ `extern void RGBA_to_BC1( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L47 _prototype_ `extern void BC1_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L48 _prototype_ `extern void BC1_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L51 _prototype_ `extern void RGB_to_BC2( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — BC2 support
- L52 _prototype_ `extern void RGBA_to_BC2( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L53 _prototype_ `extern void BC2_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L54 _prototype_ `extern void BC2_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L57 _prototype_ `extern void RGB_to_BC3( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — BC3 support
- L58 _prototype_ `extern void RGBA_to_BC3( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L59 _prototype_ `extern void BC3_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L60 _prototype_ `extern void BC3_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L61 _prototype_ `extern void BC1_to_BC3( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L64 _prototype_ `extern void L_to_BC4( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — BC4 support
- L65 _prototype_ `extern void BC4_to_L( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L66 _prototype_ `extern void BC4_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L67 _prototype_ `extern void BC4_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L70 _prototype_ `extern void RGBA_to_BC5( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — BC5 support
- L71 _prototype_ `extern void RGB_to_BC5( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L72 _prototype_ `extern void BC5_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L73 _prototype_ `extern void BC5_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L81 _prototype_ `extern void RGBA_to_ASTC4x4RGBAL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`) — ASTC 4x4 support
- L82 _prototype_ `extern void RGB_to_ASTC4x4RGBAL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L83 _prototype_ `extern void ASTC4x4RGBAL_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L84 _prototype_ `extern void ASTC4x4RGBAL_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L86 _prototype_ `extern void RGB_to_ASTC4x4RGBL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L87 _prototype_ `extern void RGBA_to_ASTC4x4RGBL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L88 _prototype_ `extern void ASTC4x4RGBL_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L89 _prototype_ `extern void ASTC4x4RGBL_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L90 _prototype_ `extern void L_to_ASTC4x4RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L92 _prototype_ `extern void RGB_to_ASTC4x4RGL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L93 _prototype_ `extern void RGBA_to_ASTC4x4RGL( uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality );` (scope `miro`)
- L94 _prototype_ `extern void ASTC4x4RGL_to_RGB( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L95 _prototype_ `extern void ASTC4x4RGL_to_RGBA( uint32 sx, uint32 sy, const uint8* From, uint8* To );` (scope `miro`)
- L97 _prototype_ `extern void ASTC4x4RGBL_to_ASTC4x4RGBAL(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L98 _prototype_ `extern void ASTC4x4RGBAL_to_ASTC4x4RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L101 _prototype_ `extern void RGBA_to_ASTC6x6RGBAL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`) — ASTC 6x6 support
- L102 _prototype_ `extern void RGB_to_ASTC6x6RGBAL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L103 _prototype_ `extern void ASTC6x6RGBAL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L104 _prototype_ `extern void ASTC6x6RGBAL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L106 _prototype_ `extern void RGB_to_ASTC6x6RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L107 _prototype_ `extern void RGBA_to_ASTC6x6RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L108 _prototype_ `extern void ASTC6x6RGBL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L109 _prototype_ `extern void ASTC6x6RGBL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L111 _prototype_ `extern void RGB_to_ASTC6x6RGL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L112 _prototype_ `extern void RGBA_to_ASTC6x6RGL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L113 _prototype_ `extern void ASTC6x6RGL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L114 _prototype_ `extern void ASTC6x6RGL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L117 _prototype_ `extern void RGBA_to_ASTC8x8RGBAL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`) — ASTC 8x8 support
- L118 _prototype_ `extern void RGB_to_ASTC8x8RGBAL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L119 _prototype_ `extern void ASTC8x8RGBAL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L120 _prototype_ `extern void ASTC8x8RGBAL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L122 _prototype_ `extern void RGB_to_ASTC8x8RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L123 _prototype_ `extern void RGBA_to_ASTC8x8RGBL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L124 _prototype_ `extern void ASTC8x8RGBL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L125 _prototype_ `extern void ASTC8x8RGBL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L127 _prototype_ `extern void RGB_to_ASTC8x8RGL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L128 _prototype_ `extern void RGBA_to_ASTC8x8RGL(uint32 sx, uint32 sy, const uint8* From, uint8* To, int32 Quality);` (scope `miro`)
- L129 _prototype_ `extern void ASTC8x8RGL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L130 _prototype_ `extern void ASTC8x8RGL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L133 _prototype_ `extern void ASTC10x10RGBAL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`) — ASTC 10x10 support
- L134 _prototype_ `extern void ASTC10x10RGBAL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L135 _prototype_ `extern void ASTC10x10RGBL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L136 _prototype_ `extern void ASTC10x10RGBL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L137 _prototype_ `extern void ASTC10x10RGL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L138 _prototype_ `extern void ASTC10x10RGL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L141 _prototype_ `extern void ASTC12x12RGBAL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`) — ASTC 12x12 support
- L142 _prototype_ `extern void ASTC12x12RGBAL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L143 _prototype_ `extern void ASTC12x12RGBL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L144 _prototype_ `extern void ASTC12x12RGBL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L145 _prototype_ `extern void ASTC12x12RGL_to_RGB(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L146 _prototype_ `extern void ASTC12x12RGL_to_RGBA(uint32 sx, uint32 sy, const uint8* From, uint8* To);` (scope `miro`)
- L152 _namespace_ `namespace miro`
- L152 _namespace_ `namespace SubImageCompression` (scope `miro`)
- L154 _typedef_ `using FuncRefType = TFunctionRef<void(miro::FImageSize, miro::FImageSize, miro::FImageSize, const uint8*, uint8*, int32)>;` (scope `miro::SubImageCompression`)
- L157 _prototype_ `void RGB_To_BC3SubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L158 _prototype_ `void RGBA_To_BC3SubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L160 _prototype_ `void RGB_To_BC1SubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L161 _prototype_ `void RGBA_To_BC1SubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L163 _prototype_ `void RGB_To_BC2SubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L164 _prototype_ `void RGBA_To_BC2SubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L166 _prototype_ `void L_To_BC4SubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L168 _prototype_ `void RGB_To_BC5SubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L169 _prototype_ `void RGBA_To_BC5SubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L176 _prototype_ `void RGBA_To_ASTC4x4RGBALSubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`) — ASTC 4x4 support
- L177 _prototype_ `void RGB_To_ASTC4x4RGBALSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L179 _prototype_ `void RGB_To_ASTC4x4RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L180 _prototype_ `void RGBA_To_ASTC4x4RGBLSubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L181 _prototype_ `void L_To_ASTC4x4RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L182 _prototype_ `void RGB_To_ASTC4x4RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L183 _prototype_ `void RGBA_To_ASTC4x4RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L186 _prototype_ `void RGBA_To_ASTC6x6RGBALSubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`) — ASTC 6x6 support
- L187 _prototype_ `void RGB_To_ASTC6x6RGBALSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L188 _prototype_ `void RGB_To_ASTC6x6RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L189 _prototype_ `void RGBA_To_ASTC6x6RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L190 _prototype_ `void RGB_To_ASTC6x6RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L191 _prototype_ `void RGBA_To_ASTC6x6RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L194 _prototype_ `void RGBA_To_ASTC8x8RGBALSubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`) — ASTC 8x8 support
- L195 _prototype_ `void RGB_To_ASTC8x8RGBALSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L196 _prototype_ `void RGB_To_ASTC8x8RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L197 _prototype_ `void RGBA_To_ASTC8x8RGBLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L198 _prototype_ `void RGB_To_ASTC8x8RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L199 _prototype_ `void RGBA_To_ASTC8x8RGLSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To, int32 Quality);` (scope `miro::SubImageCompression`)
- L206 _namespace_ `namespace miro`
- L206 _namespace_ `namespace SubImageDecompression` (scope `miro`)
- L208 _typedef_ `using FuncRefType = TFunctionRef<void(miro::FImageSize, miro::FImageSize, miro::FImageSize, const uint8*, uint8*)>;` (scope `miro::SubImageDecompression`)
- L211 _prototype_ `void ASTC4x4RGBAL_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L212 _prototype_ `void ASTC4x4RGBAL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L213 _prototype_ `void ASTC4x4RGBL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L214 _prototype_ `void ASTC4x4RGBL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L215 _prototype_ `void ASTC4x4RGL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L216 _prototype_ `void ASTC4x4RGL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L218 _prototype_ `void ASTC6x6RGBAL_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L219 _prototype_ `void ASTC6x6RGBAL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L220 _prototype_ `void ASTC6x6RGBL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L221 _prototype_ `void ASTC6x6RGBL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L222 _prototype_ `void ASTC6x6RGL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L223 _prototype_ `void ASTC6x6RGL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L225 _prototype_ `void ASTC8x8RGBAL_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L226 _prototype_ `void ASTC8x8RGBAL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L227 _prototype_ `void ASTC8x8RGBL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L228 _prototype_ `void ASTC8x8RGBL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L229 _prototype_ `void ASTC8x8RGL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L230 _prototype_ `void ASTC8x8RGL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L232 _prototype_ `void ASTC10x10RGBAL_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L233 _prototype_ `void ASTC10x10RGBAL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L234 _prototype_ `void ASTC10x10RGBL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L235 _prototype_ `void ASTC10x10RGBL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L236 _prototype_ `void ASTC10x10RGL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L237 _prototype_ `void ASTC10x10RGL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L239 _prototype_ `void ASTC12x12RGBAL_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L240 _prototype_ `void ASTC12x12RGBAL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L241 _prototype_ `void ASTC12x12RGBL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L242 _prototype_ `void ASTC12x12RGBL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L243 _prototype_ `void ASTC12x12RGL_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L244 _prototype_ `void ASTC12x12RGL_To_RGBASubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L250 _prototype_ `void BC1_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L251 _prototype_ `void BC1_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L252 _prototype_ `void BC2_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L253 _prototype_ `void BC2_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L254 _prototype_ `void BC3_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L255 _prototype_ `void BC3_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L256 _prototype_ `void BC4_To_LSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L257 _prototype_ `void BC4_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L258 _prototype_ `void BC4_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L259 _prototype_ `void BC5_To_RGBASubImage(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)
- L260 _prototype_ `void BC5_To_RGBSubImage (FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* RESTRICT From, uint8* RESTRICT To);` (scope `miro::SubImageDecompression`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Cloth.h` (Internal)


#### class `UE::Mutable::Private::FCloth`  
`class FCloth : public FResource`  
_L17-39_
- inherits: `FResource`
- L20 _public prototype_ `FCloth() = default;`
- L22 _public prototype_ `FCloth(const FCloth& Other) = default;`
- L24 _public prototype_ `FCloth& operator=(const FCloth& Other) = default;`
- L26 _public prototype_ `bool operator==(const FCloth& Other) const;`
- L28 _public prototype_ `virtual int32 GetDataSize() const override;`
- L30 _public prototype_ `void Serialise(FOutputArchive& Ar) const;`
- L31 _public prototype_ `void Unserialise(FInputArchive& Ar);`
- L33 _public prototype_ `bool IsValid() const;`
- L35 _public member_ `int32 AssetLODIndex = -1;`
- L36 _public member_ `TArray<FMeshToMeshVertData, FDefaultMemoryTrackingAllocator<MemoryCounters::FMeshMemoryCounter>> Data;`
- L38 _public member_ `TPassthroughObjectPtr<UClothingAssetBase> ClothingAsset;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/CodeVisitor.h` (Internal)


#### class `UE::Mutable::Private::UniqueConstCodeVisitorIterative`  
`template<typename STATE=int32> class UniqueConstCodeVisitorIterative`  
_L24-179_
- desc: Code visitor that: - is top-down - cannot change the visited instructions. - will not visit twice the same instruction with the same state. - Its iterative
- L28 _public function_ `UniqueConstCodeVisitorIterative()`
- L36 _public prototype_ `virtual ~UniqueConstCodeVisitorIterative() = default;` — Ensure virtual destruction
- L41 _protected function_ `void SetDefaultState(const STATE& State)`
- L47 _protected function_ `const STATE& GetDefaultState() const`
- L54 _protected function_ `STATE GetCurrentState() const` — Use this from visit to access the state at the time of processing the current instruction.
- L60 _protected function_ `void RecurseWithState(FOperation::ADDRESS Address, const STATE& NewState)` — For manual recursion that changes the state for a specific path.
- L71 _protected function_ `void RecurseWithCurrentState(FOperation::ADDRESS Address)` — For manual recursion that doesn't change the state for a specific path.
- L77 _protected function_ `void SetCurrentState(const STATE& NewState)` — Can be called from visit to set the state to visit all children ops
- L87 _protected function_ `void Traverse(FOperation::ADDRESS Root, const FProgram& Program )`
- L95 _protected function_ `void FullTraverse(const FProgram& Program)`
- L111 _private prototype_ `virtual bool Visit(FOperation::ADDRESS, const FProgram&) = 0;` — Do the actual work by overriding this in the derived classes. Return true if the traverse has to continue with the children of the given address.
- L131 _private member_ `TArray<FPending> Pending;`
- L134 _private member_ `TArray<STATE> States;` — States found so far
- L137 _private member_ `int32 CurrentState;` — Index of the current state, from the States array.
- L141 _private member_ `TMap<FOperation::ADDRESS, TArray<int32>> Visited;` — Array of states visited for each operation. Empty array means operation not visited at all.
- L144 _private function_ `void Recurse(const FProgram& Program)` — Process all the pending operations and visit all children if necessary

#### struct `UE::Mutable::Private::UniqueConstCodeVisitorIterative::FPending`  
`struct FPending`  
_L114-130_
- desc: Operations to be processed
- L116 _public function_ `FPending()`
- L122 _public function_ `FPending(FOperation::ADDRESS InAddress, int32 InStateIndex)`
- L128 _public member_ `FOperation::ADDRESS Address=0;`
- L129 _public member_ `int32 StateIndex=0;`

#### struct `UE::Mutable::Private::COVERED_CODE_VISITOR_STATE`  
`struct COVERED_CODE_VISITOR_STATE`  
_L190-192_

#### class `UE::Mutable::Private::DiscreteCoveredCodeVisitorBase`  
`template<typename PARENT,typename STATE> class DiscreteCoveredCodeVisitorBase : public PARENT`  
_L195-355_
- inherits: `PARENT`
- L199 _public function_ `DiscreteCoveredCodeVisitorBase(FSystem* InSystem, const TSharedRef<FLiveInstance>& InLiveInstance) : LiveInstance(InLiveInstance)`
- L208 _public function_ `void Run( FOperation::ADDRESS at )`
- L217 _protected function_ `virtual bool Visit(FOperation::ADDRESS Address, const FProgram& Program)`
- L352 _protected member_ `FSystem* System = nullptr;`
- L353 _protected member_ `TSharedPtr<const FModel> Model;`
- L354 _protected member_ `TSharedRef<FLiveInstance> LiveInstance;`

#### class `UE::Mutable::Private::UniqueDiscreteCoveredCodeVisitor`  
`template<typename COVERED_STATE = COVERED_CODE_VISITOR_STATE> class UniqueDiscreteCoveredCodeVisitor : public DiscreteCoveredCodeVisitorBase<UniqueConstCodeVisitorIterative<COVERED_STATE>, COVERED_STATE>`  
_L368-383_
- inherits: `DiscreteCoveredCodeVisitorBase<UniqueConstCodeVisitorIterative<COVERED_STATE>,COVERED_STATE>`
- desc: Code visitor that : - only traverses the operations that are relevant for a given set of parameter values. It only considers the discrete parameters like integers and booleans. In the case of forks caused by continuous parameters like float weights for interpolation, all the branches are traversed. - cannot change the instructions - will not repeat visits to instructions with the same state - the state has to be a compatible with COVERED_CODE_VISITOR_STATE
- L370 _private typedef_ `using PARENT=DiscreteCoveredCodeVisitorBase<UniqueConstCodeVisitorIterative<COVERED_STATE>, COVERED_STATE>;`
- L374 _public function_ `UniqueDiscreteCoveredCodeVisitor ( FSystem* InSystem, const TSharedRef<FLiveInstance>& InLiveInstance ) : PARENT(InSystem, InLiveInstance)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L169 _function_ `` (scope `UE::Mutable::Private::UniqueConstCodeVisitorIterative::Recurse`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ComponentId.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L10 _typedef_ `using FComponentId = int32;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ConvertData.h` (Internal)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L17 _function_ `inline void ConvertData ( int channel, void* pResult, EMeshBufferFormat resultFormat, const void* pSource, EMeshBufferFormat sourceFormat )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ExtensionData.h` (Internal)


#### class `UE::Mutable::Private::FExtensionData`  
`class FExtensionData`  
_L20-24_
- desc: ExtensionData represents data types that Mutable doesn't support natively. Extensions can provide data, and functionality to operate on that data, without Mutable needing to know what the data refers to.
- L23 _public member_ `TPassthroughObjectPtr<UObject> PassthroughObject;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ExternalOperationProvider.h` (Internal)


#### class `UE::Mutable::Private::IExternalOperationProvider`  
`class IExternalOperationProvider`  
_L11-17_
- L14 _public prototype_ `virtual ~IExternalOperationProvider() = default;`
- L16 _public prototype_ `virtual const FInstancedStruct& Get(FOperation::ADDRESS Address) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Image.h` (Internal)


#### class `UE::Mutable::Private::FImage`  
`class FImage : public FResource`  
_L30-246_
- inherits: `FResource`
- desc: 2D image resource with mipmaps.
- L38 _public prototype_ `FImage();`
- L48 _public prototype_ `FImage(uint32 SizeX, uint32 SizeY, uint32 Lods, EImageFormat Format, EInitializationType InitType);` — Constructor from the size and format. It will allocate the memory for the image, but its content will be undefined. \param sizeX Width of the image. \param sizeY Height of the image. \param lods Number of levels of detail (mipmaps) to include in the image, inclduing the base level. It must be a number between 1 and the maximum possible levels, which depends on the image size. \param format Pixel format.
- L51 _public prototype_ `static TManagedRef<FImage> CreateAsReference(const TPassthroughObjectPtr<UTexture>& ExternalObject, const FImageDesc& Desc, bool bForceLoad);` — Create a new empty image that repreents an external resource image.
- L54 _public prototype_ `static void Serialise( const FImage*, FOutputArchive& );` — Serialisation
- L55 _public prototype_ `static TManagedRef<FImage> StaticUnserialise( FInputArchive& );`
- L58 _public prototype_ `int32 GetDataSize() const override;` — Resource interface
- L65 _public prototype_ `void Init(uint32 SizeX, uint32 SizeY, uint32 Lods, EImageFormat Format, EInitializationType InitType);`
- L68 _public prototype_ `void InitToBlack();` — Clear the image to black color.
- L71 _public prototype_ `bool IsReference() const;` — Return true if this is a reference to an engine image.
- L74 _public prototype_ `bool IsForceLoad() const;` — If true, this is a reference that must be resolved at compile time.
- L77 _public prototype_ `uint16 GetSizeX() const;` — Return the width of the image.
- L80 _public prototype_ `uint16 GetSizeY() const;` — Return the height of the image.
- L82 _public prototype_ `const FImageSize& GetSize() const;`
- L85 _public prototype_ `EImageFormat GetFormat() const;` — Return the pixel format of the image.
- L89 _public prototype_ `int32 GetLODCount() const;` — Return the number of levels of detail (mipmaps) in the texture. The base lavel is also counted, so the minimum is 1.
- L92 _public prototype_ `const uint8* GetLODData(int32 LODIndex) const;` — Return a pointer to a instance-owned buffer where the image pixels are.
- L93 _public prototype_ `uint8* GetLODData(int32 LODIndex);`
- L96 _public prototype_ `int32 GetLODDataSize(int32 LODIndex) const;` — Return the size in bytes of a specific LOD of the image.
- L119 _public typedef_ `} EImageFlags;`
- L122 _public member_ `mutable uint8 Flags = 0;` — Persistent flags with some image properties. The meaning will depend of every context.
- L125 _public member_ `uint16 RelevancyMinY = 0;` — Non-persistent relevancy map.
- L126 _public member_ `uint16 RelevancyMaxY = 0;`
- L129 _public member_ `TPassthroughObjectPtr<UTexture> PassthroughObject;` — Passthrough Id or TStrongObjectPtr.
- L133 _public member_ `FImageDataStorage DataStorage;` — Pixel data for all lods.
- L139 _public function_ `TManagedPtr<FImage> Clone() const` — Deep clone.
- L156 _public function_ `void Copy(const FImage* Other)` — Copy another image.
- L173 _public function_ `void CopyMove(FImage* Other)`
- L193 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L196 _public prototype_ `void Unserialise(FInputArchive&);`
- L199 _public function_ `inline bool operator==(const FImage& Other) const`
- L209 _public prototype_ `FVector4f Sample(FVector2f Coords) const;` — Sample the image and return an RGB color.
- L214 _public prototype_ `static int32 CalculateDataSize(int32 SizeX, int32 SizeY, int32 LodCount, EImageFormat Format);` — Calculate the size of the image data in bytes, regardless of what is allocated in m_data, only using the image descriptions. For non-block-compressed images, it returns 0.
- L218 _public prototype_ `FIntVector2 CalculateMipSize(int32 LOD) const;` — Calculate the size in pixels of a particular mipmap of this image. The size doesn't include pixels necessary for completing blocks in block-compressed formats.
- L221 _public prototype_ `uint8* GetMipData(int32 Mip);` — Return a pointer to the beginning of the data for a particular mip.
- L222 _public prototype_ `const uint8* GetMipData(int32 Mip) const;`
- L226 _public prototype_ `int32 GetMipsDataSize() const;` — Return the size of the resident mips. for block-compressed images the result is the same as in CalculateDataSize() for non-block-compressed images, the sizes encoded in the image data is used to compute the final size.
- L229 _public prototype_ `bool IsPlainColor(FVector4f& Color) const;` — See if all the pixels in the image are equal and return the color.
- L233 _public prototype_ `bool IsFullAlpha() const;` — See if all the pixels in the alpha channel are the max value of the pixel format (white).
- L237 _public prototype_ `void ReduceLODsTo(int32 NewLODCount);` — Reduce the LODs of the image to the given amount. Don't do anything if there are already less LODs than specified.
- L238 _public prototype_ `void ReduceLODs(int32 LODsToSkip);`
- L241 _public prototype_ `static int32 GetMipmapCount(int32 SizeX, int32 SizeY);` — Calculate the number of mipmaps for a particular image size.
- L244 _public prototype_ `void GetNonBlackRect(FImageRect& OutRect) const;` — Get the rect inside the image bounding the non-black content of the image.
- L245 _public prototype_ `void GetNonBlackRect_Reference(FImageRect& OutRect) const;`

#### enum `UE::Mutable::Private::FImage::(anonymous)`  
``  
_L104-119_

#### struct `UE::Mutable::Private::FImageOperator`  
`struct FImageOperator`  
_L251-339_
- desc: This struct contains image operations that may need to allocate and free temporary images to work. It's purpose is to override the creation, release and clone functions depending on the context.
- L254 _public typedef_ `typedef TFunction<TManagedPtr<FImage>(int32, int32, int32, EImageFormat, EInitializationType)> FImageCreateFunc;` — Common callback used for functions that can create temporary images.
- L255 _public typedef_ `typedef TFunction<TManagedPtr<FImage>(const FImage*)> FImageCloneFunc;`
- L257 _public member_ `FImageCreateFunc CreateImage;`
- L258 _public member_ `FImageCloneFunc CloneImage;`
- L263 _public typedef_ `typedef TFunction<void(bool&, int32, FImage*, const FImage*, int32)> FImagePixelFormatFunc;` — Interface to override the internal mutable image pixel format conversion functions. Arguments match the FImageOperator::ImagePixelFormat function.
- L264 _public member_ `FImagePixelFormatFunc FormatImageOverride;`
- L266 _public function_ `FImageOperator(FImageCreateFunc Create, FImageCloneFunc Clone, FImagePixelFormatFunc FormatOverride) : CreateImage(Create) , CloneImage(Clone) , FormatImageOverride(FormatOverride)`
- L274 _public function_ `static FImageOperator GetDefault( const FImagePixelFormatFunc& InFormatOverride )` — Create an default version for untracked resources.
- L289 _public prototype_ `TManagedPtr<FImage> ImagePixelFormat(int32 Quality, const FImage* Base, EImageFormat TargetFormat, int32 OnlyLOD = -1);` — Convert an image to another pixel format. Allocates the destination image. \warning Not all format conversions are implemented. \param onlyLOD If different than -1, only the specified lod level will be converted in the returned image. \return nullptr if the conversion failed, usually because not enough memory was allocated in the result. This is only checked for RLE compression.
- L296 _public prototype_ `void ImagePixelFormat(bool& bOutSuccess, int32 Quality, FImage* Result, const FImage* Base, int32 OnlyLOD = -1);` — Convert an image to another pixel format. \warning Not all format conversions are implemented. \param onlyLOD If different than -1, only the specified lod level will be converted in the returned image. \return false if the conversion failed, usually because not enough memory was allocated in the result. This is only checked for RLE compression.
- L297 _public prototype_ `void ImagePixelFormat(bool& bOutSuccess, int32 Quality, FImage* Result, const FImage* Base, int32 BeginResultLOD, int32 BeginBaseLOD, int32 NumLODs);`
- L299 _public prototype_ `TManagedPtr<FImage> ImageSwizzle(EImageFormat Format, const TManagedPtr<const FImage> Sources[], const uint8 Channels[]);`
- L302 _public prototype_ `TManagedPtr<FImage> ExtractMip(const FImage* From, int32 Mip);`
- L305 _public prototype_ `void ImageResizeLinear(FImage* Dest, int32 ImageCompressionQuality, const FImage* Base);` — Bilinear filter image resize.
- L308 _public prototype_ `void FillColor(FImage* Image, FVector4f Color);` — Fill the image with a plain color.
- L323 _public prototype_ `void ImageMipmap(int32 CompressionQuality, FImage* Dest, const FImage* Base, int32 StartLevel, int32 LevelCount, const FMipmapGenerationSettings&, bool bGenerateOnlyTail = false);` — Generate the mipmaps for images. if bGenerateOnlyTail is true, generates the mips missing from Base to LevelCount and sets them in Dest (the full chain is spit in two images). Otherwise generate the mips missing from Base up to LevelCount and append them in Dest to the already generated Base's mips.
- L328 _public prototype_ `void ImageMipmap_PrepareScratch(const FImage* DestImage, int32 StartLevel, int32 LevelCount, FScratchImageMipmap&);` — Mipmap separating the worst case treatment in 3 steps to manage allocations of temp data.
- L329 _public prototype_ `void ImageMipmap(FImageOperator::FScratchImageMipmap&, int32 CompressionQuality, FImage* Dest, const FImage* Base, int32 LevelStart, int32 LevelCount, const FMipmapGenerationSettings&, bool bGenerateOnlyTail = false);`
- L334 _public prototype_ `bool ImageCrop(TManagedPtr<FImage>& OutCropped, int32 CompressionQuality, const FImage* Base, const box<FIntVector2>& Rect);`
- L337 _public prototype_ `void ImageCompose(FImage* Base, const FImage* Block, const box<FIntVector2>& Rect);`

#### struct `UE::Mutable::Private::FImageOperator::FScratchImageMipmap`  
`struct FScratchImageMipmap`  
_L311-316_
- desc: Support struct to keep preallocated data required for some mipmap operations.
- L313 _public member_ `TManagedPtr<FImage> Uncompressed;`
- L314 _public member_ `TManagedPtr<FImage> UncompressedMips;`
- L315 _public member_ `TManagedPtr<FImage> CompressedMips;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Mutable` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L106 _enumerator_ `IF_IS_PLAIN_COLOR_VALID = 1 << 0` (scope `UE::Mutable::Private::FImage::__anone741bd250103`) — Set if the next flag has been calculated and its value is valid.
- L109 _enumerator_ `IF_IS_PLAIN_COLOR = 1 << 1` (scope `UE::Mutable::Private::FImage::__anone741bd250103`) — If the previous flag is set and this one too, the image is single color.
- L112 _enumerator_ `IF_CANNOT_BE_SCALED = 1 << 2` (scope `UE::Mutable::Private::FImage::__anone741bd250103`) — If this is set, the image shouldn't be scaled: it's contents is resolution-dependent.
- L115 _enumerator_ `IF_HAS_RELEVANCY_MAP = 1 << 3` (scope `UE::Mutable::Private::FImage::__anone741bd250103`) — If this is set, the image has an updated relevancy map. This flag is not persistent.
- L118 _enumerator_ `IF_IS_FORCELOAD = 1 << 5` (scope `UE::Mutable::Private::FImage::__anone741bd250103`) — For reference images, this indicates that they should be loaded into full images as soon as they are generated.
- L277 _function_ `[](int32 SizeX, int32 SizeY, int32 NumLODs, EImageFormat Format, EInitializationType InitType)` (scope `UE::Mutable::Private::FImageOperator::GetDefault`)
- L344 _prototype_ `void ImageMipmapInPlace(int32 CompressionQuality, FImage* Base, const FMipmapGenerationSettings&);` (scope `UE::Mutable::Private`) — Update all the mipmaps in the image from the data in the base one. Only the mipmaps already existing in the image are updated.
- L347 _prototype_ `void ImageSwizzle(FImage* Result, const TManagedPtr<const FImage> Sources[], const uint8 Channels[]);` (scope `UE::Mutable::Private`)
- L349 _function_ `inline EImageFormat GetUncompressedFormat(EImageFormat Format)` (scope `UE::Mutable::Private`)
- L389 _function_ `template<class T> TManagedPtr<T> CloneOrTakeOver(TManagedPtr<T>&& Source)` (scope `UE::Mutable::Private`)
- L410 _function_ `template<class T> TManagedPtr<T> CloneOrTakeOver(TManagedPtr<const T>&& Source)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ImageDataStorage.h` (Internal)


#### struct `UE::Mutable::Private::MemoryCounters::FImageMemoryCounter`  
`struct FImageMemoryCounter`  
_L18-21_
- L20 _public prototype_ `static std::atomic<SSIZE_T>& Get();`

#### class `UE::Mutable::Private::FImageDataStorage`  
`class FImageDataStorage`  
_L40-207_
- L43 _public member_ `TArray<FImageArray, TInlineAllocator<1>> Buffers;`
- L45 _public member_ `FImageSize ImageSize = FImageSize(0, 0);`
- L46 _public member_ `EImageFormat ImageFormat = EImageFormat::None;`
- L47 _public member_ `uint8 NumLODs = 0;`
- L49 _public member_ `static constexpr int32 NumLODsInCompactedTail = 7;`
- L53 _public member_ `TStaticArray<uint16, NumLODsInCompactedTail> CompactedTailOffsets = MakeUniformStaticArray<uint16, NumLODsInCompactedTail>(0);` — This is needed for images its size cannot be known from dimensions and format, e.g., RLE compressed formats. It stores the offset to the end of the LOD so that CompactedTailOffsets[LOD] - CompactedTailOffsets[LOD - 1] is the size of LOD.
- L57 _public prototype_ `FImageDataStorage();`
- L58 _public prototype_ `FImageDataStorage(const FImageDesc& Desc);`
- L60 _public prototype_ `FImageDataStorage(const FImageDataStorage& Other);`
- L61 _public prototype_ `FImageDataStorage& operator=(const FImageDataStorage& Other);`
- L63 _public prototype_ `FImageDataStorage(FImageDataStorage&& Other) = default;`
- L64 _public prototype_ `FImageDataStorage& operator=(FImageDataStorage&& Other) = default;`
- L66 _public prototype_ `bool operator==(const FImageDataStorage& Other) const;`
- L68 _public function_ `inline FImageDesc MakeImageDesc() const`
- L73 _public function_ `inline void InitVoid(const FImageDesc& Desc)`
- L83 _public function_ `inline bool IsVoid() const`
- L88 _public prototype_ `void InitInternalArray(int32 Index, int32 Size, EInitializationType InitType);`
- L89 _public prototype_ `void Init(const FImageDesc& ImageDesc, EInitializationType InitType);`
- L91 _public prototype_ `void CopyFrom(const FImageDataStorage& Other);`
- L93 _public function_ `inline int32 GetNumLODs() const`
- L101 _public prototype_ `TArrayView<const uint8> GetLOD(int32 LODIndex) const;` — Get a const view to the data containing the LODIndex.
- L106 _public prototype_ `TArrayView<uint8> GetLOD(int32 LODIndex);` — Get a view to the data containing the LODIndex.
- L112 _public prototype_ `void SetNumLODs(int32 InNumLODs, EInitializationType InitType = EInitializationType::NotInitialized);` — Change the number of lods in the image. If InNumLODs is smaller than the current lod count, LODs are dropped from the tail up.
- L117 _public prototype_ `void DropLODs(int32 NumLODsToDrop);` — Remove NumLODsToDrop starting form LOD 0. The resulting image will be smaller.
- L122 _public prototype_ `void ResizeLOD(int32 LODIndex, int32 NewSizeBytes, EAllowShrinking AllowShrinking = EAllowShrinking::Default);` — Resizes LODIndex Data to NewSizeBytes
- L124 _public function_ `inline const FImageArray& GetInternalArray(int32 LODIndex) const`
- L131 _public function_ `inline FImageArray& GetInternalArray(int32 LODIndex)`
- L138 _public function_ `inline int32 ComputeFirstCompactedTailLOD() const`
- L147 _public prototype_ `int32 GetNumBatches(int32 BatchSizeInElems, int32 BatchElemSizeInBytes) const;` — Stateless iteration in batches.
- L148 _public prototype_ `TArrayView<const uint8> GetBatch(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes) const;`
- L149 _public prototype_ `TArrayView<uint8> GetBatch(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes);`
- L159 _public prototype_ `int32 GetNumBatchesFirstLODOffset(int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 OffsetInBytes) const;` — Returns the number of batches GetBatchFirtsLODOffet will admit and that will cover the first LOD buffer with OffsetInBytes removed from the front. A batch cannot be larger than BatchElemsSize. The last batch of a buffer will be smaller if BatchSizeInElems*BatchElemSizeInBytes is not multiple of the buffer size.
- L168 _public prototype_ `TArrayView<const uint8> GetBatchFirstLODOffset(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 OffsetInBytes) const;` — Returns a non modifiable view to the portion of the first LOD buffer with OffsetInBytes for the BatchId A batch cannot be larger than BatchElemsSize. The last batch of a buffer will be smaller if BatchSizeInElems*BatchElemSizeInBytes is not multiple of the buffer size.
- L173 _public prototype_ `TArrayView<uint8> GetBatchFirstLODOffset(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 OffsetInBytes = 0);` — Non const version of GetBatchFirstLODOffset().
- L180 _public prototype_ `int32 GetNumBatchesLODRange(int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 LODBegin, int32 LODEnd) const;` — Returns the number of batches GetBatchLODRange will admit and that will cover the [LODBegin, LODEnd) range.
- L189 _public prototype_ `TArrayView<const uint8> GetBatchLODRange(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 LODBegin, int32 LODEnd) const;` — Returns a non modifiable view to the portion of the [LODBegin, LODEnd) for the BatchId. A batch cannot be larger than BatchElemsSize. The last batch of a buffer will be smaller if BatchSizeInElems*BatchElemSizeInBytes is not multiple of the buffer size.
- L194 _public prototype_ `TArrayView<uint8> GetBatchLODRange(int32 BatchId, int32 BatchSizeInElems, int32 BatchElemSizeInBytes, int32 LODBegin, int32 LODEnd);` — Non const version of GetBatchLODRange().
- L196 _public prototype_ `int32 GetAllocatedSize() const;`
- L197 _public prototype_ `int32 GetDataSize() const;`
- L203 _public prototype_ `bool IsEmpty() const;` — Returns true if all buffers are empty. This can be true after initialization for image formats that report BytesPerBlock 0, e.g., RLE formats. If not initialized will also return true.
- L205 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L206 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _namespace_ `namespace MemoryCounters` (scope `UE::Mutable::Private`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Mutable` (scope `UE`)
- L25 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L27 _typedef_ `using FImageArray = TArray<uint8, FDefaultMemoryTrackingAllocator<MemoryCounters::FImageMemoryCounter>>;` (scope `UE::Mutable::Private`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Mutable` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L30 _namespace_ `namespace FImageDataStorageInternal` (scope `UE::Mutable::Private`)
- L32 _function_ `inline int32 ComputeNumLODsForSize(FImageSize Size)` (scope `UE::Mutable::Private::FImageDataStorageInternal`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Mutable` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ImagePrivate.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L10 _function_ `inline EImageFormat GetMostGenericFormat(EImageFormat FormatA, EImageFormat FormatB)` (scope `UE::Mutable::Private`)
- L53 _function_ `inline EImageFormat GetRGBOrRGBAFormat(EImageFormat InFormat)` (scope `UE::Mutable::Private`)
- L86 _function_ `inline bool IsCompressedFormat(EImageFormat Format)` (scope `UE::Mutable::Private`)
- L92 _function_ `inline bool IsBlockCompressedFormat(EImageFormat Format)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ImageTypes.h` (Internal)


#### enum `UE::Mutable::Private::EImageFormat`  
`enum class EImageFormat : uint8`  
_L20-71_
- desc: Pixel formats supported by the images. \ingroup runtime
- L22 _public enumerator_ `None`
- L23 _public enumerator_ `RGB_UByte`
- L24 _public enumerator_ `RGBA_UByte`
- L25 _public enumerator_ `L_UByte`
- L28 _public enumerator_ `_DEPRECATED_1` — Deprecated formats
- L29 _public enumerator_ `_DEPRECATED_2`
- L30 _public enumerator_ `_DEPRECATED_3`
- L31 _public enumerator_ `_DEPRECATED_4`
- L33 _public enumerator_ `L_UByteRLE`
- L34 _public enumerator_ `RGB_UByteRLE`
- L35 _public enumerator_ `RGBA_UByteRLE`
- L36 _public enumerator_ `L_UBitRLE`
- L39 _public enumerator_ `BC1` — Common S3TC formats
- L40 _public enumerator_ `BC2`
- L41 _public enumerator_ `BC3`
- L42 _public enumerator_ `BC4`
- L43 _public enumerator_ `BC5`
- L46 _public enumerator_ `BC6` — Not really supported yet
- L47 _public enumerator_ `BC7`
- L50 _public enumerator_ `BGRA_UByte` — Swizzled versions, engineers be damned.
- L53 _public enumerator_ `ASTC_4x4_RGB_LDR` — The new standard
- L54 _public enumerator_ `ASTC_4x4_RGBA_LDR`
- L55 _public enumerator_ `ASTC_4x4_RG_LDR`
- L57 _public enumerator_ `ASTC_8x8_RGB_LDR`
- L58 _public enumerator_ `ASTC_8x8_RGBA_LDR`
- L59 _public enumerator_ `ASTC_8x8_RG_LDR`
- L60 _public enumerator_ `ASTC_12x12_RGB_LDR`
- L61 _public enumerator_ `ASTC_12x12_RGBA_LDR`
- L62 _public enumerator_ `ASTC_12x12_RG_LDR`
- L63 _public enumerator_ `ASTC_6x6_RGB_LDR`
- L64 _public enumerator_ `ASTC_6x6_RGBA_LDR`
- L65 _public enumerator_ `ASTC_6x6_RG_LDR`
- L66 _public enumerator_ `ASTC_10x10_RGB_LDR`
- L67 _public enumerator_ `ASTC_10x10_RGBA_LDR`
- L68 _public enumerator_ `ASTC_10x10_RG_LDR`
- L70 _public enumerator_ `Count`

#### struct `UE::Mutable::Private::FImageDesc`  
`struct FImageDesc`  
_L79-124_
- L81 _public function_ `FImageDesc()`
- L85 _public function_ `FImageDesc(const FImageSize& InSize, EImageFormat InFormat, EImageFormat InFormatIfAlpha, uint8 InLods) : m_size(InSize) , m_format(InFormat) , FormatIfAlpha(InFormatIfAlpha) , m_lods(InLods)`
- L94 _public member_ `FImageSize m_size = FImageSize(0, 0);`
- L97 _public member_ `EImageFormat m_format = EImageFormat::None;`
- L100 _public member_ `EImageFormat FormatIfAlpha = EImageFormat::None;`
- L103 _public member_ `uint8 m_lods = 0;` — Levels of detail (mipmaps)
- L106 _public function_ `inline bool operator==(const FImageDesc& Other) const`

#### struct `UE::Mutable::Private::FExtendedImageDesc`  
`struct FExtendedImageDesc : public FImageDesc`  
_L127-135_
- inherits: `FImageDesc`
- desc: An image descriptor with information about missing data LODs and which images are needed to load to generate the image
- L133 _public member_ `uint8 FirstLODAvailable = 0;` — Number of LODs that cannot be generated because the data is not available. It is assumed that non available LODs are consecutive starting from the mip with higher resolution.
- L134 _public member_ `TArray<int32> ConstantImagesNeededToGenerate;`

#### enum `UE::Mutable::Private::EBlendType`  
`enum class EBlendType`  
_L138-152_
- desc: List of supported modes in generic image layering operations.
- L140 _public enumerator_ `BT_NONE = 0`
- L141 _public enumerator_ `BT_SOFTLIGHT`
- L142 _public enumerator_ `BT_HARDLIGHT`
- L143 _public enumerator_ `BT_BURN`
- L144 _public enumerator_ `BT_DODGE`
- L145 _public enumerator_ `BT_SCREEN`
- L146 _public enumerator_ `BT_OVERLAY`
- L147 _public enumerator_ `BT_BLEND`
- L148 _public enumerator_ `BT_MULTIPLY`
- L149 _public enumerator_ `BT_LIGHTEN` — Increase the channel value by a given proportion of what is missing from white
- L150 _public enumerator_ `BT_NORMAL_COMBINE`
- L151 _public enumerator_ `_BT_COUNT`

#### enum `UE::Mutable::Private::EAddressMode`  
`enum class EAddressMode`  
_L155-161_
- L157 _public enumerator_ `None`
- L158 _public enumerator_ `Wrap`
- L159 _public enumerator_ `ClampToEdge`
- L160 _public enumerator_ `ClampToBlack`

#### enum `UE::Mutable::Private::EMipmapFilterType`  
`enum class EMipmapFilterType`  
_L169-173_
- L171 _public enumerator_ `Unfiltered`
- L172 _public enumerator_ `SimpleAverage`

#### enum `UE::Mutable::Private::ECompositeImageMode`  
`enum class ECompositeImageMode`  
_L176-184_
- L178 _public enumerator_ `CIM_Disabled`
- L179 _public enumerator_ `CIM_NormalRoughnessToRed`
- L180 _public enumerator_ `CIM_NormalRoughnessToGreen`
- L181 _public enumerator_ `CIM_NormalRoughnessToBlue`
- L182 _public enumerator_ `CIM_NormalRoughnessToAlpha`
- L183 _public enumerator_ `_CIM_COUNT`

#### enum `UE::Mutable::Private::ESamplingMethod`  
`enum class ESamplingMethod : uint8`  
_L187-192_
- L189 _public enumerator_ `Point = 0`
- L190 _public enumerator_ `BiLinear`
- L191 _public enumerator_ `MaxValue`

#### enum `UE::Mutable::Private::EInitializationType`  
`enum class EInitializationType`  
_L196-200_
- L198 _public enumerator_ `NotInitialized`
- L199 _public enumerator_ `Black`

#### enum `UE::Mutable::Private::EMinFilterMethod`  
`enum class EMinFilterMethod : uint8`  
_L202-207_
- L204 _public enumerator_ `None = 0`
- L205 _public enumerator_ `TotalAreaHeuristic`
- L206 _public enumerator_ `MaxValue`

#### struct `UE::Mutable::Private::FImageFormatData`  
`struct FImageFormatData`  
_L212-259_
- L214 _public member_ `static constexpr SIZE_T MAX_BYTES_PER_BLOCK = 16;`
- L216 _public function_ `FImageFormatData ( uint8 InPixelsPerBlockX = 0, uint8 InPixelsPerBlockY = 0, uint16 InBytesPerBlock = 0, uint16 InChannels = 0 )`
- L230 _public function_ `FImageFormatData ( uint8 InPixelsPerBlockX, uint8 InPixelsPerBlockY, uint16 InBytesPerBlock, uint16 InChannels, std::initializer_list<uint8> BlackBlockInit ) : FImageFormatData(InPixelsPerBlockX, InPixelsPerBlockY, InBytesPerBlock, InChannels)`
- L247 _public member_ `uint8 PixelsPerBlockX, PixelsPerBlockY;` — For block based formats, size of the block size.For uncompressed formats it will always be 1,1. For non-block-based compressed formats, it will be 0,0.
- L247 _public member_ `uint8 PixelsPerBlockX, PixelsPerBlockY;` — For block based formats, size of the block size.For uncompressed formats it will always be 1,1. For non-block-based compressed formats, it will be 0,0.
- L252 _public member_ `uint16 BytesPerBlock;` — Number of bytes used by every pixel block, if uncompressed or block-compressed format. For non-block-compressed formats, it returns 0.
- L255 _public member_ `uint16 Channels;` — Channels in every pixel of the image.
- L258 _public member_ `uint8 BlackBlock[MAX_BYTES_PER_BLOCK] = { 0 };` — Representation of a black block of the image.

#### struct `UE::Mutable::Private::FMipmapGenerationSettings`  
`struct FMipmapGenerationSettings`  
_L263-270_
- L265 _public member_ `EMipmapFilterType FilterType = EMipmapFilterType::SimpleAverage;`
- L266 _public member_ `EAddressMode AddressMode = EAddressMode::None;`
- L268 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L269 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _typedef_ `using FImageSize = UE::Math::TIntVector2<uint16>;` (scope `UE::Mutable::Private`)
- L16 _typedef_ `using FImageRect = box<FImageSize>;` (scope `UE::Mutable::Private`)
- L72 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EImageFormat);` (scope `UE::Mutable::Private`)
- L74 _function_ `inline uint32 GetTypeHash(const EImageFormat& Format)` (scope `UE::Mutable::Private`)
- L115 _function_ `friend inline uint32 GetTypeHash(const FImageDesc& Desc)` (scope `UE::Mutable::Private`)
- L153 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EBlendType);` (scope `UE::Mutable::Private`)
- L162 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EAddressMode);` (scope `UE::Mutable::Private`)
- L164 _function_ `inline uint32 GetTypeHash(const EAddressMode& Mode)` (scope `UE::Mutable::Private`)
- L174 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EMipmapFilterType);` (scope `UE::Mutable::Private`)
- L185 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(ECompositeImageMode);` (scope `UE::Mutable::Private`)
- L193 _prototype_ `static_assert(uint32(ESamplingMethod::MaxValue) <= (1 << 3), "ESa` (scope `UE::Mutable::Private`)
- L194 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(ESamplingMethod);` (scope `UE::Mutable::Private`)
- L208 _prototype_ `static_assert(uint32(EMinFilterMethod::MaxValue) <= (1 << 3), "EMi` (scope `UE::Mutable::Private`)
- L209 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EMinFilterMethod);` (scope `UE::Mutable::Private`)
- L261 _prototype_ `const FImageFormatData& GetImageFormatData(EImageFormat format);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Instance.h` (Internal)


#### struct `UE::Mutable::Private::FOverrideMaterial`  
`struct FOverrideMaterial`  
_L20-24_
- L22 _public member_ `FName SlotName;`
- L23 _public member_ `FMaterialId MaterialId;`

#### struct `UE::Mutable::Private::FOverlayMaterial`  
`struct FOverlayMaterial`  
_L26-30_
- L28 _public member_ `FName SlotName;`
- L29 _public member_ `FMaterialId MaterialId;`

#### struct `UE::Mutable::Private::FInstanceComponent`  
`struct FInstanceComponent`  
_L32-43_
- L34 _public member_ `FComponentId Id = INDEX_NONE;`
- L36 _public member_ `FMaterialId OverlayMaterialId;`
- L38 _public member_ `TArray<FOverrideMaterial> OverrideMaterials;`
- L40 _public member_ `TArray<FOverlayMaterial> OverlayMaterials;`
- L42 _public member_ `FSkeletalMeshId SkeletalMeshId;`

#### class `UE::Mutable::Private::FInstance`  
`class FInstance : public FResource`  
_L50-110_
- inherits: `FResource`
- desc: A customised object created from a model and a set of parameter values. It corresponds to an "engine object" but the contents of its data depends on the Model, and it may contain any number of LODs, components, surfaces, meshes and images, even none.
- L59 _public prototype_ `UE::Mutable::Private::TManagedPtr<FInstance> Clone() const;` — Clone this instance
- L62 _public prototype_ `int32 GetDataSize() const override;` — Resource interface
- L69 _public prototype_ `int32 GetComponentCount() const;` — Get the number of components of this instance.
- L73 _public prototype_ `FComponentId GetComponentId(int32 ComponentIndex) const;` — Get the Id of a component \param ComponentIndex Index of the component, from 0 to GetComponentCount()-1
- L75 _public prototype_ `FSkeletalMeshId GetSkeletalMeshId(int32 ComponentIndex) const;`
- L79 _public prototype_ `FMaterialId GetOverlayMaterialId(int32 ComponentIndex) const;` — Get the index of the overlay material. \param ComponentIndex Index of the component, from 0 to GetComponentCount()-1
- L81 _public prototype_ `int32 GetOverrideMaterialCount(int32 ComponentIndex) const;`
- L83 _public prototype_ `FName GetOverrideMaterialSlotSlotName(int32 ComponentIndex, int32 MaterialIndex) const;`
- L85 _public prototype_ `FMaterialId GetOverrideMaterialId(int32 ComponentIndex, int32 MaterialIndex) const;`
- L87 _public prototype_ `int32 GetOverlayMaterialCount(int32 ComponentIndex) const;`
- L89 _public prototype_ `FName GetOverlayMaterialSlotSlotName(int32 ComponentIndex, int32 MaterialIndex) const;`
- L91 _public prototype_ `FMaterialId GetOverlayMaterialId(int32 ComponentIndex, int32 MaterialIndex) const;`
- L94 _public prototype_ `int32 GetExtensionDataCount() const;` — Get the number of ExtensionData values in a component
- L96 _public prototype_ `int32 AddComponent();`
- L98 _public prototype_ `void SetSkeletalMeshId(int32 ComponentIndex, const FSkeletalMeshId& SkeletalMeshId);`
- L100 _public prototype_ `void SetOverlayMaterialId(int32 ComponentIndex, const FMaterialId& MaterialId);`
- L102 _public prototype_ `void AddOverrideMaterial(int32 ComponentIndex, const FName& SlotName, const FMaterialId& MaterialId);`
- L104 _public prototype_ `void AddOverlayMaterial(int32 ComponentIndex, const FName& SlotName, const FMaterialId& MaterialId);`
- L106 _public member_ `TArray<FInstanceComponent, TInlineAllocator<1>> Components;`
- L109 _public member_ `TArray<TManagedPtr<const FExtensionData>> ExtensionData;` — Every entry must have a valid ExtensionData and name

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/LOD.h` (Internal)


#### class `UE::Mutable::Private::FLOD`  
`class FLOD : public FResource`  
_L13-28_
- inherits: `FResource`
- L17 _public function_ `virtual int32 GetDataSize() const override` — FResource interface
- L19 _public function_ `TManagedPtr<FLOD> Clone() const`
- L27 _public member_ `TArray<TManagedPtr<const FMesh>> Meshes;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Layout.h` (Internal)


#### enum `UE::Mutable::Private::EAutoBlocksStrategy`  
`enum class EAutoBlocksStrategy : uint32`  
_L18-23_
- desc: Types of automatic block strategies
- L20 _public enumerator_ `Rectangles`
- L21 _public enumerator_ `UVIslands`
- L22 _public enumerator_ `Ignore`

#### enum `UE::Mutable::Private::EPackStrategy`  
`enum class EPackStrategy : uint32`  
_L26-31_
- desc: Types of layout packing strategies
- L28 _public enumerator_ `Resizeable`
- L29 _public enumerator_ `Fixed`
- L30 _public enumerator_ `Overlay`

#### enum `UE::Mutable::Private::EReductionMethod`  
`enum class EReductionMethod : uint32`  
_L34-38_
- desc: Types of layout reduction methods
- L36 _public enumerator_ `Halve` — Divide axis by 2
- L37 _public enumerator_ `Unitary` — Reduces 1 block the axis

#### struct `UE::Mutable::Private::FLayoutBlock`  
`struct FLayoutBlock`  
_L41-100_
- L43 _public member_ `static constexpr uint64 InvalidBlockId = TNumericLimits<uint64>::Max();`
- L44 _public member_ `static constexpr uint64 InvalidMaskIndex = TNumericLimits<uint16>::Max();`
- L46 _public member_ `FIntVector2 Min = { 0, 0 };`
- L47 _public member_ `FIntVector2 Size = { 0, 0 };`
- L50 _public member_ `uint64 Id;` — Absolute id used to control merging of various layouts
- L53 _public member_ `int32 Priority;` — Priority value to control the shrink texture layout strategy
- L56 _public member_ `uint16 bReduceBothAxes : 1;` — Value to control the method to reduce the block
- L59 _public member_ `uint16 bReduceByTwo : 1;` — Value to control if a block has to be reduced by two in an unitary reduction strategy
- L62 _public member_ `uint16 UnusedPadding : 14;` — Explicit padding to prevent uninitialized memory in this POD.
- L70 _public member_ `uint16 MaskIndex = InvalidMaskIndex;` — Index of the block mask used to classify the vertices and decide if they belong to the block. The image is stored in the Masks array of the FLayout object. It is interpreted as covering the space of the entire layout grid. If the mask is null, all the vertices inside the block rect belong to the block. The image may be shared among several blocks and also among several layouts.
- L73 _public function_ `FLayoutBlock(FIntVector2 InMin = {}, FIntVector2 InSize = {})`
- L85 _public function_ `inline bool operator==(const FLayoutBlock& o) const`
- L90 _public function_ `inline bool IsSimilar(const FLayoutBlock& o) const`

#### class `UE::Mutable::Private::FLayout`  
`class FLayout : public FResource`  
_L108-209_
- inherits: `FResource`
- desc: Image block layout class. It contains the information about what blocks are defined in a texture layout (texture coordinates set from a mesh). It is usually not necessary to use this objects, except for some advanced cases.
- L113 _public member_ `FIntVector2 Size = FIntVector2(0, 0);`
- L118 _public member_ `FIntVector2 MaxSize = FIntVector2(0, 0);` — Maximum size in layout blocks that this layout can grow to. From there on, blocks will shrink to fit. If 0,0 then no maximum size applies.
- L121 _public member_ `EPackStrategy Strategy = EPackStrategy::Resizeable;`
- L124 _public member_ `EReductionMethod ReductionMethod = EReductionMethod::Halve;`
- L127 _public member_ `TArray<FLayoutBlock> Blocks;`
- L132 _public member_ `TArray<TManagedPtr<const FImage>> Masks;` — List of masks that may be used by the blocks for finer-grade selection of vertices. The masks may be shared by multiple blocks and also across layouts.
- L141 _public prototype_ `TManagedPtr<FLayout> Clone() const;` — Deep clone this layout.
- L144 _public prototype_ `static void Serialise( const FLayout* p, FOutputArchive& arch );` — Serialisation
- L145 _public prototype_ `static TManagedRef<FLayout> StaticUnserialise( FInputArchive& arch );`
- L148 _public prototype_ `bool operator==( const FLayout& other ) const;` — Full compare
- L151 _public prototype_ `int32 GetDataSize() const override;` — Resource interface
- L158 _public prototype_ `FIntPoint GetGridSize() const;` — Get the resolution of the grid where the blocks are defined.
- L164 _public prototype_ `void SetGridSize( int32 SizeX, int32 SizeY );` — Get the resolution of the grid where the blocks are defined. It must be bigger than 0 on each axis. \param sizeX width of the grid. \param sizeY height of the grid.
- L169 _public prototype_ `void GetMaxGridSize(int32* SizeX, int32* SizeY) const;` — Get the maximum resolution of the grid where the blocks are defined. \param[out] pSizeX The integer pointed by this will be set to the width of the grid. \param[out] pSizeY The integer pointed by this will be set to the height of the grid.
- L175 _public prototype_ `void SetMaxGridSize(int32 SizeX, int32 SizeY);` — Get the maximum resolution of the grid where the blocks are defined. It must be bigger than 0 on each axis. \param sizeX width of the grid. \param sizeY height of the grid.
- L178 _public prototype_ `int32 GetBlockCount() const;` — Return the number of blocks in this layout.
- L182 _public prototype_ `void SetBlockCount( int32 );` — Set the number of blocks in this layout. The existing blocks will be kept as much as possible. The new blocks will be undefined.
- L186 _public prototype_ `void SetLayoutPackingStrategy(EPackStrategy);` — Set the texture layout packing strategy By default the texture layout packing strategy is set to resizable layout
- L189 _public prototype_ `EPackStrategy GetLayoutPackingStrategy() const;` — Set the texture layout packing strategy
- L196 _public prototype_ `void Serialise(FOutputArchive& arch) const;`
- L199 _public prototype_ `void Unserialise(FInputArchive& arch);`
- L202 _public prototype_ `bool IsSimilar(const FLayout& o) const;`
- L205 _public prototype_ `int32 FindBlock(uint64 Id) const;` — Find a block by id. This converts the "absolute" id to a relative index to the layout blocks. Return -1 if not found.
- L208 _public prototype_ `bool IsSingleBlockAndFull() const;` — Return true if the layout is a single block filling all area.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L211 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FLayoutBlock);` (scope `UE::Mutable::Private`)
- L212 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FLayoutBlock);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ManagedPointer.h` (Internal)


#### struct `UE::Mutable::Private::ManagedPointerInternal::FStaticCastTag`  
`struct FStaticCastTag`  
_L41-41_

#### struct `UE::Mutable::Private::ManagedPointerInternal::FConstCastTag`  
`struct FConstCastTag`  
_L42-42_

#### struct `UE::Mutable::Private::ManagedPointerInternal::FNullTag`  
`struct FNullTag`  
_L43-43_

#### struct `UE::Mutable::Private::ManagedPointerInternal::FNullWithControllerTag`  
`struct FNullWithControllerTag`  
_L44-44_

#### enum `UE::Mutable::Private::ManagedPointerInternal::EReferenceControllerFlags`  
`enum class EReferenceControllerFlags : uint8`  
_L46-52_
- L48 _public enumerator_ `None = 0`
- L49 _public enumerator_ `Deleted = 1 << 0`
- L51 _public enumerator_ `Null = 1 << 2` — Locked  = 1 << 1,

#### class `UE::Mutable::Private::ManagedPointerInternal::FReferenceControllerBase`  
`class FReferenceControllerBase`  
_L56-235_
- L61 _private member_ `mutable UE::FMutex Lock;` — For now a FMutex is used to guarantee thread safety. All operations should lock for a very small amount of cycles an so FMutex is very unlikely to yield the thread. If this becomes problematic, an atomic state could be used.
- L63 _private member_ `EReferenceControllerFlags Flags = EReferenceControllerFlags::None;`
- L66 _private member_ `int32 StrongRefCount {1};` — Always start with one strong reference, this is the reference added at Object creation.
- L67 _private member_ `int32 WeakRefCount {0};`
- L71 _public function_ `virtual ~FReferenceControllerBase()`
- L75 _public prototype_ `virtual void DeleteObject() = 0;`
- L77 _public function_ `inline bool IsUniqueReference() const`
- L84 _public function_ `inline bool IsUniqueStrong() const`
- L91 _public function_ `inline bool IsUniqueWeak() const`
- L98 _public function_ `inline void AddStrongReference()`
- L105 _public function_ `bool ConditionallyAddStrongReference()`
- L118 _public function_ `int32 GetStrongReferenceCount()`
- L130 _public function_ `inline void ReleaseStrongReference()`
- L157 _public function_ `inline void AddWeakReference()`
- L164 _public function_ `inline void ReleaseWeakReference()`
- L191 _public function_ `inline bool TryDeleteObject()`
- L214 _public function_ `inline bool IsDeleted() const`
- L221 _public function_ `inline void SetNull()`
- L229 _public function_ `inline bool IsNull() const`

#### class `UE::Mutable::Private::ManagedPointerInternal::TIntrusiveReferenceController`  
`template<typename ObjectType> class TIntrusiveReferenceController : public FReferenceControllerBase`  
_L238-263_
- inherits: `FReferenceControllerBase`
- L240 _private member_ `mutable TTypeCompatibleBytes<ObjectType> ObjectStorage;`
- L245 _public function_ `template<typename... ArgTypes> explicit TIntrusiveReferenceController(ArgTypes&&... Args)`
- L250 _public function_ `virtual void DeleteObject() override`
- L255 _public function_ `ObjectType* GetObjectPtr() const`
- L261 _public prototype_ `TIntrusiveReferenceController(const TIntrusiveReferenceController&) = delete;` — Non-copyable
- L262 _public prototype_ `TIntrusiveReferenceController& operator=(const TIntrusiveReferenceController&) = delete;`

#### class `UE::Mutable::Private::ManagedPointerInternal::TNullReferenceController`  
`template<typename ObjectType> class TNullReferenceController : public FReferenceControllerBase`  
_L266-283_
- inherits: `FReferenceControllerBase`
- L270 _public function_ `explicit TNullReferenceController()`
- L275 _public function_ `virtual void DeleteObject() override`
- L279 _public function_ `ObjectType* GetObjectPtr() const`

#### class `UE::Mutable::Private::ManagedPointerInternal::FStrongReferencer`  
`class FStrongReferencer`  
_L305-386_
- L310 _public prototype_ `inline FStrongReferencer();` — Constructor for an empty strong referencer object
- L313 _public prototype_ `inline explicit FStrongReferencer(FReferenceControllerBase* InReferenceController);` — Constructor that counts a single reference to the specified object
- L316 _public prototype_ `inline FStrongReferencer(const FStrongReferencer& Other);` — Copy constructor creates a new reference to the existing object
- L319 _public prototype_ `inline FStrongReferencer(FStrongReferencer&& Other);` — Move constructor creates no new references
- L325 _public prototype_ `inline FStrongReferencer(const FWeakReferencer& OtherWeak);` — Creates a strong referencer object from a weak referencer object.  This will only result in a valid object reference if the object already has at least one other strong referencer.
- L331 _public prototype_ `inline FStrongReferencer(FWeakReferencer&& OtherWeak);` — Creates a strong referencer object from a weak referencer object.  This will only result in a valid object reference if the object already has at least one other strong referencer.
- L334 _public prototype_ `inline ~FStrongReferencer();` — Destructor.
- L338 _public prototype_ `inline FStrongReferencer& operator=(const FStrongReferencer& Other);` — Assignment operator adds a reference to the assigned object.  If this counter was previously referencing an object, that reference will be released.
- L343 _public prototype_ `inline FStrongReferencer& operator=(FStrongReferencer&& Other);` — Move assignment operator adds no references to the assigned object.  If this counter was previously referencing an object, that reference will be released.
- L350 _public prototype_ `inline bool IsValid() const;` — Tests to see whether or not this strong counter contains a valid reference @return  True if reference is valid
- L352 _public prototype_ `inline bool IsNull() const;`
- L359 _public prototype_ `inline int32 GetStrongReferenceCount() const;` — Returns the number of strong references to this object (including this reference.) @return  Number of strong references to the object (including this reference.)
- L366 _public prototype_ `inline bool IsUniqueReference() const;` — Returns true if this is the only reference to this object, weak or strong. @return  True if there is only one reference to the object.
- L373 _public prototype_ `inline bool IsUniqueStrong() const;` — Returns true if this the only strong reference to this object. @return True if there is only one strong reference to the object.
- L375 _public prototype_ `inline bool TryDeleteObject();`
- L385 _private member_ `FReferenceControllerBase* ReferenceController;` — Pointer to the reference controller for the object a strong reference/pointer is referencing
- L447 _function_ `inline FStrongReferencer::FStrongReferencer() : ReferenceController(nullptr)`
- L452 _function_ `inline FStrongReferencer::FStrongReferencer(FReferenceControllerBase* InReferenceController) : ReferenceController(InReferenceController)`
- L457 _function_ `inline FStrongReferencer::FStrongReferencer(const FStrongReferencer& Other) : ReferenceController(Other.ReferenceController)`
- L468 _function_ `inline FStrongReferencer::FStrongReferencer(FStrongReferencer&& Other) : ReferenceController(Other.ReferenceController)`
- L474 _function_ `inline FStrongReferencer::FStrongReferencer(const FWeakReferencer& OtherWeak) : ReferenceController(OtherWeak.ReferenceController)`
- L491 _function_ `inline FStrongReferencer::FStrongReferencer(FWeakReferencer&& OtherWeak) : ReferenceController(OtherWeak.ReferenceController)`
- L513 _function_ `inline FStrongReferencer::~FStrongReferencer()`
- L521 _function_ `inline FStrongReferencer& FStrongReferencer::operator=(const FStrongReferencer& Other)`
- L546 _function_ `inline FStrongReferencer& FStrongReferencer::operator=(FStrongReferencer&& Other)`
- L568 _function_ `inline bool FStrongReferencer::TryDeleteObject()`
- L578 _function_ `inline bool FStrongReferencer::IsValid() const`
- L583 _function_ `inline bool FStrongReferencer::IsNull() const`
- L593 _function_ `inline int32 FStrongReferencer::GetStrongReferenceCount() const`
- L598 _function_ `inline bool FStrongReferencer::IsUniqueReference() const`
- L603 _function_ `inline bool FStrongReferencer::IsUniqueStrong() const`

#### class `UE::Mutable::Private::ManagedPointerInternal::FWeakReferencer`  
`class FWeakReferencer`  
_L392-444_
- desc: FWeakReferencer is a wrapper around a pointer to a reference controller that is used by a TManagedWeakPtr to keep track of a referenced object's lifetime.
- L397 _public prototype_ `inline FWeakReferencer();` — Default constructor with empty counter
- L400 _public prototype_ `inline FWeakReferencer(const FWeakReferencer& Other);` — Construct a weak referencer object from another weak referencer
- L403 _public prototype_ `inline FWeakReferencer(FWeakReferencer&& Other);` — Construct a weak referencer object from an rvalue weak referencer
- L406 _public prototype_ `inline FWeakReferencer(const FStrongReferencer& OtherStrongRef);` — Construct a weak referencer object from a strong referencer object
- L409 _public prototype_ `inline ~FWeakReferencer();` — Destructor.
- L413 _public prototype_ `inline FWeakReferencer& operator=(const FWeakReferencer& Other);` — Assignment operator from a weak referencer object.  If this counter was previously referencing an object, that reference will be released.
- L417 _public prototype_ `inline FWeakReferencer& operator=(FWeakReferencer&& Other);` — Assignment operator from an rvalue weak referencer object.  If this counter was previously referencing an object, that reference will be released.
- L421 _public prototype_ `inline FWeakReferencer& operator=(const FStrongReferencer& OtherStrongRef);` — Assignment operator from a strong reference counter.  If this counter was previously referencing an object, that reference will be released.
- L428 _public prototype_ `inline bool IsValid() const;` — Tests to see whether or not this weak counter contains a valid reference @return  True if reference is valid
- L434 _private prototype_ `inline void AssignReferenceController(FReferenceControllerBase* NewReferenceController);` — Assigns a new reference controller to this counter object, first adding a reference to it, then releasing the previous object.
- L443 _private member_ `FReferenceControllerBase* ReferenceController;` — Pointer to the reference controller for the object a TManagedWeakPtr is referencing
- L609 _function_ `inline FWeakReferencer::FWeakReferencer() : ReferenceController(nullptr)`
- L614 _function_ `inline FWeakReferencer::FWeakReferencer(const FWeakReferencer& Other) : ReferenceController(Other.ReferenceController)`
- L624 _function_ `inline FWeakReferencer::FWeakReferencer(FWeakReferencer&& Other) : ReferenceController(Other.ReferenceController)`
- L630 _function_ `inline FWeakReferencer::FWeakReferencer(const FStrongReferencer& OtherStrongRef) : ReferenceController(OtherStrongRef.ReferenceController)`
- L640 _function_ `inline FWeakReferencer::~FWeakReferencer()`
- L650 _function_ `inline FWeakReferencer& FWeakReferencer::operator=(const FWeakReferencer& Other)`
- L657 _function_ `inline FWeakReferencer& FWeakReferencer::operator=(FWeakReferencer&& Other)`
- L671 _function_ `inline FWeakReferencer& FWeakReferencer::operator=(const FStrongReferencer& OtherStrongRef)`
- L678 _function_ `inline bool FWeakReferencer::IsValid() const`
- L683 _function_ `inline void FWeakReferencer::AssignReferenceController(FReferenceControllerBase* NewReferenceController)`

#### class `UE::Mutable::Private::TManagedRef`  
`template<class ObjectType> class TManagedRef`  
_L728-948_
- L731 _public typedef_ `using ElementType = ObjectType;`
- L744 _public function_ `inline TManagedRef(const TManagedRef<OtherType>& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L751 _public function_ `inline TManagedRef(const TManagedRef& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L757 _public function_ `inline TManagedRef(TManagedRef&& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L773 _public function_ `inline TManagedRef& operator=(const TManagedRef& Other)` — Assignment operator replaces this strong reference with the specified strong reference.  The object currently referenced by this strong reference will no longer be referenced and will be deleted if there are no other referencers. @param  Other  Strong reference to replace with
- L780 _public function_ `inline TManagedRef& operator=(TManagedRef&& Other)`
- L791 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TManagedPtr<ObjectType> ToStrongPtr() const` — Converts a strong reference to a strong pointer. @return  Managed pointer to the object
- L801 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TManagedWeakPtr<ObjectType> ToWeakPtr() const` — Converts a strong reference to a weak ptr. @return  Weak pointer to the object
- L811 _public function_ `[[nodiscard]] inline ObjectType& Get() const` — Returns a C++ reference to the object this strong reference is referencing @return  The object owned by this strong reference
- L823 _public function_ `[[nodiscard]] inline ObjectType& operator*() const` — Dereference operator returns a reference to the object this strong pointer points to @return  Reference to the object
- L835 _public function_ `[[nodiscard]] inline ObjectType* operator->() const` — Arrow operator returns a pointer to this strong reference's object @return  Returns a pointer to the object referenced by this strong reference
- L847 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsUniqueReference() const` — Returns true if this is the only reference to this object, weak or strong. @return  True if there is only one reference to the object.
- L853 _public function_ `template <typename OtherType> [[nodiscard]] bool UEOpEquals(const TManagedRef<OtherType>& Rhs) const`
- L859 _public function_ `template <typename OtherType> [[nodiscard]] bool UEOpEquals(const TManagedPtr<OtherType>& Rhs) const`
- L867 _public function_ `template <typename OtherType> [[nodiscard]] bool UEOpEquals(const TManagedWeakPtr<OtherType>& Rhs) const`
- L873 _public function_ `template <typename OtherType> [[nodiscard]] bool UEOpLessThan(const TManagedRef<OtherType>& Rhs) const`
- L890 _private function_ `inline explicit TManagedRef(const TManagedPtr<OtherType>& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L903 _private function_ `inline explicit TManagedRef(TManagedPtr<OtherType>&& Other) : Object(Other.Object) , StrongReferenceState(MoveTemp(Other.StrongReferenceState))`
- L920 _private function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsValid() const` — Checks to see if this strong reference is actually pointing to an object. NOTE: This validity test is intentionally private because strong references must always be valid. @return  True if the strong reference is valid and can be dereferenced
- L937 _private member_ `ObjectType* Object;` — The object we're holding a reference to.  Can be nullptr.
- L941 _private member_ `ManagedPointerInternal::FStrongReferencer StrongReferenceState;` — Interface to the reference counter for this object.  Note that the actual reference controller object is strong by all strong and weak pointers that refer to the object
- L943 _private function_ `inline explicit TManagedRef(ObjectType* InObject, ManagedPointerInternal::FReferenceControllerBase* InController) : Object(InObject) , StrongReferenceState(InController)`

#### class `UE::Mutable::Private::TManagedPtr`  
`template<typename ObjectType> class TManagedPtr`  
_L952-1311_
- L955 _public typedef_ `using ElementType = ObjectType;`
- L960 _public function_ `inline TManagedPtr(ManagedPointerInternal::FNullTag* = nullptr) : Object(nullptr) , StrongReferenceState()` — Constructs an empty strong pointer
- L976 _public function_ `inline TManagedPtr(const TManagedPtr<OtherType>& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L982 _public function_ `inline TManagedPtr(const TManagedPtr& Other) : Object(Other.Object) , StrongReferenceState(Other.StrongReferenceState)`
- L988 _public function_ `inline TManagedPtr(TManagedPtr&& Other) : Object(Other.Object) , StrongReferenceState(MoveTemp(Other.StrongReferenceState))`
- L1005 _public function_ `inline TManagedPtr(const TManagedRef<OtherType>& OtherRef) : Object(OtherRef.Object) , StrongReferenceState(OtherRef.StrongReferenceState)`
- L1022 _public function_ `template <typename OtherType> inline TManagedPtr(const TManagedPtr<OtherType>& Other, ManagedPointerInternal::FStaticCastTag) : Object(static_cast<ObjectType*>(Other.Object)) , StrongReferenceState(Other.StrongReferenceState)` — Special constructor used internally to statically cast one strong pointer type to another.  You should never call this constructor directly.  Instead, use the StaticCastManagedPtr() function. This constructor creates a strong pointer as a strong reference to an existing strong pointer after statically casting that pointer's object.  This constructor is needed for static casts. @param  InSharedPtr  The strong pointer whose object we should create an additional reference to
- L1037 _public function_ `template <typename OtherType> inline TManagedPtr(const TManagedPtr<OtherType>& Other, ManagedPointerInternal::FConstCastTag) : Object(const_cast<ObjectType*>(Other.Object)) , StrongReferenceState(Other.StrongReferenceState)` — Special constructor used internally to cast a 'const' strong pointer a 'mutable' pointer.  You should never call this constructor directly.  Instead, use the ConstCastManagedPtr() function. This constructor creates a strong pointer as a strong reference to an existing strong pointer after const casting that pointer's object.  This constructor is needed for const casts. @param  Other  The strong pointer whose object we should create an additional reference to
- L1050 _public function_ `inline TManagedPtr& operator=(const TManagedPtr& Other)` — Assignment operator replaces this strong pointer with the specified strong pointer.  The object currently referenced by this strong pointer will no longer be referenced and will be deleted if there are no other referencers. @param  Other  Shared pointer to replace with
- L1062 _public function_ `inline TManagedPtr& operator=(TManagedPtr&& Other)` — Disable false positive buffer overrun warning during pgo linking step. PGO_LINK_DISABLE_WARNINGS
- L1080 _public function_ `[[nodiscard]] inline TManagedRef<ObjectType> ToStrongRef() const&` — Converts a strong pointer to a strong reference.  The pointer *must* be valid or an assertion will trigger. @return  Reference to the object
- L1093 _public function_ `[[nodiscard]] inline TManagedRef<ObjectType> ToStrongRef() &&` — Converts a strong pointer to a strong reference.  The pointer *must* be valid or an assertion will trigger. @return  Reference to the object
- L1106 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TManagedWeakPtr<ObjectType> ToWeakPtr() const` — Converts a strong pointer to a weak ptr. @return  Weak pointer to the object
- L1116 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT ObjectType* Get() const` — Returns the object referenced by this pointer, or nullptr if no object is reference @return  The object owned by this strong pointer, or nullptr
- L1126 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT explicit operator bool() const` — Checks to see if this strong pointer is actually pointing to an object @return  True if the strong pointer is valid and can be dereferenced
- L1136 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const bool IsValid() const` — Checks to see if this strong pointer is actually pointing to an object @return  True if the strong pointer is valid and can be dereferenced
- L1147 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const bool IsSet() const` — Check to see if this trong pointer has been set to an explicit value using the Make* functions. NOTE: The pointer may have been set with the MakeNull function, and not be valid. @return True if the strong pointer has beens set an explicit value.
- L1162 _public function_ `[[nodiscard]] inline U& operator*() const`
- L1173 _public function_ `[[nodiscard]] inline ObjectType* operator->() const` — Arrow operator returns a pointer to the object this strong pointer references @return  Returns a pointer to the object referenced by this strong pointer
- L1183 _public function_ `UE_FORCEINLINE_HINT void Reset()` — Resets this strong pointer, removing a reference to the object.  If there are no other strong references to the object then it will be destroyed.
- L1193 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsUniqueReference() const` — Returns true if this is the only reference, strong or weak, to this object. @return  True if there is only one reference to the object.
- L1199 _public function_ `template <typename OtherType> [[nodiscard]] inline bool UEOpEquals(const TManagedPtr<OtherType>& Rhs) const`
- L1205 _public function_ `template <typename OtherType> [[nodiscard]] UE_REWRITE bool UEOpEquals(const TManagedWeakPtr<OtherType>& Rhs) const`
- L1210 _public function_ `[[nodiscard]] UE_REWRITE bool UEOpEquals(TYPE_OF_NULLPTR) const`
- L1216 _public function_ `template <typename OtherType> [[nodiscard]] inline bool UEOpLessThan(const TManagedPtr<OtherType>& Rhs) const`
- L1222 _public function_ `inline bool TryDeleteObject()` — Deletes the object if this is the only strong reference.
- L1248 _private function_ `inline explicit TManagedPtr(const TManagedWeakPtr<OtherType>& OtherWeak) : Object(nullptr) , StrongReferenceState(OtherWeak.WeakReferenceState)`
- L1273 _private function_ `inline explicit TManagedPtr(TManagedWeakPtr<OtherType>&& OtherWeak) : Object(nullptr) , StrongReferenceState(MoveTemp(OtherWeak.WeakReferenceState))`
- L1298 _private member_ `ObjectType* Object;` — The object we're holding a reference to.  Can be nullptr.
- L1302 _private member_ `ManagedPointerInternal::FStrongReferencer StrongReferenceState;` — Interface to the reference counter for this object.  Note that the actual reference controller object is strong by all strong and weak pointers that refer to the object
- L1305 _private function_ `inline explicit TManagedPtr(ManagedPointerInternal::FReferenceControllerBase* InController, ManagedPointerInternal::FNullWithControllerTag) : Object(nullptr) , StrongReferenceState(InController)` — Special constructor only used when we want to create a null refrence with a null controller

#### class `UE::Mutable::Private::TManagedWeakPtr`  
`template<class ObjectType> class TManagedWeakPtr`  
_L1318-1621_
- desc: TManagedWeakPtr is a non-intrusive reference-counted weak object pointer.
- L1321 _public typedef_ `using ElementType = ObjectType;`
- L1324 _public function_ `inline TManagedWeakPtr(ManagedPointerInternal::FNullTag* = nullptr) : Object(nullptr) , WeakReferenceState()` — Constructs an empty TWeakPtr
- L1339 _public function_ `inline TManagedWeakPtr(const TManagedRef<OtherType>& OtherStrongRef) : Object(OtherStrongRef.Object) , WeakReferenceState(OtherStrongRef.StrongReferenceState)`
- L1354 _public function_ `inline TManagedWeakPtr(const TManagedPtr<OtherType>& OtherStrong) : Object(OtherStrong.Object ) , WeakReferenceState(OtherStrong.StrongReferenceState)`
- L1369 _public function_ `template <typename OtherType> inline TManagedWeakPtr(const TManagedWeakPtr<OtherType>& Other, ManagedPointerInternal::FStaticCastTag) : Object(static_cast<ObjectType*>(Other.Object)) , WeakReferenceState(Other.WeakReferenceState)` — Special constructor used internally to statically cast one weak pointer type to another.  You should never call this constructor directly.  Instead, use the StaticCastManagedWeakPtr() function. This constructor creates a weak pointer as a weak reference to an existing weak pointer after statically casting that pointer's object.  This constructor is needed for static casts. @param  Other  The weak pointer whose object we should create an additional reference to
- L1384 _public function_ `template <typename OtherType> inline TManagedWeakPtr(TManagedWeakPtr<OtherType> const& Other, ManagedPointerInternal::FConstCastTag) : Object(const_cast<ObjectType*>(Other.Object)) , WeakReferenceState(Other.WeakReferenceState)` — Special constructor used internally to cast a 'const' weak pointer a 'mutable' pointer.  You should never call this constructor directly.  Instead, use the ConstCastManagedWeakPtr() function. This constructor creates a weak pointer as a weak reference to an existing weak pointer after const casting that pointer's object.  This constructor is needed for const casts. @param  Other  The weak pointer whose object we should create an additional reference to
- L1400 _public function_ `inline TManagedWeakPtr(const TManagedWeakPtr<OtherType>& Other) : Object(Other.Object) , WeakReferenceState(Other.WeakReferenceState)`
- L1410 _public function_ `inline TManagedWeakPtr(TManagedWeakPtr<OtherType>&& Other) : Object(Other.Object) , WeakReferenceState(MoveTemp(Other.WeakReferenceState))`
- L1417 _public function_ `inline TManagedWeakPtr(const TManagedWeakPtr& Other) : Object(Other.Object) , WeakReferenceState(Other.WeakReferenceState)`
- L1423 _public function_ `inline TManagedWeakPtr(TManagedWeakPtr&& Other) : Object(Other.Object) , WeakReferenceState(MoveTemp(Other.WeakReferenceState))`
- L1433 _public function_ `inline TManagedWeakPtr& operator=(ManagedPointerInternal::FNullTag*)` — Assignment to a nullptr pointer.  Clears this weak pointer's reference.
- L1445 _public function_ `inline TManagedWeakPtr& operator=(const TManagedWeakPtr& Other)` — Assignment operator adds a weak reference to the object referenced by the specified weak pointer @param  Other  The weak pointer for the object to assign
- L1453 _public function_ `inline TManagedWeakPtr& operator=(TManagedWeakPtr&& OtherPtr)`
- L1475 _public function_ `inline TManagedWeakPtr& operator=(const TManagedWeakPtr<OtherType>& Other)`
- L1487 _public function_ `inline TManagedWeakPtr& operator=(TManagedWeakPtr<OtherType>&& OtherPtr)`
- L1505 _public function_ `inline TManagedWeakPtr& operator=(const TManagedRef<OtherType>& OtherStrongRef)`
- L1521 _public function_ `inline TManagedWeakPtr& operator=(const TManagedPtr<OtherType>& OtherStrongPtr)`
- L1538 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TManagedPtr<ObjectType> Pin() const&` — Converts this weak pointer to a strong pointer that you can use to access the object (if it hasn't expired yet.)  Remember, if there are no more strong references to the object, the object may have been deleted and the retuned value not be valid.  You should always check to make sure the returned pointer is valid before trying to dereference the strong pointer. @return  Strong pointer for this object (will only be valid if not deleted)
- L1552 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TManagedPtr<ObjectType> Pin() &&` — Converts this weak pointer to a strong pointer that you can use to access the object (if it hasn't expired yet.)  Remember, if there are no more strong references to the object, the object may have been deleted and the retuned value not be valid.  You should always check to make sure the returned pointer is valid before trying to dereference the strong pointer. @return  Strong pointer for this object (will only be valid if not deleted)
- L1562 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsValid() const` — Checks to see if this weak pointer actually has a valid reference to an object @return  True if the weak pointer is valid and a pin operator would have succeeded
- L1571 _public function_ `UE_FORCEINLINE_HINT void Reset()` — Resets this weak pointer, removing a weak reference to the object.  If there are no other strong or weak references to the object, then the tracking object will be destroyed.
- L1579 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool HasSameObject( const void* InOtherPtr ) const` — Returns true if the object this weak pointer points to is the same as the specified object pointer.
- L1584 _public function_ `UE_FORCEINLINE_HINT uint32 GetWeakPtrTypeHash() const`
- L1590 _public function_ `template <typename OtherType> [[nodiscard]] inline bool UEOpEquals(const TManagedWeakPtr<OtherType>& Rhs) const`
- L1595 _public function_ `[[nodiscard]] UE_REWRITE bool UEOpEquals(TYPE_OF_NULLPTR) const`
- L1601 _public function_ `template <typename OtherType> [[nodiscard]] inline bool UEOpLessThan(const TManagedWeakPtr<OtherType>& Rhs) const`
- L1616 _private member_ `ObjectType* Object;` — The object we have a weak reference to.  Can be nullptr.  Also, it's important to note that because this is a weak reference, the object this pointer points to may have already been destroyed.
- L1620 _private member_ `ManagedPointerInternal::FWeakReferencer WeakReferenceState;` — Interface to the reference counter for this object.  Note that the actual reference controller object is strong by all strong and weak pointers that refer to the object

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L38 _namespace_ `namespace ManagedPointerInternal` (scope `UE::Mutable::Private`)
- L54 _prototype_ `ENUM_CLASS_FLAGS(EReferenceControllerFlags);` (scope `UE::Mutable::Private::ManagedPointerInternal`)
- L286 _function_ `template<typename ObjectType, typename... ArgsTypes> TIntrusiveReferenceController<ObjectType>* NewIntrusiveReferenceController(ArgsTypes&&... Args)` (scope `UE::Mutable::Private::ManagedPointerInternal`)
- L292 _function_ `template<typename ObjectType> TNullReferenceController<ObjectType>* NewNullReferenceController()` (scope `UE::Mutable::Private::ManagedPointerInternal`)
- L712 _namespace_ `namespace ManagedPointerInternal` (scope `UE::Mutable::Private`)
- L715 _function_ `template<typename ObjectType> TManagedRef<ObjectType> MakeManagedStrongRef(ObjectType* Object, FReferenceControllerBase* Controller)` (scope `UE::Mutable::Private::ManagedPointerInternal`)
- L721 _function_ `template<typename ObjectType> TManagedPtr<ObjectType> MakeManagedNullPtr(FReferenceControllerBase* Controller)` (scope `UE::Mutable::Private::ManagedPointerInternal`)
- L1625 _function_ `template <typename ObjectType, typename... ArgTypes> [[nodiscard]] inline TManagedRef<ObjectType> MakeManaged(ArgTypes&&... Args)` (scope `UE::Mutable::Private`)
- L1635 _function_ `template <typename ObjectType> [[nodiscard]] inline TManagedPtr<ObjectType> MakeManagedNull()` (scope `UE::Mutable::Private`)
- L1649 _function_ `template<class CastToType, class CastFromType> [[nodiscard]] UE_FORCEINLINE_HINT TManagedPtr<CastToType> StaticCastManagedPtr(const TManagedPtr<CastFromType>& Other)` (scope `UE::Mutable::Private`) — Casts a strong pointer of one type to another type. (static_cast)  Useful for down-casting. @param  Other  The strong pointer to cast
- L1661 _function_ `template <class CastToType, class CastFromType> [[nodiscard]] UE_FORCEINLINE_HINT TManagedWeakPtr<CastToType> StaticCastManagedWeakPtr(const TManagedWeakPtr<CastFromType>& Other)` (scope `UE::Mutable::Private`) — Casts a weak pointer of one type to another type. (static_cast)  Useful for down-casting. @param  Other  The weak pointer to cast
- L1673 _function_ `template <class CastToType, class CastFromType> [[nodiscard]] UE_FORCEINLINE_HINT TManagedRef<CastToType> ConstCastManagedStrongRef(const TManagedRef<CastFromType>& Other)` (scope `UE::Mutable::Private`) — Casts a 'const' strong reference to 'mutable' strong reference. (const_cast) @param  Other  The strong reference to cast
- L1685 _function_ `template <class CastToType, class CastFromType> [[nodiscard]] UE_FORCEINLINE_HINT TManagedPtr<CastToType> ConstCastManagedPtr(const TManagedPtr<CastFromType>& Other)` (scope `UE::Mutable::Private`) — Casts a 'const' strong pointer to 'mutable' strong pointer. (const_cast) @param  Other  The strong pointer to cast
- L1697 _function_ `template <class CastToType, class CastFromType> [[nodiscard]] UE_FORCEINLINE_HINT TManagedWeakPtr<CastToType> ConstCastManagedWeakPtr(const TManagedWeakPtr<CastFromType>& Other)` (scope `UE::Mutable::Private`) — Casts a 'const' weak pointer to 'mutable' weak pointer. (const_cast) @param  InWeakPtr  The weak pointer to cast
- L1711 _function_ `template <typename ObjectType> [[nodiscard]] uint32 GetTypeHash(const TManagedRef<ObjectType>& InStrongRef)` (scope `UE::Mutable::Private`) — Computes a hash code for this object @param  InStrongRef  Strong pointer to compute hash code for @return  Hash code value
- L1724 _function_ `template <typename ObjectType> [[nodiscard]] uint32 GetTypeHash(const TManagedPtr<ObjectType>& InStrongPtr)` (scope `UE::Mutable::Private`) — Computes a hash code for this object @param  InStrongPtr  Shared pointer to compute hash code for @return  Hash code value
- L1737 _function_ `template <typename ObjectType> [[nodiscard]] uint32 GetTypeHash(const TManagedWeakPtr<ObjectType>& InWeakPtr)` (scope `UE::Mutable::Private`) — Computes a hash code for this object @param  InWeakPtr  Weak pointer to compute hash code for @return  Hash code value

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Material.h` (Internal)


#### struct `UE::Mutable::Private::FParameterKey`  
`struct FParameterKey`  
_L23-32_
- L25 _public member_ `FName ParameterName;`
- L26 _public member_ `int8 LayerIndex = -1;`
- L28 _public prototype_ `inline void Serialise(FOutputArchive& arch) const;`
- L29 _public prototype_ `inline void Unserialise(FInputArchive& arch);`
- L31 _public prototype_ `bool operator==(const FParameterKey& Other) const = default;`

#### class `UE::Mutable::Private::FMaterial`  
`class FMaterial : public FResource`  
_L44-86_
- inherits: `FResource`
- desc: Material type resource
- L53 _public prototype_ `static void Serialise(const FMaterial* MaterialPtr, FOutputArchive& Arch);` — Serialisation
- L54 _public prototype_ `static TManagedPtr<FMaterial> StaticUnserialise(FInputArchive& Arch);`
- L57 _public prototype_ `TManagedPtr<FMaterial> Clone() const;` — Clone this material
- L60 _public function_ `virtual int32 GetDataSize() const override` — Resource interface
- L65 _public prototype_ `bool operator==(const FMaterial& Other) const;`
- L66 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L67 _public prototype_ `void Unserialise(FInputArchive&);`
- L70 _public member_ `TPassthroughObjectPtr<UMaterialInterface> PassthroughObject;` — Passthrough Id or TStrongObjectPtr.
- L83 _public member_ `TMap<FParameterKey, FImageParameterData> ImageParameters;`
- L84 _public member_ `TMap<FParameterKey, FVector4f> ColorParameters;`
- L85 _public member_ `TMap<FParameterKey, float> ScalarParameters;`

#### struct `UE::Mutable::Private::FMaterial::FImageParameterData`  
`struct FImageParameterData`  
_L72-81_
- L74 _public member_ `TVariant<FOperation::ADDRESS, TManagedPtr<const FImage>> ImageParameter;`
- L75 _public member_ `int32 ImagePropertyIndex;`
- L77 _public prototype_ `inline void Serialise(FOutputArchive& arch) const;`
- L78 _public prototype_ `inline void Unserialise(FInputArchive& arch);`
- L80 _public prototype_ `bool operator==(const FImageParameterData& Other) const = default;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Mutable` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L35 _function_ `inline uint32 GetTypeHash(const FParameterKey& Key)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MemoryCounters.h` (Internal)


#### struct `UE::Mutable::Private::MemoryCounters::FInternalMemoryCounter`  
`struct FInternalMemoryCounter`  
_L10-13_
- L12 _public prototype_ `static std::atomic<SSIZE_T>& Get();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L8 _namespace_ `namespace MemoryCounters` (scope `UE::Mutable::Private`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L19 _typedef_ `using AllocType = FDefaultMemoryTrackingAllocator<MemoryCounters::FInternalMemoryCounter>;` (scope `UE::Mutable::Private`)
- L22 _typedef_ `template<class Type, class Alloc = AllocType > using TMemoryTrackedArray = TArray<Type, Alloc>;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MemoryTrackingAllocationPolicy.h` (Internal)


#### class `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper`  
`template<typename BaseAlloc, typename CounterType> class TMemoryTrackingAllocatorWrapper`  
_L28-157_
- L33 _public typedef_ `using SizeType = typename BaseAlloc::SizeType;`

#### enum `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::(anonymous)`  
`enum`  
_L35-35_

#### enum `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::(anonymous)`  
`enum`  
_L36-36_

#### class `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::ForAnyElementType`  
`class ForAnyElementType : private BaseAlloc::ForAnyElementType`  
_L45-141_
- inherits: `BaseAlloc::ForAnyElementType`
- desc: ForAnyElementType is privately inherited from the wrapped allocator ForAnyElementType so the base class members must be explicitly defined to compile. This way if any new method is added to the allocator interface, it forces its addition here. This is useful in case the new method needs to do some memory tracking, otherwise a simple using declaration may suffice.
- L48 _public function_ `ForAnyElementType()`
- L53 _public function_ `inline ~ForAnyElementType()` — Destructor.
- L64 _public prototype_ `ForAnyElementType(const ForAnyElementType&) = delete;`
- L65 _public prototype_ `ForAnyElementType& operator=(const ForAnyElementType&) = delete;`
- L67 _public function_ `inline void MoveToEmpty(ForAnyElementType& Other)`
- L81 _public function_ `inline void ResizeAllocation( SizeType CurrentNum, SizeType NewMax, SIZE_T NumBytesPerElement )`
- L105 _public function_ `inline void ResizeAllocation( SizeType CurrentNum, SizeType NewMax, SIZE_T NumBytesPerElement, uint32 AlignmentOfElement )`
- L140 _private member_ `SSIZE_T AllocSize = 0;`

#### class `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::ForElementType`  
`template<typename ElementType> class ForElementType : public ForAnyElementType`  
_L144-155_
- inherits: `ForAnyElementType`
- L147 _public function_ `ForElementType()`
- L151 _public function_ `inline ElementType* GetAllocation() const`

#### struct `TAllocatorTraits`  
`template<typename BaseAlloc, typename Counter> struct TAllocatorTraits<UE::Mutable::Private::TMemoryTrackingAllocatorWrapper<BaseAlloc, Counter>> : public TAllocatorTraits<BaseAlloc>`  
_L183-186_
- inherits: `TAllocatorTraits<BaseAlloc>`

#### enum `TAllocatorTraits::(anonymous)`  
`enum`  
_L185-185_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L35 _enumerator_ `enum { NeedsElementType = BaseAlloc::NeedsElementType }; enum { RequireRangeCheck = BaseAlloc::RequireRangeCheck }; /** * ForAnyElementType is privately inherited from the wrapped allocator ForAnyElementType so * the base class members must be explicitly defined to compile. This way if any new method * is added to the allocator interface` (scope `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::__anon2d90b7e40103`)
- L36 _enumerator_ `enum { RequireRangeCheck = BaseAlloc::RequireRangeCheck }; /** * ForAnyElementType is privately inherited from the wrapped allocator ForAnyElementType so * the base class members must be explicitly defined to compile. This way if any new method * is added to the allocator interface` (scope `UE::Mutable::Private::TMemoryTrackingAllocatorWrapper::__anon2d90b7e40203`)
- L163 _typedef_ `template<typename CounterType> using FDefaultMemoryTrackingAllocator = TMemoryTrackingAllocatorWrapper<FDefaultAllocator, CounterType>;` (scope `UE::Mutable::Private`)
- L166 _typedef_ `template<typename CounterType> using FDefaultMemoryTrackingBitArrayAllocator = TInlineAllocator<4, FDefaultMemoryTrackingAllocator<CounterType>>;` (scope `UE::Mutable::Private`)
- L169 _typedef_ `template<typename CounterType> using FDefaultMemoryTrackingSparceArrayAllocator = TSparseArrayAllocator< FDefaultMemoryTrackingAllocator<CounterType>, FDefaultMemoryTrackingBitArrayAllocator<CounterType>>;` (scope `UE::Mutable::Private`)
- L174 _typedef_ `template<typename CounterType> using FDefaultMemoryTrackingSetAllocator = TSetAllocator< FDefaultMemoryTrackingSparceArrayAllocator<CounterType>, TInlineAllocator<1, FDefaultMemoryTrackingAllocator<CounterType>>, DEFAULT_NUMBER_OF_ELEMENTS_PER_HASH_BUCKET, DEFAULT_BASE_NUMBER_OF_HASH_BUCKETS, DEFAULT_MIN_NUMBER_OF_HASHED_ELEMENTS>;` (scope `UE::Mutable::Private`)
- L185 _enumerator_ `enum { SupportsMoveFromOtherAllocator = false };` (scope `TAllocatorTraits::__anon2d90b7e40303`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MemoryTrackingUtils.h` (Internal)


#### struct `UE::Mutable::Private::FGlobalMemoryCounter`  
`struct FGlobalMemoryCounter`  
_L22-40_
- L25 _private member_ `static inline SSIZE_T AbsoluteCounter { 0 };`
- L26 _private member_ `static inline SSIZE_T AbsolutePeakValue { 0 };`
- L27 _private member_ `static inline SSIZE_T Counter { 0 };`
- L28 _private member_ `static inline SSIZE_T PeakValue { 0 };`
- L30 _private member_ `static inline FCriticalSection Mutex {};`
- L33 _public prototype_ `static void Update(SSIZE_T Differential);`
- L34 _public prototype_ `static void Zero();`
- L35 _public prototype_ `static void Restore();`
- L36 _public prototype_ `static SSIZE_T GetPeak();`
- L37 _public prototype_ `static SSIZE_T GetCounter();`
- L38 _public prototype_ `static SSIZE_T GetAbsolutePeak();`
- L39 _public prototype_ `static SSIZE_T GetAbsoluteCounter();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L13 _macro_ `#define UE_MUTABLE_TRACK_ALLOCATOR_MEMORY_PEAK 1`
- L15 _macro_ `#define UE_MUTABLE_TRACK_ALLOCATOR_MEMORY_PEAK 0`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Mutable` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Mesh.h` (Internal)


#### struct `UE::Mutable::Private::FSurfaceSubMesh`  
`struct FSurfaceSubMesh`  
_L46-57_
- L48 _public member_ `int32 VertexBegin = 0;`
- L49 _public member_ `int32 VertexEnd = 0;`
- L50 _public member_ `int32 IndexBegin = 0;`
- L51 _public member_ `int32 IndexEnd = 0;`

#### enum `UE::Mutable::Private::EMorphUsageFlags`  
`enum class EMorphUsageFlags : uint8`  
_L63-74_
- L65 _public enumerator_ `None = 0`
- L67 _public enumerator_ `Baked = 1 << 0`
- L68 _public enumerator_ `RealTime = 1 << 1`
- L69 _public enumerator_ `External = 1 << 2`
- L71 _public enumerator_ `Merged = RealTime | External`
- L73 _public enumerator_ `AllFlags = 0xFF`

#### struct `UE::Mutable::Private::FMeshSurface`  
`struct FMeshSurface`  
_L80-104_
- L82 _public member_ `TArray<FSurfaceSubMesh, TInlineAllocator<1>> SubMeshes;`
- L84 _public member_ `uint32 BoneMapIndex = 0;`
- L85 _public member_ `uint32 BoneMapCount = 0;`
- L86 _public member_ `uint32 Id = 0;`
- L87 _public member_ `bool bCastShadow = false;`
- L88 _public member_ `bool bRecomputeTangent = false;`
- L102 _public prototype_ `inline void Serialise(FOutputArchive& Arch) const;`
- L103 _public prototype_ `inline void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FTriangleInfo`  
`struct FTriangleInfo`  
_L107-120_
- desc: Helper structs for mesh utility methods below.
- L110 _public member_ `uint32 Indices[3];` — Vertex indices in the original mesh.
- L113 _public member_ `uint32 CollapsedIndices[3];` — Vertex indices in the collapsed vertex list of the mesh.
- L116 _public member_ `uint16 BlockIndices[3];` — Optional data with layout block indices.
- L119 _public member_ `bool bUVsFixed = false;` — Optional data with a flag indicating the UVs have changed during layout for this trioangle.

#### struct `UE::Mutable::Private::FMeshMorph`  
`struct FMeshMorph`  
_L123-144_
- L125 _public member_ `TArray<FName> Names;`
- L127 _public member_ `TArray<FVector4f> MaximumValuePerMorph;`
- L128 _public member_ `TArray<FVector4f> MinimumValuePerMorph;`
- L129 _public member_ `TArray<uint32> BatchStartOffsetPerMorph;`
- L130 _public member_ `TArray<uint32> BatchesPerMorph;`
- L132 _public member_ `TArray<TArray<int32, TInlineAllocator<1>>> SurfacesInUsePerMorph;`
- L134 _public member_ `TArray<EMorphUsageFlags> UsageFlagsPerMorph;`
- L136 _public member_ `uint32 NumTotalBatches = 0;`
- L137 _public member_ `float PositionPrecision = 0.0f;` — TODO MORPHS Due to merging, this must be per block
- L138 _public member_ `float TangentZPrecision = 0.0f;` — TODO MORPHS Due to merging, this must be per block
- L140 _public prototype_ `bool operator==(const FMeshMorph&) const = default;`
- L142 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L143 _public prototype_ `void Unserialise(FInputArchive&);`

#### struct `UE::Mutable::Private::FSkinWeightProfile`  
`struct FSkinWeightProfile`  
_L147-176_
- L149 _public member_ `FName Name;`
- L151 _public member_ `bool bDefaultProfile = false;`
- L152 _public member_ `int8 DefaultProfileFromLODIndex = 0;`
- L154 _public member_ `uint8 NumBoneInfluences = 0;`
- L155 _public member_ `bool bUse16BitBoneIndex = false;`
- L156 _public member_ `bool bUse16BitBoneWeight = false;`
- L158 _public member_ `TArray<uint8> BoneIDs;`
- L159 _public member_ `TArray<uint8> BoneWeights;`
- L168 _public member_ `TArray<FVertexInfo> VertexIndexToInfluenceOffset;`
- L170 _public prototype_ `void CopyMetadata(const FSkinWeightProfile& From);`
- L172 _public prototype_ `bool operator==(const FSkinWeightProfile&) const = default;`
- L174 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L175 _public prototype_ `void Unserialise(FInputArchive&);`

#### struct `UE::Mutable::Private::FSkinWeightProfile::FVertexInfo`  
`struct FVertexInfo`  
_L161-167_
- L163 _public member_ `uint32 VertexIndex;`
- L164 _public member_ `uint32 InfluenceOffset;`
- L166 _public prototype_ `bool operator==(const FVertexInfo&) const = default;`

#### struct `UE::Mutable::Private::FMeshSocket`  
`struct FMeshSocket`  
_L182-198_
- L184 _public member_ `FName SocketName;`
- L185 _public member_ `FName BoneName;`
- L186 _public member_ `FVector RelativeLocation = FVector::ZeroVector;`
- L187 _public member_ `FRotator RelativeRotation = FRotator::ZeroRotator;`
- L188 _public member_ `FVector RelativeScale = FVector::ZeroVector;`
- L190 _public member_ `bool bForceAlwaysAnimated = false;`
- L192 _public member_ `int8 Priority = 0;` — Not serialized. AddMetadata may modify it
- L194 _public prototype_ `bool operator==(const FMeshSocket&) const = default;`
- L196 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L197 _public prototype_ `void Unserialise(FInputArchive&);`

#### enum `UE::Mutable::Private::EBoneUsageFlags`  
`enum class EBoneUsageFlags : uint32`  
_L212-223_
- L214 _public enumerator_ `None = 0`
- L215 _public enumerator_ `Root = 1 << 1`
- L216 _public enumerator_ `Skinning = 1 << 2`
- L217 _public enumerator_ `SkinningParent = 1 << 3`
- L218 _public enumerator_ `Physics = 1 << 4`
- L219 _public enumerator_ `PhysicsParent = 1 << 5`
- L220 _public enumerator_ `Deform = 1 << 6`
- L221 _public enumerator_ `DeformParent = 1 << 7`
- L222 _public enumerator_ `Reshaped = 1 << 8`

#### enum `UE::Mutable::Private::EBaseMeshBufferType`  
`enum EBaseMeshBufferType : uint8`  
_L227-238_
- L229 _public enumerator_ `Position`
- L230 _public enumerator_ `TexCoords`
- L231 _public enumerator_ `Tangent`
- L232 _public enumerator_ `Color`
- L233 _public enumerator_ `Skinning`
- L234 _public enumerator_ `Indices`
- L236 _public enumerator_ `None`
- L237 _public enumerator_ `NumTypes = None`

#### enum `UE::Mutable::Private::EMeshBufferType`  
`enum class EMeshBufferType`  
_L241-251_
- L243 _public enumerator_ `None`
- L244 _public enumerator_ `SkeletonDeformBinding`
- L245 _public enumerator_ `PhysicsBodyDeformBinding`
- L246 _public enumerator_ `PhysicsBodyDeformSelection`
- L247 _public enumerator_ `PhysicsBodyDeformOffsets`
- L248 _public enumerator_ `MeshLaplacianData`
- L249 _public enumerator_ `MeshLaplacianOffsets`
- L250 _public enumerator_ `UniqueVertexMap`

#### enum `UE::Mutable::Private::EShapeBindingMethod`  
`enum class EShapeBindingMethod : uint32`  
_L254-260_
- L256 _public enumerator_ `ReshapeClosestProject = 0`
- L257 _public enumerator_ `ClipDeformClosestProject = 1`
- L258 _public enumerator_ `ClipDeformClosestToSurface = 2`
- L259 _public enumerator_ `ClipDeformNormalProject = 3`

#### enum `UE::Mutable::Private::EVertexColorUsage`  
`enum class EVertexColorUsage : uint32`  
_L262-267_
- L264 _public enumerator_ `None = 0`
- L265 _public enumerator_ `ReshapeMaskWeight = 1`
- L266 _public enumerator_ `ReshapeClusterId = 2`

#### enum `UE::Mutable::Private::EMeshCopyFlags`  
`enum class EMeshCopyFlags : uint32`  
_L274-301_
- L276 _public enumerator_ `None = 0`
- L277 _public enumerator_ `WithSkeletalMesh = 1 << 1`
- L278 _public enumerator_ `WithSurfaces = 1 << 2`
- L279 _public enumerator_ `WithSkeleton = 1 << 3`
- L280 _public enumerator_ `WithPhysicsBody = 1 << 4`
- L281 _public enumerator_ `WithFaceGroups = 1 << 5`
- L282 _public enumerator_ `WithGameplayTags = 1 << 6`
- L283 _public enumerator_ `WithVertexBuffers = 1 << 7`
- L284 _public enumerator_ `WithIndexBuffers = 1 << 8`
- L285 _public enumerator_ `WithSockets = 1 << 9`
- L286 _public enumerator_ `WithAdditionalBuffers = 1 << 10`
- L287 _public enumerator_ `WithLayouts = 1 << 11`
- L288 _public enumerator_ `WithPoses = 1 << 12`
- L289 _public enumerator_ `WithBoneMap = 1 << 13`
- L290 _public enumerator_ `WithSkeletonIDs = 1 << 14`
- L291 _public enumerator_ `WithAdditionalPhysics = 1 << 15`
- L292 _public enumerator_ `WithAssetUserData = 1 << 16`
- L293 _public enumerator_ `WithMorphData = 1 << 17`
- L294 _public enumerator_ `WithMorphMetaData = 1 << 18`
- L295 _public enumerator_ `WithClothData = 1 << 19`
- L296 _public enumerator_ `WithAnimSlots = 1 << 20`
- L297 _public enumerator_ `WithSkinWeightProfileData = 1 << 21`
- L298 _public enumerator_ `WithSkinWeightProfileMetaData = 1 << 22`
- L300 _public enumerator_ `AllFlags = 0xFFFFFFFF`

#### enum `UE::Mutable::Private::EMeshContentFlags`  
`enum class EMeshContentFlags : uint8`  
_L305-315_
- L307 _public enumerator_ `None = 0`
- L308 _public enumerator_ `GeometryData = 1 << 0`
- L309 _public enumerator_ `PoseData = 1 << 1`
- L310 _public enumerator_ `PhysicsData = 1 << 2`
- L311 _public enumerator_ `MetaData = 1 << 3`
- L313 _public enumerator_ `LastFlag = MetaData`
- L314 _public enumerator_ `AllFlags = (LastFlag << 1) - 1`

#### enum `UE::Mutable::Private::EMeshFlags`  
`enum class EMeshFlags : uint32`  
_L319-328_
- desc: Optimised mesh formats that are identified in some operations to chose a faster version.
- L321 _public enumerator_ `None = 0`
- L324 _public enumerator_ `ProjectFormat = 1 << 0` — The mesh is formatted to be used for planar and cilyndrical projection
- L327 _public enumerator_ `ProjectWrappingFormat = 1 << 1` — The mesh is formatted to be used for wrapping projection

#### class `UE::Mutable::Private::FMesh`  
`class FMesh : public FResource`  
_L336-739_
- inherits: `FResource`
- desc: Mesh object containing any number of buffers with any number of channels. The buffers can be per-index or per-vertex. The mesh also includes layout information for every texture channel for internal usage, and it can be ignored. The meshes are always assumed to be triangle list primitives.
- L340 _public member_ `static constexpr uint64 InvalidVertexId = TNumericLimits<uint64>::Max();`
- L349 _public prototype_ `static TManagedRef<FMesh> CreateAsReference(const TPassthroughObjectPtr<USkeletalMesh>& PasstroughObjectPtr);` — Create a new empty mesh that repreents an external resource mesh.
- L352 _public prototype_ `TManagedPtr<FMesh> Clone() const;` — Deep clone this mesh.
- L355 _public prototype_ `TManagedPtr<FMesh> Clone(EMeshCopyFlags Flags) const;` — Clone with flags allowing to not include some parts in the cloned mesh
- L358 _public prototype_ `void CopyFrom(const FMesh& From, EMeshCopyFlags Flags = EMeshCopyFlags::AllFlags);` — Copy form another mesh.
- L361 _public prototype_ `static void Serialise(const FMesh* InMesh, FOutputArchive& Arch );` — Serialisation
- L362 _public prototype_ `static TManagedPtr<FMesh> StaticUnserialise(FInputArchive& Arch);`
- L365 _public prototype_ `int32 GetDataSize() const override;` — Resource interface
- L372 _public prototype_ `bool IsReference() const;` — Return true if this is a reference to an engine image.
- L375 _public prototype_ `void SetReferencedMorph(const FString& MorphName);` — Mesh references can actually reference a morphed mesh. In that case you can set and get the morph with these functions.
- L376 _public prototype_ `const FString& GetReferencedMorph() const;`
- L382 _public prototype_ `int32 GetIndexCount() const;`
- L385 _public prototype_ `FMeshBufferSet& GetIndexBuffers();` — Index buffers. They are owned by this mesh.
- L386 _public prototype_ `const FMeshBufferSet& GetIndexBuffers() const;`
- L389 _public prototype_ `int32 GetVertexCount() const;`
- L392 _public prototype_ `FMeshBufferSet& GetVertexBuffers();` — Vertex buffers. They are owned by this mesh.
- L393 _public prototype_ `const FMeshBufferSet& GetVertexBuffers() const;`
- L395 _public prototype_ `int32 GetFaceCount() const;`
- L401 _public prototype_ `int32 GetSurfaceCount() const;` — Get the number of surfaces defined in this mesh. Surfaces are buffer-contiguous mesh fragments that share common properties (usually material)
- L402 _public prototype_ `void GetSurface(int32 SurfaceIndex, int32& OutFirstVertex, int32& OutVertexCount, int32& OutFirstIndex, int32& OutIndexCount, int32& OutFirstBone, int32& OutBoneCount) const;`
- L411 _public prototype_ `uint32 GetSurfaceId(int32 SurfaceIndex) const;` — Return an internal id that can be used to match mesh surfaces and instance surfaces. Only valid for meshes that are part of instances.
- L418 _public prototype_ `bool AreVertexIdsImplicit() const;` — Return true if the mesh has unique vertex IDs and they stored in an implicit way. This is relevant for some mesh operations that will need to make them explicit so that the result is still correct.
- L419 _public prototype_ `bool AreVertexIdsExplicit() const;`
- L422 _public prototype_ `void MakeVertexIdsRelative();` — Create an explicit vertex buffer for vertex IDs if they are implicit.
- L425 _public prototype_ `void MakeIdsExplicit();` — Ensure the format of an empty mesh includes explicit IDs. The mesh cannot have any vertex data.
- L431 _public prototype_ `void AddLayout( TManagedPtr<const FLayout> );`
- L434 _public prototype_ `int32 GetLayoutCount() const;`
- L437 _public prototype_ `TManagedPtr<const FLayout> GetLayout( int32 Index) const;`
- L440 _public prototype_ `void SetLayout( int32 Index, TManagedPtr<const FLayout> );`
- L446 _public prototype_ `void SetSkeleton(const TManagedPtr<const FSkeleton>&);`
- L447 _public prototype_ `TManagedPtr<const FSkeleton> GetSkeleton() const;`
- L449 _public prototype_ `void ConvertBoneIdsToIndices();`
- L456 _public prototype_ `void SetPhysicsBody(const TManagedPtr<const FPhysicsBody>&);`
- L457 _public prototype_ `TManagedPtr<const FPhysicsBody> GetPhysicsBody() const;`
- L459 _public prototype_ `int32 AddAdditionalPhysicsBody(const TManagedPtr<const FPhysicsBody>&);`
- L460 _public prototype_ `TManagedPtr<const FPhysicsBody> GetAdditionalPhysicsBody(int32 I) const;`
- L464 _public prototype_ `int32 FindBonePoseByBoneIndex(int32 Index) const;`
- L467 _public prototype_ `void SetBonePoseCount(int32 Count);`
- L470 _public prototype_ `int32 GetBonePoseCount() const;`
- L473 _public prototype_ `void SetBonePose(int32 Index, FBoneIdOrIndex BoneName, FTransform3f Transform, EBoneUsageFlags BoneUsageFlags, int8 Priority = 0);`
- L476 _public prototype_ `FBoneIdOrIndex GetBonePoseId(int32 BoneIndex) const;` — @return - Bone identifier of the pose at 'Index'.
- L479 _public prototype_ `void GetBonePoseTransform(int32 BoneIndex, FTransform3f& Transform) const;` — Return a matrix stored per bone. It is a set of 16-float values.
- L482 _public prototype_ `EBoneUsageFlags GetBoneUsageFlags(int32 BoneIndex) const;`
- L485 _public prototype_ `void SetBoneMap(const TArray<FBoneIdOrIndex>& InBoneMap);` — Set the bonemap of this mesh
- L488 _public prototype_ `const TArray<FBoneIdOrIndex>& GetBoneMap() const;` — Return an array containing the bonemaps of all surfaces in the mesh.
- L494 _public prototype_ `uint32 GetId() const;` — Get an internal identifier used to reference this mesh in operations like deferred mesh building, or instance updating.
- L496 _public prototype_ `bool HasMorphs() const;`
- L498 _public prototype_ `bool HasClothing() const;`
- L501 _public typedef_ `template<typename Type> using TMemoryTrackedArray = TArray<Type, FDefaultMemoryTrackingAllocator<MemoryCounters::FMeshMemoryCounter>>;`
- L504 _public member_ `mutable uint32 InternalId = 0;` — Non-persistent internal id unique for a mesh generated for a specific state and parameter values.
- L510 _public member_ `mutable EMeshFlags Flags = EMeshFlags::None;` — This is bit - mask on the EMeshFlags enumeration, marking what static formats are compatible with this one and other properties. It should be reset after any operation that modifies the format.
- L513 _public member_ `TPassthroughObjectPtr<USkeletalMesh> PassthroughObject;` — Passthrough Id or TStrongObjectPtr.
- L516 _public member_ `FString ReferencedMorph;` — If the mesh is a reference the referenced morph name is stored here. Otherwise it is an empty string.
- L522 _public member_ `uint32 MeshIDPrefix = 0;` — Prefix for the unique IDs related to this mesh (vertices and layout blocks). Useful if the mesh stores them in an implicit, or relative way. See MeshVertexIdIterator for details.
- L524 _public member_ `FMeshBufferSet VertexBuffers;`
- L526 _public member_ `FMeshBufferSet IndexBuffers;`
- L528 _public member_ `TArray<uint32> MorphDataBuffer;`
- L531 _public member_ `TArray<TPair<EMeshBufferType, FMeshBufferSet>> AdditionalBuffers;` — Additional buffers used for temporary or custom data in different algorithms.
- L533 _public member_ `TArray<FMeshSurface> Surfaces;`
- L535 _public member_ `FMeshMorph Morph;`
- L538 _public member_ `TArray<FCloth> ClothSections;` — Only valid if the mesh is a LOD (has multiple sections).
- L541 _public member_ `TArray<FSkinWeightProfile> SkinWeightProfiles;` — SkinWeight Profiles
- L544 _public member_ `TArray<TPassthroughObjectPtr<USkeleton>> SkeletonObjects;` — Externally provided skeletons required by this mesh.
- L550 _public member_ `TManagedPtr<const FSkeleton> Skeleton;` — This skeleton and physicsbody are not owned and may be used by other meshes, so it cannot be modified once the mesh has been fully created.
- L551 _public member_ `TManagedPtr<const FPhysicsBody> PhysicsBody;`
- L554 _public member_ `TArray<TManagedPtr<const FPhysicsBody>> AdditionalPhysicsBodies;` — Additional physics bodies referenced by the mesh that don't merge.
- L557 _public member_ `TArray<TPassthroughObjectPtr<UPhysicsAsset>> PhysicsAssets;` — Physics assets referenced by the mesh to be merged.
- L560 _public member_ `TArray<TPassthroughObjectPtr<UPhysicsAsset>> AdditionalPhysicsAssets;` — Additional physics assets referenced by the mesh that don't merge.
- L566 _public member_ `TArray<TManagedPtr<const FLayout>> Layouts;` — Texture Layout blocks attached to this mesh. They are const because they could be shared with other meshes, so they need to be cloned and replaced if a modification is needed.
- L568 _public member_ `TArray<FName> GameplayTags;`
- L570 _public member_ `TArray<TPassthroughObjectPtr<UAssetUserData>> AssetUserData;`
- L572 _public member_ `TArray<TPair<FName, TPassthroughObjectPtr<UClass>>> AnimationSlots;`
- L602 _public member_ `TMemoryTrackedArray<FBonePose> BonePoses;` — This is the pose used by this mesh fragment, used to update the transforms of the final skeleton taking into consideration the meshes being used.
- L605 _public member_ `TArray<FBoneIdOrIndex> BoneMap;` — Array containing the bonemaps of all surfaces in the mesh.
- L608 _public member_ `TArray<FMeshSocket> Sockets;` — Array containing the sockets of this mesh. Not serialized. Added with Metadata
- L610 _public prototype_ `inline void Serialise(FOutputArchive& arch) const;`
- L612 _public prototype_ `inline void Unserialise(FInputArchive& arch);`
- L615 _public function_ `inline bool operator==(const FMesh& Other) const`
- L690 _public prototype_ `bool IsSimilar(const FMesh& Other) const;` — Compare the mesh with another one, but ignore internal data like generated vertex indices.
- L708 _public prototype_ `void GetVertexMap(const FMesh& Other, FVertexMatchMap& VertexMap, float Tolerance = 1e-3f) const;`
- L711 _public prototype_ `UE::Math::TIntVector3<uint32> GetFaceVertexIndices(int32 FaceIndex) const;` — Compare the vertex attributes to check if they match.
- L717 _public prototype_ `bool HasCompatibleFormat(const FMesh* Other) const;` — Return true if the given mesh has the same vertex and index formats, and in the same buffer structure.
- L720 _public prototype_ `void ResetStaticFormatFlags() const;` — Update the flags identifying the mesh format as some of the optimised formats.
- L723 _public prototype_ `void EnsureSurfaceData();` — Create the surface data if not present.
- L726 _public prototype_ `void CheckIntegrity() const;` — Check mesh buffer data for possible inconsistencies
- L729 _public prototype_ `bool IsClosed() const;` — Return true if this mesh is closed. It is still closed if it has dangling vertices.
- L735 _public prototype_ `void ResetBufferIndices();` — Change the buffer descriptions so that all buffer indices start at 0 and are in the same order than memory.
- L738 _public prototype_ `void Log(FString& Out, int32 VertexLimit) const;` — Debug: get a text representation of the mesh

#### struct `UE::Mutable::Private::FMesh::FBonePose`  
`struct FBonePose`  
_L574-596_
- L577 _public member_ `FBoneIdOrIndex BoneId;` — Identifier built from the bone FName.
- L579 _public member_ `EBoneUsageFlags BoneUsageFlags = EBoneUsageFlags::None;`
- L582 _public member_ `int8 BonePosePriority = 0;` — Not serialized. Add Metadata may overwrite it.
- L584 _public member_ `FTransform3f BoneTransform;`
- L586 _public prototype_ `inline void Serialise(FOutputArchive& arch) const;`
- L587 _public prototype_ `inline void Unserialise(FInputArchive& arch);`
- L589 _public function_ `inline bool operator==(const FBonePose& Other) const`

#### struct `UE::Mutable::Private::FMesh::FVertexMatchMap`  
`struct FVertexMatchMap`  
_L697-706_
- desc: Make a map from the vertices in this mesh to thefirst matching vertex of the given mesh. If non is found, the index is set to -1.
- L700 _public member_ `TArray<int32> FirstMatch;` — One for every vertex
- L703 _public member_ `TArray<int32> Matches;` — The matches of every vertex in a sequence
- L705 _public prototype_ `bool DoMatch(int32 Vertex, int32 OtherVertex) const;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace Mutable` (scope `UE`)
- L37 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L53 _function_ `friend bool operator==(const FSurfaceSubMesh& Lhs, const FSurfaceSubMesh& Rhs)` (scope `UE::Mutable::Private`)
- L60 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FSurfaceSubMesh);` (scope `UE::Mutable::Private`)
- L61 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FSurfaceSubMesh);` (scope `UE::Mutable::Private`)
- L76 _prototype_ `ENUM_CLASS_FLAGS(EMorphUsageFlags);` (scope `UE::Mutable::Private`)
- L77 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(EMorphUsageFlags);` (scope `UE::Mutable::Private`)
- L78 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(EMorphUsageFlags);` (scope `UE::Mutable::Private`)
- L91 _function_ `friend bool operator==(const FMeshSurface& Lhs, const FMeshSurface& Rhs)` (scope `UE::Mutable::Private`)
- L179 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FSkinWeightProfile::FVertexInfo);` (scope `UE::Mutable::Private`)
- L180 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FSkinWeightProfile::FVertexInfo);` (scope `UE::Mutable::Private`)
- L202 _prototype_ `void GetUVIsland(TArray<FTriangleInfo>& InTriangles, const uint32 InFirstTriangle, TArray<uint32>& OutTriangleIndices, const TArray<FVector2f>& InUVs, const TMultiMap<int32, uint32>& InVertexToTriangleMap);` (scope `UE::Mutable::Private`) — Fill an array with the indices of all triangles belonging to the same UV island as InFirstTriangle.
- L209 _prototype_ `void MeshCreateCollapsedVertexMap(const FMesh* Mesh, TArray<int32>& CollapsedVertices);` (scope `UE::Mutable::Private`) — Create a map from vertices into vertices, collapsing vertices that have the same position.
- L225 _prototype_ `ENUM_CLASS_FLAGS(EBoneUsageFlags);` (scope `UE::Mutable::Private`)
- L269 _function_ `inline uint32 GetTypeHash(const EVertexColorUsage& Usage)` (scope `UE::Mutable::Private`)
- L303 _prototype_ `ENUM_CLASS_FLAGS(EMeshCopyFlags);` (scope `UE::Mutable::Private`)
- L316 _prototype_ `ENUM_CLASS_FLAGS(EMeshContentFlags);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MeshBufferSet.h` (Internal)


#### struct `UE::Mutable::Private::MemoryCounters::FMeshMemoryCounter`  
`struct FMeshMemoryCounter`  
_L15-18_
- L17 _public prototype_ `static std::atomic<SSIZE_T>& Get();`

#### enum `UE::Mutable::Private::EMeshBufferFormat`  
`enum class EMeshBufferFormat : uint32`  
_L24-75_
- desc: Supported formats for the elements in mesh buffers.
- L26 _public enumerator_ `None`
- L28 _public enumerator_ `Float16`
- L29 _public enumerator_ `Float32`
- L31 _public enumerator_ `UInt8`
- L32 _public enumerator_ `UInt16`
- L33 _public enumerator_ `UInt32`
- L34 _public enumerator_ `Int8`
- L35 _public enumerator_ `Int16`
- L36 _public enumerator_ `Int32`
- L39 _public enumerator_ `NUInt8` — Integers interpreted as being in the range 0.0f to 1.0f
- L40 _public enumerator_ `NUInt16`
- L41 _public enumerator_ `NUInt32`
- L44 _public enumerator_ `NInt8` — Integers interpreted as being in the range -1.0f to 1.0f
- L45 _public enumerator_ `NInt16`
- L46 _public enumerator_ `NInt32`
- L49 _public enumerator_ `PackedDir8` — Packed 1 to -1 value using multiply+add (128 is almost zero). Use 8-bit unsigned ints.
- L56 _public enumerator_ `PackedDir8_W_TangentSign` — Same as EMeshBufferFormat::PackedDir8, with the w component replaced with the sign of the determinant of the vertex basis to define the orientation of the tangent space in UE4 format. Use 8-bit unsigned ints.
- L59 _public enumerator_ `PackedDirS8` — Packed 1 to -1 value using multiply+add (128 is almost zero). Use 8-bit signed ints.
- L66 _public enumerator_ `PackedDirS8_W_TangentSign` — Same as EMeshBufferFormat::PackedDirS8, with the w component replaced with the sign of the determinant of the vertex basis to define the orientation of the tangent space in UE4 format. Use 8-bit signed ints.
- L68 _public enumerator_ `Float64`
- L69 _public enumerator_ `UInt64`
- L70 _public enumerator_ `Int64`
- L71 _public enumerator_ `NUInt64`
- L72 _public enumerator_ `NInt64`
- L74 _public enumerator_ `Count`

#### struct `UE::Mutable::Private::FMeshBufferFormatData`  
`struct FMeshBufferFormatData`  
_L78-85_
- L81 _public member_ `uint8 SizeInBytes;` — Size per component in bytes.
- L84 _public member_ `uint8 MaxValueBits;` — log 2 of the max value if integer.

#### enum `UE::Mutable::Private::EMeshBufferSemantic`  
`enum class EMeshBufferSemantic : uint32`  
_L91-135_
- desc: Semantics of the mesh buffers
- L93 _public enumerator_ `None`
- L96 _public enumerator_ `VertexIndex` — For index buffers, and mesh morphs
- L99 _public enumerator_ `Position` — Standard vertex semantics
- L100 _public enumerator_ `Normal`
- L101 _public enumerator_ `Tangent`
- L102 _public enumerator_ `Binormal`
- L103 _public enumerator_ `TexCoords`
- L104 _public enumerator_ `Color`
- L105 _public enumerator_ `BoneWeights`
- L106 _public enumerator_ `BoneIndices`
- L113 _public enumerator_ `LayoutBlock` — Internal semantic indicating what layout block each vertex belongs to. It can be safely ignored if present in meshes returned by the system. It will never be in the same buffer that other vertex semantics.
- L115 _public enumerator_ `_DEPRECATED`
- L122 _public enumerator_ `Other` — To let users define channels with semantics unknown to the system. These channels will never be transformed, and the per-vertex or per-index data will be simply copied.
- L124 _public enumerator_ `_DEPRECATED2`
- L127 _public enumerator_ `TriangleIndex` — Semantics usefule for mesh binding.
- L128 _public enumerator_ `BarycentricCoords`
- L129 _public enumerator_ `Distance`
- L131 _public enumerator_ `AltSkinWeight_DEPRECATED`
- L134 _public enumerator_ `Count` — Utility

#### struct `UE::Mutable::Private::FMeshBufferChannel`  
`struct FMeshBufferChannel`  
_L139-163_
- L141 _public member_ `EMeshBufferSemantic Semantic = EMeshBufferSemantic::None;`
- L143 _public member_ `EMeshBufferFormat Format = EMeshBufferFormat::None;`
- L146 _public member_ `int32 SemanticIndex = 0;` — Index of the semantic, in case there are more than one of this type.
- L149 _public member_ `uint16 Offset = 0;` — Offset in bytes from the begining of a buffer element
- L152 _public member_ `uint16 ComponentCount = 0;` — Number of components of the type in Format for every value in the channel
- L154 _public function_ `inline bool operator==(const FMeshBufferChannel& Other) const`

#### struct `UE::Mutable::Private::FMeshBuffer`  
`struct FMeshBuffer`  
_L166-215_
- L169 _public typedef_ `template<typename Type> using TMemoryTrackedArray = TArray<Type, FDefaultMemoryTrackingAllocator<MemoryCounters::FMeshMemoryCounter>>;`
- L171 _public member_ `TArray<FMeshBufferChannel> Channels;`
- L172 _public member_ `TMemoryTrackedArray<uint8> Data;`
- L173 _public member_ `uint32 ElementSize = 0;`
- L175 _public prototype_ `void Serialise(UE::Mutable::Private::FOutputArchive& Arch) const;`
- L176 _public prototype_ `inline void Unserialise(UE::Mutable::Private::FInputArchive& Arch);`
- L178 _public function_ `inline bool operator==(const FMeshBuffer& Other) const`
- L188 _public function_ `inline bool HasSemantic(EMeshBufferSemantic Semantic) const` — Return true if the buffer has any channel with the passed semantic.
- L200 _public function_ `inline bool HasSameFormat(const FMeshBuffer& Other) const`
- L205 _public function_ `inline bool HasPadding() const`

#### enum `UE::Mutable::Private::EMeshBufferSetFlags`  
`enum class EMeshBufferSetFlags : uint32`  
_L217-221_
- L219 _public enumerator_ `None = 0`
- L220 _public enumerator_ `IsDescriptor = 1 << 0`

#### class `UE::Mutable::Private::FMeshBufferSet`  
`class FMeshBufferSet`  
_L226-432_
- desc: Set of buffers storing mesh element data. Elements can be vertices, indices or faces.
- L230 _public member_ `uint32 ElementCount = 0;`
- L231 _public member_ `EMeshBufferSetFlags Flags = EMeshBufferSetFlags::None;`
- L232 _public member_ `TArray<FMeshBuffer> Buffers;`
- L234 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L235 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L237 _public function_ `inline bool operator==(const FMeshBufferSet& Other) const`
- L248 _public prototype_ `int32 GetElementCount() const;` — Get the number of elements in the buffers
- L254 _public prototype_ `void SetElementCount(int32 Count, EMemoryInitPolicy MemoryInitPolicy = EMemoryInitPolicy::Uninitialized);` — Set the number of vertices in the mesh. This will resize the vertex buffers keeping the previous data when possible. New data content is defined by MemoryInitPolicy.
- L260 _public prototype_ `int32 GetElementSize(int32 Buffer) const;` — Get the size in bytes of a buffer element. @param buffer index of the buffer from 0 to GetBufferCount()-1
- L263 _public prototype_ `int32 GetBufferCount() const;` — Get the number of vertex buffers in the mesh
- L266 _public prototype_ `void SetBufferCount(int32 Count);` — Set the number of vertex buffers in the mesh.
- L272 _public prototype_ `int32 GetBufferChannelCount(int32 BufferIndex) const;` — Get the number of channels in a vertex buffer. \param buffer index of the vertex buffer from 0 to GetBufferCount()-1
- L285 _public prototype_ `void GetChannel( int32 BufferIndex, int32 ChannelIndex, EMeshBufferSemantic* SemanticPtr, int32* SemanticIndexPtr, EMeshBufferFormat* FormatPtr, int32* ComponentCountPtr, int32* OffsetPtr ) const;` — Get a channel of a buffer by index \param buffer index of the vertex buffer from 0 to GetBufferCount()-1 \param channel index of the channel from 0 to GetBufferChannelCount( buffer )-1 \param[out] pSemantic semantic of the channel \param[out] pSemanticIndex index of the semantic in case of having more than one of the same type. \param[out] pFormat data format of the channel \param[out] pComponentCount components of an element of the channel \param[out] pOffset offset in bytes from the beginning of an element of the buffer
- L306 _public prototype_ `void SetBuffer( int32 BufferIndex, int32 ElementSize, int32 ChannelCount, const EMeshBufferSemantic* SemanticsPtr = nullptr, const int32* SemanticIndicesPtr = nullptr, const EMeshBufferFormat* FormatsPtr = nullptr, const int32* ComponentCountsPtr = nullptr, const int32* OffsetsPtr = nullptr, EMemoryInitPolicy MemoryInitPolicy = EMemoryInitPolicy::Uninitialized);` — Set all the channels of a buffer \param buffer index of the buffer from 0 to GetBufferCount()-1 \param elementSize sizei n bytes of a vertex element in this buffer \param channelCount number of channels to set in the buffer \param pSemantics buffer of channelCount semantics \param pSemanticIndices buffer of indices for the semantic of every channel \param pFormats buffer of channelCount formats \param pComponentCounts buffer of channelCount component counts \param pOffsets offsets in bytes of every particular channel inside the buffer element
- L323 _public prototype_ `void SetBufferChannel( int32 BufferIndex, int32 ChannelIndex, EMeshBufferSemantic Semantic, int32 SemanticIndex, EMeshBufferFormat Format, int32 ComponentCount, int32 Offset );` — Set one  channels of a buffer \param buffer index of the buffer from 0 to GetBufferCount()-1 \param elementSize sizei n bytes of a vertex element in this buffer \param channelIndex number of channels to set in the buffer
- L340 _public prototype_ `uint8* GetBufferData(int32 Buffer);` — Get a pointer to the object-owned data of a buffer. Channel data is interleaved for every element and packed in the order it was set without any padding. \param buffer index of the buffer from 0 to GetBufferCount()-1 \todo Add padding support for better alignment of buffer elements.
- L341 _public prototype_ `const uint8* GetBufferData(int32 Buffer) const;`
- L342 _public prototype_ `uint32 GetBufferDataSize(int32 Buffer) const;`
- L356 _public prototype_ `void FindChannel(EMeshBufferSemantic Semantic, int32 SemanticIndex, int32* BufferPtr, int32* ChannelPtr) const;` — Find the index of a buffer channel by semantic and relative index inside the semantic. \param semantic Semantic of the channel we are searching. \param semanticIndex Index of the semantic of the channel we are searching. e.g. if we want the second set of texture coordinates, it should be 1. \param[out] pBuffer -1 if the channel is not found, otherwise it will contain the index of the buffer where the channel was found. \param[out] pChannel -1 if the channel is not found, otherwise it will contain the channel index of the channel inside the buffer returned at [buffer]
- L363 _public prototype_ `int32 GetChannelOffset(int32 Buffer, int32 Channel) const;` — Get the offset in bytes of the data of this channel inside an element data. \param buffer index of the buffer from 0 to GetBufferCount()-1 \param channel index of the channel from 0 to GetBufferChannelCount( buffer )-1
- L369 _public prototype_ `void AddBuffer( const FMeshBufferSet& Other, int32 BufferIndex);` — Add a new buffer by cloning a buffer from another set. The buffers must have the same number of elements.
- L372 _public prototype_ `bool HasSameFormat(const FMeshBufferSet& Other) const;` — Return true if the formats of the two vertex buffers set match.
- L378 _public prototype_ `void RemoveBuffer(int32 BufferIndex);` — Remove the buffer at the specified position. This "invalidates" any buffer index that was referencing buffers after the removed one.
- L386 _public prototype_ `void CopyElement(uint32 FromIndex, uint32 ToIndex);` — Copy an element from one position to another, overwriting the other element. Both positions must be valid, buffer size won't change.
- L389 _public prototype_ `bool HasSameFormat(int32 ThisBufferIndex, const FMeshBufferSet& pOther, int32 OtherBufferIndex) const;` — Compare the format of the two buffers at index buffer and return true if they match.
- L392 _public prototype_ `int32 GetDataSize() const;` — Get the total memory size of the buffers and this struct
- L395 _public prototype_ `int32 GetAllocatedSize() const;`
- L401 _public prototype_ `bool IsSpecialBufferToIgnoreInSimilar(const FMeshBuffer& Buffer) const;` — Compare the mesh buffer with another one, but ignore internal data like generated vertex indices.
- L409 _public prototype_ `bool IsSimilar(const FMeshBufferSet& Other) const;` — Compare the mesh buffer with another one, but ignore internal data like generated vertex indices. Be aware this method compares the data byte by byte without checking if the data belong to the buffer components and could give false negatives if unset padding data is present.
- L416 _public prototype_ `bool IsSimilarRobust(const FMeshBufferSet& Other, bool bCompareUVs) const;` — Compare the mesh buffer with another one, but ignore internal data like generated vertex indices. This version compares the data component-wise, skipping any memory not specified in the buffer description.
- L422 _public prototype_ `void ResetBufferIndices();` — Change the buffer descriptions so that all buffer indices start at 0 and are in the same order than memory.
- L425 _public prototype_ `void UpdateOffsets(int32 BufferIndex);`
- L428 _public prototype_ `bool HasAnySemanticWithDifferentFormat(EMeshBufferSemantic Semantic, EMeshBufferFormat ExpectedFormat) const;` — Check that all channels of a specific semantic use the provided format.
- L431 _public prototype_ `bool IsDescriptor() const;` — Check if this buffer set is only a format descriptor, e.i. reports num elements larger than 0 but does not hold any data

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _namespace_ `namespace MemoryCounters` (scope `UE::Mutable::Private`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L87 _prototype_ `const FMeshBufferFormatData& GetMeshFormatData(EMeshBufferFormat Format);` (scope `UE::Mutable::Private`)
- L223 _prototype_ `ENUM_CLASS_FLAGS(EMeshBufferSetFlags);` (scope `UE::Mutable::Private`)
- L435 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FMeshBufferChannel);` (scope `UE::Mutable::Private`)
- L436 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FMeshBufferChannel);` (scope `UE::Mutable::Private`)
- L437 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EMeshBufferFormat);` (scope `UE::Mutable::Private`)
- L438 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EMeshBufferSemantic);` (scope `UE::Mutable::Private`)
- L439 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(EMeshBufferSetFlags);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MeshBufferUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _namespace_ `namespace MeshBufferUtils` (scope `UE::Mutable::Private`)
- L21 _variable_ `constexpr int32 MaxTexCordChannelCount = 4;` (scope `UE::Mutable::Private::MeshBufferUtils`) — Determines the max amount of channels that can inhabit a Texture Coordinate buffer.
- L28 _prototype_ `void SetupVertexPositionsBuffer(const int32& InCurrentVertexBuffer, FMeshBufferSet& OutTargetVertexBuffers);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Vertex Position Buffer of the Mutable mesh owning the provided MeshBufferSet @param InCurrentVertexBuffer Index of the Vertex Buffer being set up inside the OutTargetVertexBuffers. @param OutTargetVertexBuffers Mesh buffer to be set up.
- L35 _prototype_ `void SetupTangentBuffer(const int32& InCurrentVertexBuffer, FMeshBufferSet& OutTargetVertexBuffers);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Vertex Tangent Buffer of the Mutable mesh owning the provided MeshBufferSet @param InCurrentVertexBuffer Index of the Vertex Buffer being set up inside the OutTargetVertexBuffers. @param OutTargetVertexBuffers Mesh buffer to be set up.
- L44 _prototype_ `void SetupTexCoordinatesBuffer(const int32& InCurrentVertexBuffer, const int32& InChannelCount, bool bHighPrecision, FMeshBufferSet& OutTargetVertexBuffers, const int32* InTextureSemanticIndicesOverride = nullptr);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Vertex Texture Coordinates Buffer of the Mutable mesh owning the provided MeshBufferSet @param InCurrentVertexBuffer Index of the Vertex Buffer being set up inside the OutTargetVertexBuffers. @param InChannelCount Determines the amount of TexCord channels able to be added onto the buffer. @param OutTargetVertexBuffers Mesh buffer to be set up. @param InTextureSemanticIndicesOverride (Optional) If you are certain of the texture semantic indices that should be used populate this argument, if not, leave it as null
- L53 _prototype_ `void SetupSkinBuffer(const int32& InCurrentVertexBuffer, const int32& MaxBoneIndexTypeSizeBytes, const int32& MaxBoneWeightTypeSizeBytes, const int32& MaxNumBonesPerVertex, FMeshBufferSet& OutTargetVertexBuffers);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Vertex Skin Buffer of the Mutable mesh owning the provided MeshBufferSet @param InCurrentVertexBuffer Index of the Vertex Buffer being set up inside the OutTargetVertexBuffers. @param MaxBoneIndexTypeSizeBytes Maximum size of the vertex bone index type. @param MaxNumBonesPerVertex Amount of bone influences a vertex can have. @param OutTargetVertexBuffers Mesh buffer to be set up.
- L61 _prototype_ `void SetupVertexColorBuffer(const int32& InCurrentVertexBuffer, FMeshBufferSet& OutTargetVertexBuffers);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Vertex Color Buffer of the Mutable mesh owning the provided MeshBufferSet @param InCurrentVertexBuffer Index of the Vertex Buffer being set up inside the OutTargetVertexBuffers. @param OutTargetVertexBuffers Mesh buffer to be set up.
- L69 _prototype_ `void SetupIndexBuffer(FMeshBufferSet& OutTargetIndexBuffers, EMeshBufferFormat InFormat);` (scope `UE::Mutable::Private::MeshBufferUtils`) — Sets up all the channels that ought to be part of the Index Buffer of the Mutable mesh owning the provided MeshBufferSet @param OutTargetIndexBuffers Index buffer to be set up.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MeshPrivate.h` (Internal)


#### class `UE::Mutable::Private::UntypedMeshBufferIterator`  
`class UntypedMeshBufferIterator`  
_L93-286_
- L96 _public function_ `inline UntypedMeshBufferIterator()`
- L105 _public function_ `inline UntypedMeshBufferIterator ( FMeshBufferSet& BufferSet, EMeshBufferSemantic Semantic, int32 SemanticIndex = 0 )`
- L147 _public function_ `inline uint8* ptr() const`
- L152 _public function_ `inline void operator++()`
- L157 _public function_ `inline void operator++(int32)`
- L162 _public function_ `inline void operator+=( int32 c )`
- L167 _public function_ `inline UntypedMeshBufferIterator operator+(int32 c) const`
- L175 _public function_ `inline SIZE_T operator-( const UntypedMeshBufferIterator& Other ) const`
- L187 _public function_ `inline int32 GetElementSize() const`
- L192 _public function_ `inline EMeshBufferFormat GetFormat() const`
- L197 _public function_ `inline int32 GetComponents() const`
- L202 _public function_ `FVector4f GetAsVec4f() const`
- L214 _public function_ `FVector3f GetAsVec3f() const`
- L224 _public function_ `FVector3d GetAsVec3d() const`
- L234 _public function_ `FVector2f GetAsVec2f() const`
- L245 _public function_ `uint32 GetAsUINT32() const`
- L252 _public function_ `uint64 GetAsUINT64() const`
- L259 _public function_ `void SetFromUINT32(uint32 v)`
- L264 _public function_ `void SetFromVec3f(const FVector3f& v)`
- L272 _public function_ `void SetFromVec3d(const FVector3d& v)`
- L282 _protected member_ `int32 ElementSize;`
- L283 _protected member_ `uint8* Buffer;`
- L284 _protected member_ `EMeshBufferFormat Format;`
- L285 _protected member_ `int32 Components;`

#### class `UE::Mutable::Private::MeshBufferIterator`  
`template<EMeshBufferFormat FORMAT, class CTYPE, int32 COMPONENTS> class MeshBufferIterator : public UntypedMeshBufferIterator`  
_L296-362_
- inherits: `UntypedMeshBufferIterator`
- L299 _public function_ `inline MeshBufferIterator ( FMeshBufferSet& BufferSet, EMeshBufferSemantic Semantic, int32 SemanticIndex = 0 ) : UntypedMeshBufferIterator( BufferSet, Semantic, SemanticIndex )`
- L350 _public function_ `inline CTYPE* operator*()` — \TODO: Replace this with safer sized-typed access.
- L355 _public function_ `inline MeshBufferIterator<FORMAT,CTYPE,COMPONENTS> operator+(int32 c) const`

#### class `UE::Mutable::Private::UntypedMeshBufferIteratorConst`  
`class UntypedMeshBufferIteratorConst`  
_L368-555_
- L372 _public prototype_ `UntypedMeshBufferIteratorConst() = default;`
- L373 _public prototype_ `UntypedMeshBufferIteratorConst(UntypedMeshBufferIteratorConst&&) = default;`
- L374 _public prototype_ `UntypedMeshBufferIteratorConst(const UntypedMeshBufferIteratorConst&) = default;`
- L375 _public prototype_ `UntypedMeshBufferIteratorConst& operator=(UntypedMeshBufferIteratorConst&&) = default;`
- L376 _public prototype_ `UntypedMeshBufferIteratorConst& operator=(const UntypedMeshBufferIteratorConst&) = default;`
- L378 _public function_ `inline UntypedMeshBufferIteratorConst ( const FMeshBufferSet& BufferSet, EMeshBufferSemantic Semantic, int32 SemanticIndex = 0 )`
- L420 _public function_ `inline const uint8* ptr() const`
- L425 _public function_ `inline void operator++()`
- L430 _public function_ `inline void operator++(int32)`
- L435 _public function_ `inline void operator+=( int32 c )`
- L440 _public function_ `inline SIZE_T operator-( const UntypedMeshBufferIterator& Other ) const`
- L452 _public function_ `inline SIZE_T operator-( const UntypedMeshBufferIteratorConst& Other ) const`
- L464 _public function_ `inline int32 GetElementSize() const`
- L469 _public function_ `inline EMeshBufferFormat GetFormat() const`
- L474 _public function_ `inline int32 GetComponents() const`
- L479 _public function_ `FVector4f GetAsVec4f() const`
- L489 _public function_ `FVector3f GetAsVec3f() const`
- L499 _public function_ `FVector3d GetAsVec3d() const`
- L509 _public function_ `FVector2f GetAsVec2f() const`
- L520 _public function_ `uint32 GetAsUINT32() const`
- L527 _public function_ `uint64 GetAsUINT64() const`
- L534 _public function_ `void GetAsInt32Vec(int32* Data, int32 Count) const`
- L542 _public function_ `inline UntypedMeshBufferIteratorConst operator+(int32 c) const`
- L551 _protected member_ `int32 ElementSize = 0;`
- L552 _protected member_ `const uint8* Buffer = nullptr;`
- L553 _protected member_ `EMeshBufferFormat Format = EMeshBufferFormat::None;`
- L554 _protected member_ `int32 Components = 0;`

#### class `UE::Mutable::Private::MeshBufferIteratorConst`  
`template<EMeshBufferFormat FORMAT, class CTYPE, int32 COMPONENTS> class MeshBufferIteratorConst : public UntypedMeshBufferIteratorConst`  
_L564-635_
- inherits: `UntypedMeshBufferIteratorConst`
- L568 _public function_ `inline MeshBufferIteratorConst()`
- L573 _public function_ `inline MeshBufferIteratorConst ( const FMeshBufferSet& BufferSet, EMeshBufferSemantic Semantic, int32 SemanticIndex = 0 ) : UntypedMeshBufferIteratorConst( BufferSet, Semantic, SemanticIndex )`
- L623 _public function_ `inline const CTYPE* operator*() const`
- L628 _public function_ `inline MeshBufferIteratorConst<FORMAT,CTYPE,COMPONENTS> operator+(int32 c) const`

#### class `UE::Mutable::Private::MeshVertexIdIteratorConst`  
`class MeshVertexIdIteratorConst`  
_L641-742_
- desc: Iterator for vertex Ids. The lifecycle of the iterator cannot exceed the mesh lifecycle.
- L646 _private member_ `int32 CurrentIdIndex = 0;` — Current Id that the iterator is pointing at.
- L647 _private member_ `int32 NumVertices = 0;`
- L649 _private member_ `uint64 MeshIDPrefix = 0;`
- L652 _private member_ `UntypedMeshBufferIteratorConst BufferIterator;` — Buffer iterator in case there is an actual Id BufferIndex.
- L656 _public function_ `inline MeshVertexIdIteratorConst()`
- L660 _public function_ `inline MeshVertexIdIteratorConst( const FMesh* InMesh )`
- L672 _public function_ `inline void operator++()`
- L682 _public function_ `inline void operator++(int32)`
- L692 _public function_ `inline void operator+=(int32 c)`
- L702 _public function_ `inline MeshVertexIdIteratorConst operator+(int32 c) const`
- L709 _public function_ `bool IsValid() const`
- L714 _public function_ `uint64 Get() const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _function_ `inline void GetMeshBuf ( FMesh* Mesh, EMeshBufferSemantic Semantic, EMeshBufferFormat expectedFormat, int32 expectedComponents, uint8*& pBuf, int32& elemSize )` (scope `UE::Mutable::Private`)
- L53 _function_ `inline void GetMeshBuf ( const FMesh* Mesh, EMeshBufferSemantic Semantic, EMeshBufferFormat expectedFormat, int32 expectedComponents, const uint8*& pBuf, int32& elemSize )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Model.h` (Internal)


#### struct `UE::Mutable::Private::FConstantResourceIndex`  
`struct FConstantResourceIndex`  
_L43-48_
- L45 _public member_ `uint32 Index : 31;`
- L47 _public member_ `uint32 Streamable : 1;` — This may mean that the resource needs to be looked up on a different array.

#### enum `UE::Mutable::Private::ERomDataType`  
`enum class ERomDataType : uint32`  
_L54-58_
- desc: This is encoded with minimal bits. Make sure to review all uses if extended.
- L56 _public enumerator_ `Image = 0`
- L57 _public enumerator_ `Mesh = 1`

#### struct `UE::Mutable::Private::FRomDataRuntime`  
`struct FRomDataRuntime`  
_L63-77_
- desc: Data stored for a rom even if it is not loaded. This struct is size-sensitive since there may be many roms and it is always loaded in memory when a CO is.
- L66 _public member_ `uint32 Size : 30;` — Size of the rom
- L69 _public member_ `uint32 ResourceType : 1;` — Index of the resource in its type-specific array. See ERomDataType.
- L72 _public member_ `uint32 IsHighRes : 1;` — Properties of the rom data.

#### struct `UE::Mutable::Private::FRomDataCompile`  
`struct FRomDataCompile`  
_L83-87_
- L86 _public member_ `uint32 SourceId;` — ID used to identify the origin of this data and used for grouping.

#### struct `UE::Mutable::Private::FImageLODRange`  
`struct FImageLODRange`  
_L100-109_
- L102 _public member_ `int32 FirstIndex = 0;`
- L103 _public member_ `uint16 ImageSizeX = 0;`
- L104 _public member_ `uint16 ImageSizeY = 0;`
- L105 _public member_ `uint8 LODCount = 0;`
- L106 _public member_ `uint8 NumLODsInTail = 0;`
- L107 _public member_ `uint8 Flags = 0;`
- L108 _public member_ `EImageFormat ImageFormat = EImageFormat::None;`

#### struct `UE::Mutable::Private::FMeshContentRange`  
`struct FMeshContentRange`  
_L112-155_
- L114 _public member_ `static constexpr uint32 FirstIndexMaxBits = 24;`
- L115 _public member_ `static constexpr uint32 ContentFlagsMaxBits = 32 - FirstIndexMaxBits;`
- L116 _public member_ `static constexpr uint32 FirstIndexBitMask = (1 << FirstIndexMaxBits) - 1;`
- L123 _public member_ `uint32 FirstIndex_ContentFlags = 0;` — NOTE: Bitfields layout can be implementation defined, here we want consistency across all compilers so that the struct can be POD serializable.
- L124 _public member_ `uint32 MeshIDPrefix = 0;`
- L126 _public function_ `FORCEINLINE EMeshContentFlags GetContentFlags() const`
- L133 _public function_ `FORCEINLINE uint32 GetFirstIndex() const`
- L138 _public function_ `FORCEINLINE void SetContentFlags(EMeshContentFlags ContentFlags)`
- L147 _public function_ `FORCEINLINE void SetFirstIndex(uint32 FirstIndex)`

#### struct `UE::Mutable::Private::FProgram`  
`struct FProgram`  
_L160-414_
- L162 _public prototype_ `FProgram();`
- L207 _public member_ `int32 NumOps = 0;`
- L208 _public member_ `TArray<FOperation::ADDRESS> OperationDebugData;`
- L211 _public member_ `TArray<uint8> ByteCode;` — Byte-coded representation of the program, using variable-sized op data.
- L214 _public member_ `TArray<FState> States;`
- L217 _public member_ `TArray<FRomDataRuntime> Roms;` — Data for every rom required in-game.
- L220 _public member_ `TArray<FRomDataCompile> RomsCompileData;` — Data for every rom required at compile-time. It is empty in cooked data.
- L225 _public member_ `TArray<TManagedPtr<const FImage>> ConstantImageLODsPermanent;` — Constant image mip data is split in 2 sets: ConstantImageLODsPermanent constains data that is always loaded. Index with FConstantResourceIndex::Index, when Streamable is 0.
- L228 _public member_ `TArray<FConstantResourceIndex> ConstantImageLODIndices;` — Constant image mip chain indices: ranges in this array are defined in FImageLODRange and the indices here refer to ConstantImageLODs.
- L231 _public member_ `TArray<FImageLODRange> ConstantImages;` — Constant image data.
- L234 _public member_ `TArray<FConstantResourceIndex> ConstantMeshContentIndices;` — Constant mesh content indices: ranges in this array are defined in FMeshContentRange and the indices here refer to ConstantMeshes.
- L237 _public member_ `TArray<FMeshContentRange> ConstantMeshes;` — Constant mesh data
- L242 _public member_ `TArray<TManagedPtr<const FMesh>> ConstantMeshesPermanent;` — Constant mesh data is split in 2 sets: ConstantMeshesPermanent constains data that is always loaded. Index with FConstantResourceIndex::Index, when Streamable is 0.
- L245 _public member_ `TArray<FString> ConstantStrings;` — Constant string data
- L248 _public member_ `TArray<TArray<uint32>> ConstantUInt32Lists;`
- L251 _public member_ `TArray<TArray<int32>> ConstantInt32Lists;`
- L254 _public member_ `TArray<TArray<uint64>> ConstantUInt64Lists;`
- L257 _public member_ `TArray<TArray<float>> ConstantFloatLists;`
- L260 _public member_ `TArray<TArray<bool>> ConstantBoolLists;`
- L263 _public member_ `TArray<TManagedPtr<const FLayout>> ConstantLayouts;` — Constant layout data
- L266 _public member_ `TArray<TManagedPtr<const FInstancedStruct>> ConstantInstancedStructs;` — Constant Instanced Struct
- L269 _public member_ `TArray<FProjector> ConstantProjectors;` — Constant projectors
- L272 _public member_ `TArray<FMatrix44f> ConstantMatrices;` — Constant matrices, usually used for transforms
- L275 _public member_ `TArray<FShape> ConstantShapes;` — Constant shapes
- L278 _public member_ `TArray<FRichCurve> ConstantCurves;` — Constant curves
- L281 _public member_ `TArray<TManagedPtr<const FSkeleton>> ConstantSkeletons;` — Constant skeletons
- L284 _public member_ `TArray<TManagedPtr<const FPhysicsBody>> ConstantPhysicsBodies;` — Constant Physics Bodies
- L288 _public member_ `TArray<FParameterDesc> Parameters;` — The value stored here is the default value.
- L291 _public member_ `TArray<FRangeDesc> Ranges;` — Ranges for iteration of the model operations.
- L298 _public member_ `TArray<TArray<uint16>> ParameterLists;` — List of parameter lists. These are used in several places, like storing the pregenerated list of parameters influencing a resource. The parameter lists are sorted.
- L301 _public member_ `TMap<FOperation::ADDRESS, int32> RelevantParameterList;` — Given an instruction, parameters that are in the subtree.
- L304 _public member_ `TArray<TManagedPtr<const FMaterial>> ConstantMaterials;` — Constant Material Data
- L307 _public member_ `TMap<uint32, FName> ConstantNames;` — Constant FNames
- L310 _public member_ `TMap<uint32, FMeshSocket> ConstantSockets;` — Constant Mesh Sockets
- L313 _public member_ `TSharedPtr<const IExternalOperationProvider> ExternalOperationProvider;`
- L320 _public member_ `bool bIsValid = true;` — State of the program. True unless the streamed resources were destroyed, which could happen in the editor after recompiling the CO.
- L323 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L325 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L327 _public prototype_ `void PostLoad();`
- L330 _public prototype_ `void LogHistogram() const;` — Debug method that logs the top used instruction types.
- L332 _public prototype_ `uint32 GetRomSize(int32 Index) const;`
- L334 _public prototype_ `int32 GetRomCount() const;`
- L337 _public prototype_ `uint32 GetRomSourceId(int32 Index) const;`
- L340 _public prototype_ `ERomDataType GetRomDataType(int32 Index) const;`
- L342 _public prototype_ `bool IsRomHighRes(int32 Index) const;`
- L348 _public prototype_ `int32 GetConstantImageRomId(int32 ConstantImageIndex, int32 LODIndex) const;` — Returns the ConstantImageIndex LODIndex rom id. In case ConstantImageIndex does not have LODIndex returns -1.
- L351 _public prototype_ `FOperation::ADDRESS AddConstant(const TManagedPtr<const FLayout>& Layout);`
- L353 _public prototype_ `FOperation::ADDRESS AddConstant(const TManagedPtr<const FSkeleton>& Skeleton);`
- L355 _public prototype_ `FOperation::ADDRESS AddConstant(const TManagedPtr<const FPhysicsBody>& PhysicsBody);`
- L357 _public prototype_ `uint32 AddConstant(const FMeshSocket& Socket);`
- L359 _public prototype_ `FOperation::CONSTANT_LIST_UINT32 AddConstant(const TArray<FMeshSocket>& Sockets);`
- L361 _public prototype_ `FOperation::CONSTANT_STRING AddConstant(const FString& Str);`
- L363 _public prototype_ `FOperation::ADDRESS AddConstant(const TArray<uint32>& UInt32List);`
- L365 _public prototype_ `FOperation::ADDRESS AddConstant(const TArray<int32>& Int32List);`
- L367 _public prototype_ `FOperation::CONSTANT_LIST_UINT64 AddConstant(const TArray<uint64>& UInt64List);`
- L369 _public prototype_ `FOperation::ADDRESS AddConstant(const TArray<FString>& StringList);`
- L371 _public prototype_ `FOperation::CONSTANT_NAME AddConstant(const FName& InName);`
- L373 _public prototype_ `FOperation::CONSTANT_LIST_UINT32 AddConstant(const TArray<FName>& NameList);`
- L375 _public prototype_ `FOperation::CONSTANT_MATRIX AddConstant(const FMatrix44f& Constant);`
- L377 _public prototype_ `FOperation::CONSTANT_SHAPE AddConstant(const FShape& Constant);`
- L379 _public prototype_ `FOperation::ADDRESS AddConstant(const FProjector& Constant);`
- L381 _public prototype_ `FOperation::ADDRESS AddConstant(const FRichCurve& Constant);`
- L383 _public prototype_ `FOperation::ADDRESS AddConstant(const TManagedPtr<const FMaterial>& Material);`
- L385 _public prototype_ `FOperation::ADDRESS AddConstant(const TArray<float>& FloatList);`
- L387 _public prototype_ `FOperation::ADDRESS AddConstant(const TArray<bool>& BoolList);`
- L391 _public prototype_ `EOpType GetOpType(FOperation::ADDRESS At) const;`
- L394 _public function_ `template<typename ARGS> ARGS GetOpArgs(FOperation::ADDRESS Address) const`
- L405 _public function_ `template<typename ARGS> void SetOpArgs(FOperation::ADDRESS Address, const ARGS& Args)`
- L411 _public prototype_ `const uint8* GetOpArgsPointer(FOperation::ADDRESS Address) const;`
- L413 _public prototype_ `uint8* GetOpArgsPointer(FOperation::ADDRESS Address);`

#### struct `UE::Mutable::Private::FProgram::FState`  
`struct FState`  
_L164-205_
- L167 _public member_ `FString Name;` — Name of the state
- L170 _public member_ `FOperation::ADDRESS Root = 0;` — First instruction of the full build of an instance in this state
- L176 _public member_ `TArray<int> m_runtimeParameters;` — List of parameters index (to FProgram::Parameters) of the runtime parameters of this state.
- L179 _public member_ `TArray<FOperation::ADDRESS> m_updateCache;` — List of instructions that need to be cached to efficiently update this state
- L187 _public member_ `TArray< TPair<FOperation::ADDRESS,uint64> > m_dynamicResources;` — List of root instructions for the dynamic resources that depend on the runtime parameters of this state, with a mask of relevant runtime parameters. The mask has a bit on for every runtime parameter in the m_runtimeParameters array. The uint64 is linked to MUTABLE_MAX_RUNTIME_PARAMETERS_PER_STATE
- L190 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L193 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L198 _public prototype_ `uint64 IsDynamic(FOperation::ADDRESS At) const;` — Returns the mask of parameters (from the runtime parameter list of this state) including the parameters that are relevant for the dynamic resource at the given address.
- L201 _public prototype_ `bool IsUpdateCache(FOperation::ADDRESS at) const;`
- L204 _public prototype_ `void AddUpdateCache(FOperation::ADDRESS At);`

#### class `UE::Mutable::Private::FModel`  
`class FModel`  
_L421-916_
- desc: A Model represents a customisable object with any number of parameters. When values are given to the parameters, specific Instances can be built, which hold the built application-usable data.
- L424 _public prototype_ `FModel();`
- L426 _public prototype_ `static void Serialise(const FModel*, FOutputArchive&);`
- L427 _public prototype_ `static TSharedPtr<FModel> StaticUnserialise(FInputArchive&);`
- L429 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L431 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L438 _public prototype_ `static void Serialise(FModel* Model, FModelWriter& Streamer, bool bDropData = false);` — Special serialise operation that serialises the data in separate "files". An object with the ModelStreamer interface is responsible of storing this data and providing the "file" concept. If bDropData is set to true, the rom data will be freed as it is serialized.
- L442 _public prototype_ `bool HasExternalData() const;` — Return true if the model has external data in other files. This kind of models will require data streaming when used.
- L447 _public prototype_ `bool IsValid() const;` — Return true unless the streamed resources were destroyed, which could happen in the editor after recompiling the CO.
- L451 _public prototype_ `void Invalidate();` — Invalidate the Model. Compiling a compiled CO will invalidate the model kept by previously generated resources, like streamed textures.
- L461 _public prototype_ `static TSharedPtr<FParameters> NewParameters(TSharedPtr<const FModel> Model, const FParameters* OldParameters = nullptr);` — Create a set of new parameters of the model with the default values. If old parameters are provided, they will be reused when possible instead of the default values.
- L464 _public prototype_ `bool IsParameterMultidimensional(int32 ParameterIndex) const;` — Return true if the parameter is multi-dimensional
- L467 _public prototype_ `int32 GetStateCount() const;` — Get the number of states in the model.
- L470 _public prototype_ `const FString& GetStateName( int32 StateIndex ) const;` — Get a state name by state index from 0 to GetStateCount-1
- L473 _public prototype_ `int32 FindState( const FString& Name ) const;` — Find a state index by state name
- L476 _public prototype_ `int32 GetStateParameterCount( int32 StateIndex ) const;` — Get the number of parameters available in a particular state.
- L480 _public prototype_ `int32 GetStateParameterIndex( int32 StateIndex, int32 ParamIndex ) const;` — Get the index of one of the parameters in the given state. The index refers to the parameters in a FParameters object obtained from this model with NewParameters.
- L485 _public prototype_ `bool GetBoolDefaultValue(int32 Index) const;` — Return the default value of a boolean parameter. \pre The parameter specified by index is a T_BOOL. \param Index Index of the parameter from 0 to GetCount()-1
- L490 _public prototype_ `int32 GetIntDefaultValue(int32 Index) const;` — Return the default value of a integer parameter. \pre The parameter specified by index is a T_INT. \param Index Index of the parameter from 0 to GetCount()-1
- L495 _public prototype_ `float GetFloatDefaultValue(int32 Index) const;` — Return the default value of a float parameter. \pre The parameter specified by index is a T_FLOAT. \param Index Index of the parameter from 0 to GetCount()-1
- L501 _public prototype_ `void GetColorDefaultValue(int32 Index, FVector4f& OutValue) const;` — Return the default value of a color parameter. \pre The parameter specified by index is a T_FLOAT. \param Index Index of the parameter from 0 to GetCount()-1 \param R,G,B Pointers to values where every resulting color channel will be stored
- L506 _public prototype_ `FMatrix44f GetMatrixDefaultValue(int32 Index) const;` — Return the default value of a color parameter. \pre The parameter specified by index is a T_FLOAT. \param Index Index of the parameter from 0 to GetCount()-1
- L518 _public prototype_ `void GetProjectorDefaultValue(int32 Index, EProjectorType* OutProjectionType, FVector3f* OutPos, FVector3f* OutDir, FVector3f* OutUp, FVector3f* OutScale, float* OutProjectionAngle) const;` — Return the default value of a projector parameter, as a 4x4 matrix. The matrix is supposed to be a linear transform in column-major. \pre The parameter specified by index is a T_PROJECTOR. \param Index Index of the parameter from 0 to GetCount()-1 \param OutPos Pointer to where the object-space position coordinates of the projector will be stored. \param OutDir Pointer to where the object-space direction vector of the projector will be stored. \param OutUp Pointer to where the object-space vertically up direction vector of the projector will be stored. This controls the "roll" angle of the projector. \param OutScale Pointer to the projector-space scaling of the projector.
- L524 _public function_ `template <typename CreateImageFunc> void GetConstant(uint32 ConstantIndex, TManagedPtr<const FImage>& Result, int32 MipsToSkip, const TFunction<TManagedPtr<const FImage>(int32)>&& RomsStreamed, const CreateImageFunc&& CreateImage) const` — Get a constant image, assuming at least some mips are loaded. The image constant will be composed with lodaded mips if necessary. @param RomsStreamed Given a rom index, return the  future of the streamed rom.
- L693 _public function_ `template<class CreateMeshFunc> void GetConstant( uint32 MeshConstantIndex, int32 SkeletonConstantIndex, const TPassthroughObjectPtr<UClothingAssetBase>& ClothAsset, TManagedPtr<const FMesh>& OutMesh, EMeshContentFlags FilterContentFlags, const TFunction<TManagedPtr<const FMesh>(int32)>&& RomsStreamed, CreateMeshFunc&& CreateMesh) const` — @param RomsStreamed Given a rom index, return the  future of the streamed rom.
- L901 _public function_ `FProgram& GetProgram()`
- L906 _public function_ `const FProgram& GetProgram() const`
- L912 _private member_ `FProgram Program;`
- L915 _public member_ `FRomManager RomManager;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L26 _macro_ `#define MUTABLE_MAX_RUNTIME_PARAMETERS_PER_STATE 65`
- L27 _macro_ `#define MUTABLE_GROW_BORDER_VALUE 2`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Mutable` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L38 _variable_ `constexpr bool DebugRom = false;` (scope `UE::Mutable::Private`) — Used to debug and log.
- L39 _variable_ `constexpr bool DebugRomAll = false;` (scope `UE::Mutable::Private`)
- L40 _variable_ `constexpr int32 DebugRomIndex = 44;` (scope `UE::Mutable::Private`)
- L41 _variable_ `constexpr int32 DebugImageIndex = 9;` (scope `UE::Mutable::Private`)
- L50 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FConstantResourceIndex);` (scope `UE::Mutable::Private`)
- L81 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FRomDataRuntime);` (scope `UE::Mutable::Private`)
- L88 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FRomDataCompile);` (scope `UE::Mutable::Private`)
- L92 _function_ `template<typename DATA> inline void AppendCode(TArray<uint8>& ByteCode, const DATA& Data)` (scope `UE::Mutable::Private`)
- L110 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FImageLODRange);` (scope `UE::Mutable::Private`)
- L157 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FMeshContentRange);` (scope `UE::Mutable::Private`)
- L534 _function_ `` (scope `UE::Mutable::Private::FModel::GetConstant`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MutableEditorLogger.h` (Internal)


#### class `IMutableEditorLogger`  
`class IMutableEditorLogger`  
_L8-19_
- desc: Class used to log messages from CO compilations and COI updates to the open editor.
- L12 _public prototype_ `virtual ~IMutableEditorLogger() = default;`
- L15 _public prototype_ `virtual bool LogMessage(TSharedRef<FTokenizedMessage> Message) = 0;` — Logs the Message
- L18 _public prototype_ `virtual void ClearLogMessageList() = 0;` — Clears all the visible Logs

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MutableMath.h` (Internal)


#### class `UE::Mutable::Private::box`  
`template <class VECTOR> class box`  
_L96-261_
- L100 _public member_ `VECTOR min;`
- L101 _public member_ `VECTOR size;`
- L105 _public function_ `box() : min(0), size(0)`
- L108 _public function_ `static box<VECTOR> FromMinSize(VECTOR m, VECTOR s)`
- L117 _public function_ `inline bool Contains(const VECTOR& v) const`
- L123 _public function_ `inline bool ContainsInclusive(const VECTOR& v) const`
- L129 _public function_ `inline bool Contains(const box<VECTOR>& v) const`
- L137 _public function_ `inline bool Intersects(const box<VECTOR>& other) const`
- L153 _public function_ `inline bool IntersectsExclusive(const box<VECTOR>& other) const`
- L169 _public function_ `inline box<FIntVector2> Intersect2i(const box<FIntVector2>& other) const`
- L184 _public function_ `VECTOR Homogenize( const VECTOR& v ) const`
- L190 _public function_ `inline void Bound(const VECTOR& v)`
- L207 _public function_ `inline void Bound3(const VECTOR& v)`
- L225 _public function_ `inline void Bound(const box<VECTOR>& other)`
- L232 _public function_ `inline bool IsEmpty() const`
- L240 _public function_ `inline bool operator<( const box<VECTOR>& other ) const`
- L255 _public function_ `inline bool operator==(const box<VECTOR>& other) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `template<class VECTOR> inline int32 GetDim()` (scope `UE::Mutable::Private`)
- L21 _function_ `template<> inline int32 GetDim<FVector2f>()` (scope `UE::Mutable::Private`)
- L27 _function_ `template<> inline int32 GetDim<FVector3f>()` (scope `UE::Mutable::Private`)
- L33 _function_ `template<> inline int32 GetDim<FIntVector2>()` (scope `UE::Mutable::Private`)
- L39 _function_ `template<> inline int32 GetDim<UE::Math::TIntVector2<uint16>>()` (scope `UE::Mutable::Private`)
- L45 _function_ `template<class VECTOR> inline bool AllGreaterOrEqualThan(const VECTOR& v0, const VECTOR& v1)` (scope `UE::Mutable::Private`)
- L51 _function_ `template<> inline bool AllGreaterOrEqualThan<FIntVector2>(const FIntVector2& v0, const FIntVector2& v1)` (scope `UE::Mutable::Private`)
- L57 _function_ `template<class VECTOR> inline bool AllSmallerThan(const VECTOR& v0, const VECTOR& v1)` (scope `UE::Mutable::Private`)
- L63 _function_ `template<> inline bool AllSmallerThan<FIntVector2>(const FIntVector2& v0, const FIntVector2& v1)` (scope `UE::Mutable::Private`)
- L69 _function_ `template<class VECTOR> inline bool AllSmallerOrEqualThan(const VECTOR& v0, const VECTOR& v1)` (scope `UE::Mutable::Private`)
- L75 _function_ `template<> inline bool AllSmallerOrEqualThan<FIntVector2>(const FIntVector2& v0, const FIntVector2& v1)` (scope `UE::Mutable::Private`)
- L81 _function_ `inline void ConvertLinearColorToSRGB(FVector4f& Color)` (scope `UE::Mutable::Private`) — Apply a Linear to sRGB color transformation on a given color vector.
- L85 _function_ `` (scope `UE::Mutable::Private::ConvertLinearColorToSRGB`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MutableRuntimeModule.h` (Internal)


#### class `FMutableRuntimeModule`  
`class FMutableRuntimeModule : public IModuleInterface`  
_L14-22_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L20 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMutableCore, Log, All);`

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MutableString.h` (Internal)


#### class `UE::Mutable::Private::String`  
`class String : public FResource`  
_L18-52_
- inherits: `FResource`
- desc: Container for text string data.
- L26 _public prototype_ `String(const FString&);`
- L29 _public prototype_ `TSharedPtr<String> Clone() const;` — Deep clone this string.
- L32 _public prototype_ `int32 GetDataSize() const override;` — Resource interface
- L39 _public prototype_ `const FString& GetValue() const;` — Get the string data.
- L44 _public member_ `FString Value;`
- L47 _public function_ `inline bool operator==(const String& o) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/MutableTrace.h` (Internal)


#### class `FMutableScopeTimer`  
`class FMutableScopeTimer`  
_L19-35_
- desc: Simple class that saves the time the scope is alive in the given location.
- L22 _public function_ `FMutableScopeTimer(double& InResult) : Result(InResult)`
- L27 _public function_ `~FMutableScopeTimer()`
- L33 _private member_ `double StartTime = 0.0;`
- L34 _private member_ `double& Result;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define MUTABLE_CPUPROFILER_SCOPE(Name) \` — Custom Mutable profiler scope.
- L14 _macro_ `#define MUTABLE_EDITOR_CPUPROFILER_SCOPE(Name) \` — Custom Mutable profiler scope.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/OpImageGrow.h` (Internal)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _function_ `inline void ImageGrow( FImage* pImage )` (scope `UE::Mutable::Private`)
- L68 _function_ `inline void ImageGrow( FImage* pImage, const FImage* pMask )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/OpImageProject.h` (Internal)


#### struct `UE::Mutable::Private::FScratchImageProject`  
`struct FScratchImageProject`  
_L16-20_
- L18 _public member_ `TArray<RasterVertex<4>> Vertices;`
- L19 _public member_ `TArray<uint8> CulledVertex;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L22 _prototype_ `extern void ImageRasterProjectedPlanar( const FMesh* pMesh, FImage* pTargetImage, const FImage* pSource, const FImage* pMask, bool bIsRGBFadingEnabled, bool bIsAlphaFadingEnabled, ESamplingMethod SamplingMethod, float FadeStart, float FadeEnd, float MipInterpolationFactor, int Layout, uint64 BlockId, UE::Math::TIntVector2<uint16> CropMin, UE::Math::TIntVector2<uint16> UncroppedSize, FScratchImageProject* scratch, bool bUseVectorImplementation = false);` (scope `UE::Mutable::Private`)
- L31 _prototype_ `extern void ImageRasterProjectedCylindrical( const FMesh* pMesh, FImage* pTargetImage, const FImage* pSource, const FImage* pMask, bool bIsRGBFadingEnabled, bool bIsAlphaFadingEnabled, ESamplingMethod SamplingMethod, float FadeStart, float FadeEnd, float MipInterpolationFactor, int32 Layout, float ProjectionAngle, UE::Math::TIntVector2<uint16> CropMin, UE::Math::TIntVector2<uint16> UncroppedSize, FScratchImageProject* Scratch, bool bUseVectorImplementation = false);` (scope `UE::Mutable::Private`)
- L41 _prototype_ `extern void ImageRasterProjectedWrapping( const FMesh* pMesh, FImage* pTargetImage, const FImage* pSource, const FImage* pMask, bool bIsRGBFadingEnabled, bool bIsAlphaFadingEnabled, ESamplingMethod SamplingMethod, float FadeStart, float FadeEnd, float MipInterpolationFactor, int32 Layout, uint64 BlockId, UE::Math::TIntVector2<uint16> CropMin, UE::Math::TIntVector2<uint16> UncroppedSize, FScratchImageProject* Scratch, bool bUseVectorImplementation = false);` (scope `UE::Mutable::Private`)
- L50 _prototype_ `extern float ComputeProjectedFootprintBestMip( const FMesh* pMesh, const FProjector& Projector, const FVector2f& TargetSize, const FVector2f& SourceSize);` (scope `UE::Mutable::Private`)
- L53 _prototype_ `extern void MeshProject(FMesh* Result, const FMesh* pMesh, const FProjector& Projector, int32 LayoutIndex, bool& bOutSuccess);` (scope `UE::Mutable::Private`)
- L55 _prototype_ `extern void CreateMeshOptimisedForProjection(FMesh* Result, int32 LayoutIndex);` (scope `UE::Mutable::Private`)
- L56 _prototype_ `extern void CreateMeshOptimisedForWrappingProjection(FMesh* Result, int32 LayoutIndex);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/OpMeshFormat.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _prototype_ `extern void MeshFormat ( FMesh* Result, const FMesh* Source, const FMesh* Format, bool bKeepSystemBuffers, bool bFormatVertices, bool bFormatIndices, bool bIgnoreMissingChannels, bool& bOutSuccess );` (scope `UE::Mutable::Private`) — Convert a mesh format into another one. Slow implementation, but it should never happen at run-time \param keepSystemBuffers Will keep the internal system buffers even if they are not in the original format. If they are, they will be duplicated, so be careful.
- L32 _prototype_ `void MeshFormatBuffer( const FMeshBufferSet& Source, FMeshBuffer& Result, int32 ResultElementOffset, bool bHasSpecialSemantics, uint32 IDPrefix);` (scope `UE::Mutable::Private`) — Fill a mesh buffer in Result (with an optional offset) with the current data in Source but keeping the format already in the Result.
- L35 _prototype_ `void MeshOptimizeBuffers( FMesh* );` (scope `UE::Mutable::Private`) — Try to reduce the mesh size by reducing the component count, and data type of some buffers.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/OpMeshMerge.h` (Internal)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _prototype_ `void MeshMerge(FMesh* Result, const TManagedPtr<const FMesh>& First, const TManagedPtr<const FMesh>& Second, bool bMergeSurfaces);` (scope `UE::Mutable::Private`) — Merge two meshes into one new mesh
- L19 _prototype_ `void MergeSkeletons(FSkeleton& Base, const FSkeleton& Other, TArray<int32>& OutRemappedOtherBoneIndices);` (scope `UE::Mutable::Private`) — Merge two skeletons, OutRemappedOtherBoneIndices containts the map from bone in Other to bone in Base
- L22 _prototype_ `void MergeLODMeshesForConversion(FMesh* Result, TArray<TManagedPtr<const FMesh>>& Meshes, bool bIsInitialGeneration);` (scope `UE::Mutable::Private`) — Merge multiple meshes into one new mesh.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/OpMeshPrepareLayout.h` (Internal)


#### struct `UE::Mutable::Private::FMutableLayoutClassifyResult`  
`struct FMutableLayoutClassifyResult`  
_L30-43_
- desc: Store the result of a layout vertex classify operation.
- L33 _public member_ `TArray<FVector2f> TexCoords;` — The tex coords of every mesh vertex. They could be modified during the classify operation due to forced block clamping.
- L39 _public member_ `TArray<uint16> LayoutData;` — A block index for every mesh vertex. These are indices in the array of blocks of the given FLayout object to use to classify. It could be NullBlockId if it didn't belong to a block.
- L42 _public member_ `static constexpr uint16 NullBlockId = TNumericLimits<uint16>::Max();` — Id of unassigned blocks.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _prototype_ `void MeshPrepareLayout( FMesh& Mesh, const FLayout& InLayout, int32 LayoutChannel, bool bNormalizeUVs, bool bClampUVIslands, bool bEnsureAllVerticesHaveLayoutBlock, bool bUseAbsoluteBlockIds );` (scope `UE::Mutable::Private`) — Modify the mesh to use the given layout. It will be added to the mesh and additional mesh buffers created for the layout block ids. It may also modify the UVs to clamp them to the blocks if necessary.
- L51 _prototype_ `bool ClassifyMeshVerticesInLayout( const FMesh& Mesh, const FLayout& InLayout, int32 LayoutChannel, bool bNormalizeUVs, bool bClampUVIslands, FMutableLayoutClassifyResult& OutResult );` (scope `UE::Mutable::Private`) — Assign a layout block to every vertex in the mesh if possible. If a vertex cannot be assigned, it will remain as NullBlockId. Vertex UVs for the given layout will be copied and may be modified in the output struct if they needed to be clamped to fit in a block, but the mesh won't be modified by this method.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Operations.h` (Internal)


#### enum `UE::Mutable::Private::EOpType`  
`enum class EOpType : uint8`  
_L29-594_
- desc: Operation type enum. All operations gerenrating a specific type **MUST** be contiguous and be between its TYPE_RANGE_BEGIN and TYPE_RANGE_END
- L32 _public enumerator_ `NONE` — No operation.
- L39 _public enumerator_ `BO_CONSTANT` — Boolean constant
- L41 _public enumerator_ `BO_RANGE_BEGIN = BO_CONSTANT`
- L44 _public enumerator_ `BO_PARAMETER` — Boolean parameter
- L47 _public enumerator_ `BO_EQUAL_INT_CONST` — Compare an integerexpression with an integer constant
- L50 _public enumerator_ `BO_AND` — Logical and
- L53 _public enumerator_ `BO_OR` — Logical or
- L56 _public enumerator_ `BO_NOT` — Logical not
- L64 _public enumerator_ `NU_CONSTANT` — Constant value
- L66 _public enumerator_ `BO_RANGE_END = NU_CONSTANT`
- L67 _public enumerator_ `NU_RANGE_BEGIN = BO_RANGE_END`
- L70 _public enumerator_ `NU_PARAMETER` — User parameter
- L73 _public enumerator_ `NU_CONDITIONAL` — Select one value or the other depending on a boolean input
- L76 _public enumerator_ `NU_SWITCH` — Select one of several values depending on an int input
- L84 _public enumerator_ `SC_CONSTANT` — Constant value
- L86 _public enumerator_ `NU_RANGE_END = SC_CONSTANT`
- L87 _public enumerator_ `SC_RANGE_BEGIN = NU_RANGE_END`
- L90 _public enumerator_ `SC_PARAMETER` — User parameter
- L93 _public enumerator_ `SC_CONDITIONAL` — Select one value or the other depending on a boolean input
- L96 _public enumerator_ `SC_SWITCH` — Select one of several values depending on an int input
- L98 _public enumerator_ `SC_MATERIAL_BREAK`
- L101 _public enumerator_ `SC_ARITHMETIC` — Apply an arithmetic operation to two scalars
- L104 _public enumerator_ `SC_CURVE` — Get a scalar value from a curve
- L107 _public enumerator_ `SC_EXTERNAL` — External operation
- L115 _public enumerator_ `CO_CONSTANT` — Constant value
- L117 _public enumerator_ `SC_RANGE_END = CO_CONSTANT`
- L118 _public enumerator_ `CO_RANGE_BEGIN = SC_RANGE_END`
- L121 _public enumerator_ `CO_PARAMETER` — User parameter
- L124 _public enumerator_ `CO_CONDITIONAL` — Select one value or the other depending on a boolean input
- L127 _public enumerator_ `CO_SWITCH` — Select one of several values depending on an int input
- L129 _public enumerator_ `CO_MATERIAL_BREAK`
- L132 _public enumerator_ `CO_SAMPLEIMAGE` — Sample an image to get its color
- L135 _public enumerator_ `CO_SWIZZLE` — Make a color by shuffling channels from other color
- L138 _public enumerator_ `CO_FROMSCALARS` — Compose a vector from 4 scalars
- L141 _public enumerator_ `CO_ARITHMETIC` — Apply component-wise arithmetic operations to two colors
- L144 _public enumerator_ `CO_LINEARTOSRGB` — Apply a Linear to sRGB color transformation on a given color vector
- L147 _public enumerator_ `CO_EXTERNAL` — External operation
- L154 _public enumerator_ `ST_CONSTANT` — Constant value
- L156 _public enumerator_ `CO_RANGE_END = ST_CONSTANT`
- L157 _public enumerator_ `ST_RANGE_BEGIN = CO_RANGE_END`
- L159 _public enumerator_ `ST_PARAMETER`
- L167 _public enumerator_ `PR_CONSTANT` — Constant value
- L169 _public enumerator_ `ST_RANGE_END = PR_CONSTANT`
- L170 _public enumerator_ `PR_RANGE_BEGIN = ST_RANGE_END`
- L172 _public enumerator_ `PR_PARAMETER`
- L179 _public enumerator_ `IM_CONSTANT`
- L181 _public enumerator_ `PR_RANGE_END = IM_CONSTANT`
- L182 _public enumerator_ `IM_RANGE_BEGIN = PR_RANGE_END`
- L185 _public enumerator_ `IM_PARAMETER` — User parameter
- L188 _public enumerator_ `IM_REFERENCE` — A referenced, but opaque engine image
- L191 _public enumerator_ `IM_CONDITIONAL` — Select one value or the other depending on a boolean input
- L193 _public enumerator_ `IM_SWITCH`
- L195 _public enumerator_ `IM_MATERIAL_BREAK`
- L198 _public enumerator_ `IM_PARAMETER_FROM_MATERIAL` — Converts a texture of a material parameter into a texture parameter to process it at runtime.
- L202 _public enumerator_ `IM_LAYER` — Combine an image on top of another one using a specific effect (Blend, SoftLight, Hardlight, Burn...). And optionally a mask.
- L206 _public enumerator_ `IM_LAYERCOLOR` — Apply a color on top of an image using a specific effect (Blend, SoftLight, Hardlight, Burn...), optionally using a mask.
- L209 _public enumerator_ `IM_PIXELFORMAT` — Convert between pixel formats
- L213 _public enumerator_ `IM_CONFORM` — Conform the image to a given image descriptor
- L216 _public enumerator_ `IM_MIPMAP` — Generate mipmaps up to a provided level
- L219 _public enumerator_ `IM_RESIZE` — Resize the image to a constant size
- L222 _public enumerator_ `IM_RESIZELIKE` — Resize the image to the size of another image
- L225 _public enumerator_ `IM_RESIZEREL` — Resize the image by a relative factor
- L228 _public enumerator_ `IM_BLANKLAYOUT` — Create an empty image to hold a particular layout.
- L231 _public enumerator_ `IM_COMPOSE` — Copy an image into a rect of another one.
- L234 _public enumerator_ `IM_MULTICOMPOSE` — Copy blocks from an image into a another one.
- L237 _public enumerator_ `IM_INTERPOLATE` — Interpolate between 2 images taken from a row of targets (2 consecutive targets).
- L240 _public enumerator_ `IM_SATURATE` — Change the saturation of the image.
- L243 _public enumerator_ `IM_LUMINANCE` — Generate a one-channel image with the luminance of the source image.
- L246 _public enumerator_ `IM_SWIZZLE` — Recombine the channels of several images into one.
- L250 _public enumerator_ `IM_COLORMAP` — grey-level.
- L253 _public enumerator_ `IM_BINARISE` — Generate a black and white image from an image and a threshold.
- L256 _public enumerator_ `IM_PLAINCOLOR` — Generate a plain color image
- L259 _public enumerator_ `IM_CROP` — Cut a rect from an image
- L262 _public enumerator_ `IM_PATCH` — Replace a subrect of an image with another one
- L265 _public enumerator_ `IM_RASTERMESH` — Render a mesh texture layout into a mask
- L268 _public enumerator_ `IM_MAKEGROWMAP` — Create an image displacement encoding the grow operation for a mask
- L271 _public enumerator_ `IM_DISPLACE` — Apply an image displacement on another image.
- L274 _public enumerator_ `IM_MULTILAYER` — Repeately apply
- L277 _public enumerator_ `IM_INVERT` — Inverts the colors of an image
- L280 _public enumerator_ `IM_NORMALCOMPOSITE` — Modifiy roughness channel of an image based on normal variance.
- L283 _public enumerator_ `IM_TRANSFORM` — Apply linear transform to Image content. Resulting samples outside the original image are tiled.
- L286 _public enumerator_ `IM_PARAMETER_CONVERT` — Convert an FIamge in Passthrough Parameter mode to an FImage with data.
- L289 _public enumerator_ `IM_EXTERNAL` — External operation
- L296 _public enumerator_ `ME_CONSTANT` — Constant value
- L298 _public enumerator_ `IM_RANGE_END = ME_CONSTANT`
- L299 _public enumerator_ `ME_RANGE_BEGIN = IM_RANGE_END`
- L302 _public enumerator_ `ME_PARAMETER` — User parameter
- L304 _public enumerator_ `ME_REFERENCE`
- L307 _public enumerator_ `ME_CONDITIONAL` — Select one value or the other depending on a boolean input
- L310 _public enumerator_ `ME_SWITCH` — Select one of several values depending on an int input
- L313 _public enumerator_ `ME_APPLYLAYOUT` — Apply a layout to a mesh texture coordinates channel
- L316 _public enumerator_ `ME_PREPARELAYOUT`
- L320 _public enumerator_ `ME_DIFFERENCE` — Compare two meshes and extract a morph from the first to the second The meshes must have the same topology, etc.
- L323 _public enumerator_ `ME_MORPH` — Apply a one morphs on a base.
- L326 _public enumerator_ `ME_MERGE` — Merge a mesh to a mesh
- L330 _public enumerator_ `ME_MASKCLIPMESH` — Create a new mask mesh selecting all the faces of a source that are inside a given clip mesh.
- L334 _public enumerator_ `ME_MASKCLIPUVMASK` — Create a new mask mesh selecting the faces of a source that have UVs inside the region marked in an image mask.
- L337 _public enumerator_ `ME_MASKDIFF` — Create a new mask mesh selecting all the faces of a source that match another mesh.
- L340 _public enumerator_ `ME_REMOVEMASK` — Remove all the geometry selected by a mask.
- L343 _public enumerator_ `ME_FORMAT` — Change the mesh format to match the format of another one.
- L346 _public enumerator_ `ME_EXTRACTLAYOUTBLOCK` — Extract a fragment of a mesh containing specific layout blocks.
- L349 _public enumerator_ `ME_TRANSFORM` — Apply a transform in a 4x4 matrix to the geometry channels of the mesh
- L352 _public enumerator_ `ME_CLIPMORPHPLANE` — Clip the mesh with a plane and morph it when it is near until it becomes an ellipse on the plane.
- L355 _public enumerator_ `ME_CLIPWITHMESH` — Clip the mesh with another mesh.
- L358 _public enumerator_ `ME_PROJECT` — Project a mesh using a projector and clipping the irrelevant faces
- L361 _public enumerator_ `ME_APPLYPOSE` — Deform a skinned mesh applying a skeletal pose
- L364 _public enumerator_ `ME_BINDSHAPE` — Calculate the binding of a mesh on a shape
- L367 _public enumerator_ `ME_APPLYSHAPE` — Apply a shape on a (previously bound) mesh
- L370 _public enumerator_ `ME_CLIPDEFORM` — Clip Deform using bind data.
- L373 _public enumerator_ `ME_ADDMETADATA` — Add a metadata to a mesh
- L376 _public enumerator_ `ME_SETMATERIALSLOTID` — Set the Material Slot Id to the mesh
- L379 _public enumerator_ `ME_TRANSFORMWITHMESH` — Transform with a 4x4 matrix the geometry channels of a mesh that are bounded by another mesh
- L382 _public enumerator_ `ME_TRANSFORMWITHBONE` — Transform with a 4x4 matrix the geometry channels of a mesh that are skinned to a bone or hierarchy
- L385 _public enumerator_ `ME_EXTERNAL` — External operation
- L388 _public enumerator_ `ME_SKELETALMESH_BREAK` — Select a Mesh Section from a Skeletal Mesh.
- L394 _public enumerator_ `LD_CONDITIONAL`
- L396 _public enumerator_ `ME_RANGE_END = LD_CONDITIONAL`
- L397 _public enumerator_ `LD_RANGE_BEGIN = ME_RANGE_END`
- L399 _public enumerator_ `LD_SWITCH`
- L402 _public enumerator_ `LD_NEW` — Create a new LOD from Meshes.
- L408 _public enumerator_ `SK_CONDITIONAL`
- L410 _public enumerator_ `LD_RANGE_END = SK_CONDITIONAL`
- L411 _public enumerator_ `SK_RANGE_BEGIN = LD_RANGE_END`
- L413 _public enumerator_ `SK_SWITCH`
- L416 _public enumerator_ `SK_NEW` — Create a new Skeletal Mesh from LODs.
- L419 _public enumerator_ `SK_PARAMETER` — User parameter
- L421 _public enumerator_ `SK_MERGE`
- L424 _public enumerator_ `SK_CONVERT` — Convert a SkeletalMesh in Passthrough mode to an FSkeletalMesh with data.
- L427 _public enumerator_ `SK_MORPH` — Apply a morph to a Skeletal Mesh
- L430 _public enumerator_ `SK_RESHAPE` — Transfer a mesh defromation from one SkletalMesh to another
- L433 _public enumerator_ `SK_MATERIALMODIFY` — SkeletalMesh material modification.
- L436 _public enumerator_ `SK_CLIPMESHWITHMESH` — Clip parts of a skeletal mesh inside the volume defined by another SkeletalMesh
- L439 _public enumerator_ `SK_TRANSFORM` — Apply a transform in a 4x4 matrix to the geometry channels of the Skeletal Mesh
- L442 _public enumerator_ `SK_TRANSFORMWITHBONE` — Transform with a 4x4 matrix the geometry channels of a Skeletal Mesh that are skinned to a bone or hierarchy
- L445 _public enumerator_ `SKO_CONVERT` — Convert a FSkeletalMesh to USkeletalMesh.
- L452 _public enumerator_ `IN_CONDITIONAL` — Select one value or the other depending on a boolean input
- L454 _public enumerator_ `SK_RANGE_END = IN_CONDITIONAL`
- L455 _public enumerator_ `IN_RANGE_BEGIN = SK_RANGE_END`
- L458 _public enumerator_ `IN_SWITCH` — Select one of several values depending on an int input
- L461 _public enumerator_ `IN_ADDCOMPONENT` — Add a component to an instance LOD
- L464 _public enumerator_ `IN_ADDSKELETALMESH` — Add a Skeletal Mesh to an instance.
- L467 _public enumerator_ `IN_ADDEXTENSIONDATA` — Add extension data to an instance
- L470 _public enumerator_ `IN_ADDOVERLAYMATERIAL` — Add overlay material to an instance
- L473 _public enumerator_ `IN_ADDOVERRIDEMATERIAL` — Add override material to an instance
- L480 _public enumerator_ `LA_CONSTANT` — Constant value
- L482 _public enumerator_ `IN_RANGE_END = LA_CONSTANT`
- L483 _public enumerator_ `LA_RANGE_BEGIN = IN_RANGE_END`
- L486 _public enumerator_ `LA_CONDITIONAL` — Select one value or the other depending on a boolean input
- L489 _public enumerator_ `LA_SWITCH` — Select one of several values depending on an int input
- L492 _public enumerator_ `LA_PACK` — Pack all the layout blocks from the source in the grid without overlapping
- L495 _public enumerator_ `LA_MERGE` — Merge two layouts
- L501 _public enumerator_ `LA_REMOVEBLOCKS` — Remove all layout blocks not used by any vertex of the mesh. This operation is for the new way of managing layout blocks.
- L504 _public enumerator_ `LA_FROMMESH` — Extract a layout from a mesh
- L511 _public enumerator_ `MI_CONSTANT` — Constant value
- L513 _public enumerator_ `LA_RANGE_END = MI_CONSTANT`
- L514 _public enumerator_ `MI_RANGE_BEGIN = LA_RANGE_END`
- L517 _public enumerator_ `MI_PARAMETER` — User parameter
- L520 _public enumerator_ `MI_CONDITIONAL` — Select one value or the other depending on a boolean input
- L523 _public enumerator_ `MI_SWITCH` — Select one of several values depending on an int input
- L526 _public enumerator_ `MI_SKELETALMESHOBJECT_BREAK` — Get a material from a given skeletal mesh
- L529 _public enumerator_ `MI_SKELETALMESH_BREAK` — Get a material from a given skeletal mesh
- L532 _public enumerator_ `MI_FROM_SKELETALMESH_SLOT` — Get a material from a given skeletal mesh slot
- L535 _public enumerator_ `MI_MODIFY` — Modifies the parameter values of a material
- L538 _public enumerator_ `MI_EXTERNAL` — External operation
- L546 _public enumerator_ `MA_CONSTANT` — User parameter
- L548 _public enumerator_ `MI_RANGE_END = MA_CONSTANT`
- L549 _public enumerator_ `MA_RANGE_BEGIN = MI_RANGE_END`
- L552 _public enumerator_ `MA_PARAMETER` — User parameter
- L558 _public enumerator_ `ED_CONSTANT`
- L560 _public enumerator_ `MA_RANGE_END = ED_CONSTANT`
- L561 _public enumerator_ `ED_RANGE_BEGIN = MA_RANGE_END`
- L564 _public enumerator_ `ED_CONDITIONAL` — Select one value or the other depending on a boolean input
- L567 _public enumerator_ `ED_SWITCH` — Select one of several values depending on an int input
- L574 _public enumerator_ `IS_PARAMETER` — User parameter
- L576 _public enumerator_ `ED_RANGE_END = IS_PARAMETER`
- L577 _public enumerator_ `IS_RANGE_BEGIN = ED_RANGE_END`
- L580 _public enumerator_ `IS_EXTERNAL` — External operation
- L582 _public enumerator_ `IS_CONDITIONAL`
- L584 _public enumerator_ `IS_SWITCH`
- L586 _public enumerator_ `IS_RANGE_END`
- L593 _public enumerator_ `COUNT = IS_RANGE_END`

#### enum `UE::Mutable::Private::EDataType`  
`enum class EDataType : uint8`  
_L602-629_
- desc: Types of data handled by the Mutable runtime.
- L604 _public enumerator_ `None = 0`
- L605 _public enumerator_ `Bool`
- L606 _public enumerator_ `Int`
- L607 _public enumerator_ `Scalar`
- L608 _public enumerator_ `Color`
- L609 _public enumerator_ `Image`
- L610 _public enumerator_ `Layout`
- L611 _public enumerator_ `Mesh`
- L612 _public enumerator_ `Instance`
- L613 _public enumerator_ `Projector`
- L614 _public enumerator_ `String`
- L615 _public enumerator_ `ExtensionData`
- L616 _public enumerator_ `Matrix`
- L617 _public enumerator_ `Material`
- L618 _public enumerator_ `InstancedStruct`
- L619 _public enumerator_ `SkeletalMesh`
- L620 _public enumerator_ `LOD`
- L623 _public enumerator_ `Shape` — Supporting data types : Never returned as an actual data type for any operation.
- L624 _public enumerator_ `Curve`
- L625 _public enumerator_ `Skeleton`
- L626 _public enumerator_ `PhysicsAsset`
- L628 _public enumerator_ `Count`

#### enum `UE::Mutable::Private::EMeshBindShapeFlags`  
`enum class EMeshBindShapeFlags : uint32`  
_L686-697_
- L688 _public enumerator_ `None = 0`
- L689 _public enumerator_ `ReshapeSkeleton = 1 << 0`
- L690 _public enumerator_ `EnableRigidParts = 1 << 2`
- L691 _public enumerator_ `ReshapePhysicsVolumes = 1 << 4`
- L692 _public enumerator_ `ReshapeVertices = 1 << 5`
- L693 _public enumerator_ `ApplyLaplacian = 1 << 6`
- L694 _public enumerator_ `RecomputeNormals = 1 << 7`
- L695 _public enumerator_ `ReshapeSkeletonInvertSelection = 1 << 8`
- L696 _public enumerator_ `ReshapePhysicsVolumesInvertSelection = 1 << 9`

#### enum `UE::Mutable::Private::EMeshBindColorChannelUsage`  
`enum class EMeshBindColorChannelUsage : uint8`  
_L700-705_
- L702 _public enumerator_ `None = 0`
- L703 _public enumerator_ `ClusterId = 1`
- L704 _public enumerator_ `MaskWeight = 2`

#### struct `UE::Mutable::Private::FMeshBindColorChannelUsages`  
`struct FMeshBindColorChannelUsages`  
_L707-713_
- L709 _public member_ `EMeshBindColorChannelUsage R;`
- L710 _public member_ `EMeshBindColorChannelUsage G;`
- L711 _public member_ `EMeshBindColorChannelUsage B;`
- L712 _public member_ `EMeshBindColorChannelUsage A;`

#### struct `UE::Mutable::Private::FOperation`  
`struct FOperation`  
_L718-1664_
- L720 _public typedef_ `using ADDRESS_TYPE = uint32;`
- L722 _public typedef_ `typedef ADDRESS_TYPE ADDRESS;`
- L723 _public typedef_ `typedef ADDRESS_TYPE PARAMETER;`
- L724 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_SHAPE;`
- L725 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_MATRIX;`
- L726 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_NAME;`
- L727 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_STRING;`
- L728 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_ADDRESS;`
- L729 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_UINT32;`
- L730 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_UINT64;`
- L731 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_INT32;`
- L732 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_PASSTHROUGH_ID;`
- L733 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_FLOAT;`
- L734 _public typedef_ `typedef ADDRESS_TYPE CONSTANT_LIST_BOOL;`
- L736 _public member_ `static constexpr uint32 AddressByteCodeOffsetBits = 26;`
- L737 _public member_ `static constexpr uint32 MaxAddressByteCodeOffset = (1 << AddressByteCodeOffsetBits) - 1;`

#### struct `UE::Mutable::Private::FOperation::BoolConstantArgs`  
`struct BoolConstantArgs`  
_L740-743_
- desc: Arguments for every operation type.
- L742 _public member_ `bool bValue;`

#### struct `UE::Mutable::Private::FOperation::IntConstantArgs`  
`struct IntConstantArgs`  
_L745-748_
- L747 _public member_ `int32 Value;`

#### struct `UE::Mutable::Private::FOperation::ScalarConstantArgs`  
`struct ScalarConstantArgs`  
_L750-753_
- L752 _public member_ `float Value;`

#### struct `UE::Mutable::Private::FOperation::ColorConstantArgs`  
`struct ColorConstantArgs`  
_L755-758_
- L757 _public member_ `FVector4f Value;`

#### struct `UE::Mutable::Private::FOperation::MatrixConstantArgs`  
`struct MatrixConstantArgs`  
_L760-763_
- L762 _public member_ `CONSTANT_MATRIX value;`

#### struct `UE::Mutable::Private::FOperation::ResourceConstantArgs`  
`struct ResourceConstantArgs`  
_L765-768_
- L767 _public member_ `ADDRESS value;`

#### struct `UE::Mutable::Private::FOperation::ExternalDataConstantArgs`  
`struct ExternalDataConstantArgs`  
_L770-773_
- L772 _public member_ `PASSTHROUGH_ID ExternalObjectId;`

#### struct `UE::Mutable::Private::FOperation::MeshConstantArgs`  
`struct MeshConstantArgs`  
_L775-785_
- L778 _public member_ `ADDRESS Value;` — Index of the mesh in the mesh constant array
- L782 _public member_ `int32 Skeleton;` — If not negative, index of the skeleton to set to the mesh from the skeleton constant array.
- L784 _public member_ `PASSTHROUGH_ID ClothID;`

#### struct `UE::Mutable::Private::FOperation::MaterialConstantArgs`  
`struct MaterialConstantArgs`  
_L787-791_
- L789 _public member_ `ADDRESS Value;`
- L790 _public member_ `PASSTHROUGH_ID ID;`

#### struct `UE::Mutable::Private::FOperation::ParameterArgs`  
`struct ParameterArgs`  
_L794-797_
- L796 _public member_ `PARAMETER variable;`

#### struct `UE::Mutable::Private::FOperation::MaterialParameterArgs`  
`struct MaterialParameterArgs`  
_L799-805_
- L801 _public member_ `PARAMETER Variable;`
- L803 _public member_ `CONSTANT_LIST_UINT32 ImageParameterNames;`
- L804 _public member_ `CONSTANT_LIST_UINT32 ImageParameterAddress;`

#### struct `UE::Mutable::Private::FOperation::MaterialSkeletalMeshObjectBreakArgs`  
`struct MaterialSkeletalMeshObjectBreakArgs`  
_L807-811_
- L809 _public member_ `CONSTANT_NAME SlotName;`
- L810 _public member_ `ADDRESS SkeletalMeshObject;`

#### struct `UE::Mutable::Private::FOperation::MaterialSkeletalMeshBreakArgs`  
`struct MaterialSkeletalMeshBreakArgs`  
_L813-817_
- L815 _public member_ `CONSTANT_NAME SlotName;`
- L816 _public member_ `ADDRESS SkeletalMesh;`

#### struct `UE::Mutable::Private::FOperation::MeshSkeletalMeshBreakArgs`  
`struct MeshSkeletalMeshBreakArgs`  
_L819-827_
- L821 _public member_ `PARAMETER SkeletalMeshParameter;`
- L822 _public member_ `uint8 BaseLOD = 0;`
- L823 _public member_ `uint8 BaseSection = 0;`
- L824 _public member_ `uint8 LODBias = 0;`
- L825 _public member_ `uint8 Flags = 0;`
- L826 _public member_ `uint32 MeshID = 0;`

#### struct `UE::Mutable::Private::FOperation::ConditionalArgs`  
`struct ConditionalArgs`  
_L829-832_
- L831 _public member_ `ADDRESS condition, yes, no;`
- L831 _public member_ `ADDRESS condition, yes, no;`
- L831 _public member_ `ADDRESS condition, yes, no;`

#### struct `UE::Mutable::Private::FOperation::ResourceReferenceArgs`  
`struct ResourceReferenceArgs`  
_L834-839_
- L836 _public member_ `FImageDesc ImageDesc;`
- L837 _public member_ `PASSTHROUGH_ID ID;`
- L838 _public member_ `int8 ForceLoad;`

#### struct `UE::Mutable::Private::FOperation::FSwitchCaseDescriptor`  
`struct FSwitchCaseDescriptor`  
_L841-845_
- L843 _public member_ `uint32 Count : 31;`
- L844 _public member_ `uint32 bUseRanges : 1;`

#### struct `UE::Mutable::Private::FOperation::BoolEqualScalarConstArgs`  
`struct BoolEqualScalarConstArgs`  
_L848-852_
- L850 _public member_ `ADDRESS Value;`
- L851 _public member_ `int32 Constant;`

#### struct `UE::Mutable::Private::FOperation::BoolBinaryArgs`  
`struct BoolBinaryArgs`  
_L854-857_
- L856 _public member_ `ADDRESS A,B;`
- L856 _public member_ `ADDRESS A,B;`

#### struct `UE::Mutable::Private::FOperation::BoolNotArgs`  
`struct BoolNotArgs`  
_L859-862_
- L861 _public member_ `ADDRESS A;`

#### struct `UE::Mutable::Private::FOperation::ScalarCurveArgs`  
`struct ScalarCurveArgs`  
_L864-868_
- L866 _public member_ `ADDRESS time;` — Operation generating the time value to sample the curve
- L867 _public member_ `ADDRESS curve;` — Constant curve (not an op)

#### struct `UE::Mutable::Private::FOperation::ColorSampleImageArgs`  
`struct ColorSampleImageArgs`  
_L870-875_
- L872 _public member_ `ADDRESS Image;`
- L873 _public member_ `ADDRESS X,Y;`
- L873 _public member_ `ADDRESS X,Y;`
- L874 _public member_ `uint8 Filter;`

#### struct `UE::Mutable::Private::FOperation::ColorSwizzleArgs`  
`struct ColorSwizzleArgs`  
_L877-881_
- L879 _public member_ `uint8 sourceChannels[ MUTABLE_OP_MAX_SWIZZLE_CHANNELS ];`
- L880 _public member_ `ADDRESS sources[ MUTABLE_OP_MAX_SWIZZLE_CHANNELS ];`

#### struct `UE::Mutable::Private::FOperation::ColorFromScalarsArgs`  
`struct ColorFromScalarsArgs`  
_L883-886_
- L885 _public member_ `ADDRESS V[MUTABLE_OP_MAX_SWIZZLE_CHANNELS];`

#### struct `UE::Mutable::Private::FOperation::ArithmeticArgs`  
`struct ArithmeticArgs`  
_L888-901_
- L897 _public typedef_ `} OPERATION;`
- L898 _public member_ `uint8 Operation;`
- L900 _public member_ `ADDRESS A, B;`
- L900 _public member_ `ADDRESS A, B;`

#### enum `UE::Mutable::Private::FOperation::ArithmeticArgs::(anonymous)`  
``  
_L891-897_

#### struct `UE::Mutable::Private::FOperation::ColorArgs`  
`struct ColorArgs`  
_L903-906_
- L905 _public member_ `ADDRESS Color;`

#### struct `UE::Mutable::Private::FOperation::ImageLayerArgs`  
`struct ImageLayerArgs`  
_L910-938_
- L912 _public member_ `ADDRESS base;`
- L913 _public member_ `ADDRESS mask;`
- L914 _public member_ `ADDRESS blended;`
- L915 _public member_ `uint8 blendType;` — One of EBlendType
- L918 _public member_ `uint8 blendTypeAlpha;` — One of EBlendType. If this is different than NONE, it will be applied to the alpha with the channel BlendAlphaSourceChannel of the blended.
- L921 _public member_ `uint8 BlendAlphaSourceChannel;` — Channel to use from the source blended argument to apply blendTypeAlpha, if any.
- L923 _public member_ `uint8 flags;`
- L937 _public typedef_ `F_BLENDED_RGB_FROM_ALPHA = 1 << 4, } FLAGS;` — Use the alpha channel of the blended image as its RGB.

#### enum `UE::Mutable::Private::FOperation::ImageLayerArgs::(anonymous)`  
``  
_L925-937_

#### struct `UE::Mutable::Private::FOperation::ImageMultiLayerArgs`  
`struct ImageMultiLayerArgs`  
_L940-956_
- L942 _public member_ `ADDRESS base;`
- L943 _public member_ `ADDRESS mask;`
- L944 _public member_ `ADDRESS blended;`
- L945 _public member_ `ADDRESS rangeSize;`
- L946 _public member_ `uint16 rangeId;`
- L947 _public member_ `uint8 blendType;` — One of EBlendType
- L950 _public member_ `uint8 blendTypeAlpha;` — One of EBlendType. If this is different than NONE, it will be applied to the alpha with the channel BlendAlphaSourceChannel of the blended.
- L953 _public member_ `uint8 BlendAlphaSourceChannel;` — Channel to use from the source color argument to apply blendTypeAlpha, if any.
- L955 _public member_ `uint8 bUseMaskFromBlended;`

#### struct `UE::Mutable::Private::FOperation::ImageLayerColorArgs`  
`struct ImageLayerColorArgs`  
_L958-973_
- L960 _public member_ `ADDRESS base;`
- L961 _public member_ `ADDRESS mask;`
- L962 _public member_ `ADDRESS color;`
- L963 _public member_ `uint8 blendType;` — One of EBlendType
- L966 _public member_ `uint8 blendTypeAlpha;` — One of EBlendType. If this is different than NONE, it will be applied to the alpha but with the channel BlendAlphaSourceChannel of the color.
- L969 _public member_ `uint8 BlendAlphaSourceChannel;` — Channel to use from the source color argument to apply blendTypeAlpha, if any.
- L972 _public member_ `uint8 flags;` — Like in ImageLayerArgs.

#### struct `UE::Mutable::Private::FOperation::ImagePixelFormatArgs`  
`struct ImagePixelFormatArgs`  
_L975-980_
- L977 _public member_ `ADDRESS source;`
- L978 _public member_ `EImageFormat format;`
- L979 _public member_ `EImageFormat formatIfAlpha;`

#### struct `UE::Mutable::Private::FOperation::ImageConformArgs`  
`struct ImageConformArgs`  
_L982-986_
- L984 _public member_ `ADDRESS Source;`
- L985 _public member_ `FImageDesc ConformDescriptor;`

#### struct `UE::Mutable::Private::FOperation::ImageMipmapArgs`  
`struct ImageMipmapArgs`  
_L988-1005_
- L990 _public member_ `ADDRESS source;`
- L993 _public member_ `uint8 levels;` — Number of mipmaps to build. If zero, it means all.
- L996 _public member_ `uint8 blockLevels;` — Number of mipmaps that can be generated for a single layout block.
- L1000 _public member_ `bool onlyTail;` — This is true if this operation is supposed to build only the tail mipmaps. It is used during the code optimisation phase, and to validate the code.
- L1003 _public member_ `EMipmapFilterType FilterType;` — Mipmap generation settings.
- L1004 _public member_ `EAddressMode AddressMode;`

#### struct `UE::Mutable::Private::FOperation::ImageResizeArgs`  
`struct ImageResizeArgs`  
_L1007-1011_
- L1009 _public member_ `ADDRESS Source;`
- L1010 _public member_ `uint16 Size[2];`

#### struct `UE::Mutable::Private::FOperation::ImageResizeLikeArgs`  
`struct ImageResizeLikeArgs`  
_L1013-1020_
- L1016 _public member_ `ADDRESS Source;` — Image that will be resized
- L1019 _public member_ `ADDRESS SizeSource;` — Image whose size will be used to resize the source.

#### struct `UE::Mutable::Private::FOperation::ImageResizeVarArgs`  
`struct ImageResizeVarArgs`  
_L1022-1029_
- L1025 _public member_ `ADDRESS source;` — Image that will be resized
- L1028 _public member_ `ADDRESS size;` — Size expression.

#### struct `UE::Mutable::Private::FOperation::ImageResizeRelArgs`  
`struct ImageResizeRelArgs`  
_L1031-1038_
- L1034 _public member_ `ADDRESS Source;` — Image that will be resized
- L1037 _public member_ `float Factor[2];` — Factor for each axis.

#### struct `UE::Mutable::Private::FOperation::ImageBlankLayoutArgs`  
`struct ImageBlankLayoutArgs`  
_L1040-1053_
- L1042 _public member_ `ADDRESS Layout;`
- L1045 _public member_ `uint16 BlockSize[2];` — Size of a layout block in pixels.
- L1046 _public member_ `EImageFormat Format;`
- L1049 _public member_ `uint8 GenerateMipmaps;` — If true, generate mipmaps.
- L1052 _public member_ `uint8 MipmapCount;` — Mipmaps to generate if mipmaps are to be generated. 0 means all.

#### struct `UE::Mutable::Private::FOperation::ImageComposeArgs`  
`struct ImageComposeArgs`  
_L1055-1062_
- L1057 _public member_ `ADDRESS layout;`
- L1058 _public member_ `ADDRESS base;`
- L1059 _public member_ `ADDRESS blockImage;`
- L1060 _public member_ `ADDRESS mask;`
- L1061 _public member_ `uint64 BlockId;`

#### struct `UE::Mutable::Private::FOperation::ImageMultiComposeArgs`  
`struct ImageMultiComposeArgs`  
_L1064-1079_
- L1066 _public member_ `ADDRESS Layout;`
- L1067 _public member_ `ADDRESS SourceLayout;`
- L1068 _public member_ `ADDRESS Base;`
- L1069 _public member_ `ADDRESS SourceImage;`
- L1074 _public member_ `uint16 LayoutBlockSizeInPixelsX = 0;` — Size of the image to create. If 0, reuse size from base.
- L1075 _public member_ `uint16 LayoutBlockSizeInPixelsY = 0;`
- L1077 _public member_ `uint16 SourceSizeX = 0;`
- L1078 _public member_ `uint16 SourceSizeY = 0;`

#### struct `UE::Mutable::Private::FOperation::ImageInterpolateArgs`  
`struct ImageInterpolateArgs`  
_L1081-1085_
- L1083 _public member_ `ADDRESS Factor;`
- L1084 _public member_ `ADDRESS Targets[ MUTABLE_OP_MAX_INTERPOLATE_COUNT ];`

#### struct `UE::Mutable::Private::FOperation::ImageSaturateArgs`  
`struct ImageSaturateArgs`  
_L1087-1094_
- L1090 _public member_ `ADDRESS Base;` — Image to modify.
- L1093 _public member_ `ADDRESS Factor;` — Saturation factor : 0 desaturates, 1 leaves the same, >1 saturates

#### struct `UE::Mutable::Private::FOperation::ImageLuminanceArgs`  
`struct ImageLuminanceArgs`  
_L1096-1100_
- L1099 _public member_ `ADDRESS Base;` — Image to modify.

#### struct `UE::Mutable::Private::FOperation::ImageSwizzleArgs`  
`struct ImageSwizzleArgs`  
_L1102-1107_
- L1104 _public member_ `EImageFormat format;`
- L1105 _public member_ `uint8 sourceChannels[ MUTABLE_OP_MAX_SWIZZLE_CHANNELS ];`
- L1106 _public member_ `ADDRESS sources[ MUTABLE_OP_MAX_SWIZZLE_CHANNELS ];`

#### struct `UE::Mutable::Private::FOperation::ImageColorMapArgs`  
`struct ImageColorMapArgs`  
_L1109-1114_
- L1111 _public member_ `ADDRESS Base;`
- L1112 _public member_ `ADDRESS Mask;`
- L1113 _public member_ `ADDRESS Map;`

#### struct `UE::Mutable::Private::FOperation::ImageBinariseArgs`  
`struct ImageBinariseArgs`  
_L1116-1120_
- L1118 _public member_ `ADDRESS Base;`
- L1119 _public member_ `ADDRESS Threshold;`

#### struct `UE::Mutable::Private::FOperation::ImagePlainColorArgs`  
`struct ImagePlainColorArgs`  
_L1122-1130_
- L1124 _public member_ `ADDRESS Color;`
- L1125 _public member_ `EImageFormat Format;`
- L1126 _public member_ `uint16 Size[2];`
- L1129 _public member_ `uint8 LODs;` — Number of mipmaps to generate. 0 means all the chain.

#### struct `UE::Mutable::Private::FOperation::ImageCropArgs`  
`struct ImageCropArgs`  
_L1132-1136_
- L1134 _public member_ `ADDRESS source;`
- L1135 _public member_ `uint16 minX, minY, sizeX, sizeY;`
- L1135 _public member_ `uint16 minX, minY, sizeX, sizeY;`
- L1135 _public member_ `uint16 minX, minY, sizeX, sizeY;`
- L1135 _public member_ `uint16 minX, minY, sizeX, sizeY;`

#### struct `UE::Mutable::Private::FOperation::ImagePatchArgs`  
`struct ImagePatchArgs`  
_L1138-1143_
- L1140 _public member_ `ADDRESS base;`
- L1141 _public member_ `ADDRESS patch;`
- L1142 _public member_ `uint16 minX, minY;`
- L1142 _public member_ `uint16 minX, minY;`

#### struct `UE::Mutable::Private::FOperation::ImageRasterMeshArgs`  
`struct ImageRasterMeshArgs`  
_L1145-1175_
- L1147 _public member_ `uint64 BlockId;`
- L1149 _public member_ `ADDRESS mesh;`
- L1152 _public member_ `ADDRESS image;` — These are used in case of projected mesh raster.
- L1153 _public member_ `ADDRESS angleFadeProperties;`
- L1156 _public member_ `ADDRESS mask;` — Mask selecting the pixels in the destination image that may receive projection.
- L1160 _public member_ `ADDRESS projector;` — A projector may be needed for some kind of per-pixel raster operations like cylindrical projections.
- L1162 _public member_ `uint16 sizeX, sizeY;`
- L1162 _public member_ `uint16 sizeX, sizeY;`
- L1163 _public member_ `uint16 SourceSizeX, SourceSizeY;`
- L1163 _public member_ `uint16 SourceSizeX, SourceSizeY;`
- L1164 _public member_ `uint16 CropMinX, CropMinY;`
- L1164 _public member_ `uint16 CropMinX, CropMinY;`
- L1165 _public member_ `uint16 UncroppedSizeX, UncroppedSizeY;`
- L1165 _public member_ `uint16 UncroppedSizeX, UncroppedSizeY;`
- L1166 _public member_ `uint8 bIsRGBFadingEnabled : 1;`
- L1167 _public member_ `uint8 bIsAlphaFadingEnabled : 1;`
- L1170 _public member_ `uint8 SamplingMethod : 3;` — Currently only 2 sampling methods are contemplated, but reserve 3 bits for future uses.
- L1172 _public member_ `uint8 MinFilterMethod : 3;` — Currently only 2 min filter methods are contemplated, but reserve 3 bits for future uses.
- L1174 _public member_ `uint8 LayoutIndex;`

#### struct `UE::Mutable::Private::FOperation::ImageMakeGrowMapArgs`  
`struct ImageMakeGrowMapArgs`  
_L1177-1181_
- L1179 _public member_ `ADDRESS mask;`
- L1180 _public member_ `int32 border;`

#### struct `UE::Mutable::Private::FOperation::ImageDisplaceArgs`  
`struct ImageDisplaceArgs`  
_L1183-1187_
- L1185 _public member_ `ADDRESS Source;`
- L1186 _public member_ `ADDRESS DisplacementMap;`

#### struct `UE::Mutable::Private::FOperation::ImageInvertArgs`  
`struct ImageInvertArgs`  
_L1189-1192_
- L1191 _public member_ `ADDRESS Base;`

#### struct `UE::Mutable::Private::FOperation::ImageNormalCompositeArgs`  
`struct ImageNormalCompositeArgs`  
_L1194-1201_
- L1196 _public member_ `ADDRESS base;`
- L1197 _public member_ `ADDRESS normal;`
- L1199 _public member_ `float power;`
- L1200 _public member_ `ECompositeImageMode mode;`

#### struct `UE::Mutable::Private::FOperation::ImageTransformArgs`  
`struct ImageTransformArgs`  
_L1203-1221_
- L1205 _public member_ `ADDRESS Base = 0;`
- L1206 _public member_ `ADDRESS OffsetX = 0;`
- L1207 _public member_ `ADDRESS OffsetY = 0;`
- L1208 _public member_ `ADDRESS ScaleX = 0;`
- L1209 _public member_ `ADDRESS ScaleY = 0;`
- L1210 _public member_ `ADDRESS Rotation = 0;`
- L1212 _public member_ `uint32 AddressMode : 31;`
- L1213 _public member_ `uint32 bKeepAspectRatio : 1;`
- L1216 _public member_ `uint16 SizeX = 0;` — Size of the image to create. If 0, reuse size from base.
- L1217 _public member_ `uint16 SizeY = 0;`
- L1219 _public member_ `uint16 SourceSizeX = 0;`
- L1220 _public member_ `uint16 SourceSizeY = 0;`

#### struct `UE::Mutable::Private::FOperation::MeshApplyLayoutArgs`  
`struct MeshApplyLayoutArgs`  
_L1224-1229_
- L1226 _public member_ `ADDRESS Mesh;`
- L1227 _public member_ `ADDRESS Layout;`
- L1228 _public member_ `uint16 Channel;`

#### struct `UE::Mutable::Private::FOperation::MeshPrepareLayoutArgs`  
`struct MeshPrepareLayoutArgs`  
_L1231-1240_
- L1233 _public member_ `ADDRESS Mesh;`
- L1234 _public member_ `ADDRESS Layout;`
- L1235 _public member_ `uint8 LayoutChannel = 0;`
- L1236 _public member_ `uint8 bUseAbsoluteBlockIds : 1;`
- L1237 _public member_ `uint8 bNormalizeUVs : 1;`
- L1238 _public member_ `uint8 bClampUVIslands : 1;`
- L1239 _public member_ `uint8 bEnsureAllVerticesHaveLayoutBlock : 1;`

#### struct `UE::Mutable::Private::FOperation::MeshMergeArgs`  
`struct MeshMergeArgs`  
_L1242-1249_
- L1244 _public member_ `ADDRESS Base;`
- L1245 _public member_ `ADDRESS Added;`
- L1248 _public member_ `uint32 NewSurfaceID;` — If 0, it merges the surfaces, otherwise, add a new surface for the added mesh.

#### struct `UE::Mutable::Private::FOperation::MeshMaskClipMeshArgs`  
`struct MeshMaskClipMeshArgs`  
_L1251-1255_
- L1253 _public member_ `ADDRESS source;`
- L1254 _public member_ `ADDRESS clip;`

#### struct `UE::Mutable::Private::FOperation::MeshMaskClipUVMaskArgs`  
`struct MeshMaskClipUVMaskArgs`  
_L1257-1264_
- L1259 _public member_ `ADDRESS Source = 0;`
- L1260 _public member_ `ADDRESS UVSource = 0;`
- L1261 _public member_ `ADDRESS MaskImage = 0;`
- L1262 _public member_ `ADDRESS MaskLayout = 0;`
- L1263 _public member_ `uint8 LayoutIndex = 0;`

#### struct `UE::Mutable::Private::FOperation::MeshMaskDiffArgs`  
`struct MeshMaskDiffArgs`  
_L1266-1270_
- L1268 _public member_ `ADDRESS Source;`
- L1269 _public member_ `ADDRESS Fragment;`

#### struct `UE::Mutable::Private::FOperation::MeshFormatArgs`  
`struct MeshFormatArgs`  
_L1272-1296_
- L1274 _public member_ `ADDRESS source;`
- L1275 _public member_ `ADDRESS format;`
- L1291 _public member_ `} EFlags;`
- L1294 _public member_ `uint8 Flags;` — EFlags combination, selecting the buffers to reformat and other options.

#### enum `UE::Mutable::Private::FOperation::MeshFormatArgs::(anonymous)`  
``  
_L1278-1291_

#### struct `UE::Mutable::Private::FOperation::MeshTransformArgs`  
`struct MeshTransformArgs`  
_L1298-1302_
- L1300 _public member_ `ADDRESS source;`
- L1301 _public member_ `CONSTANT_MATRIX matrix;`

#### struct `UE::Mutable::Private::FOperation::MeshClipMorphPlaneArgs`  
`struct MeshClipMorphPlaneArgs`  
_L1304-1315_
- L1306 _public member_ `ADDRESS Source;`
- L1307 _public member_ `ADDRESS MorphShape;`
- L1308 _public member_ `CONSTANT_SHAPE VertexSelectionShapeOrBone;`
- L1310 _public member_ `float Dist, Factor, MaxBoneRadius;`
- L1310 _public member_ `float Dist, Factor, MaxBoneRadius;`
- L1310 _public member_ `float Dist, Factor, MaxBoneRadius;`
- L1312 _public member_ `EClipVertexSelectionType VertexSelectionType;`
- L1314 _public member_ `EFaceCullStrategy FaceCullStrategy;`

#### struct `UE::Mutable::Private::FOperation::MeshClipWithMeshArgs`  
`struct MeshClipWithMeshArgs`  
_L1317-1323_
- L1319 _public member_ `ADDRESS Source;`
- L1320 _public member_ `ADDRESS ClipMesh;`
- L1322 _public member_ `EFaceCullStrategy FaceCullStrategy;`

#### struct `UE::Mutable::Private::FOperation::MeshProjectArgs`  
`struct MeshProjectArgs`  
_L1325-1330_
- L1327 _public member_ `ADDRESS Mesh;`
- L1328 _public member_ `ADDRESS Projector;`
- L1329 _public member_ `uint8 LayoutIndex;`

#### struct `UE::Mutable::Private::FOperation::MeshApplyPoseArgs`  
`struct MeshApplyPoseArgs`  
_L1332-1336_
- L1334 _public member_ `ADDRESS base;`
- L1335 _public member_ `ADDRESS pose;`

#### struct `UE::Mutable::Private::FOperation::MeshGeometryOperationArgs`  
`struct MeshGeometryOperationArgs`  
_L1338-1344_
- L1340 _public member_ `ADDRESS meshA;`
- L1341 _public member_ `ADDRESS meshB;`
- L1342 _public member_ `ADDRESS scalarA;`
- L1343 _public member_ `ADDRESS scalarB;`

#### struct `UE::Mutable::Private::FOperation::MeshMorphArgs`  
`struct MeshMorphArgs`  
_L1346-1351_
- L1348 _public member_ `CONSTANT_STRING Name;`
- L1349 _public member_ `ADDRESS Base;`
- L1350 _public member_ `ADDRESS Factor;`

#### struct `UE::Mutable::Private::FOperation::MeshBindShapeArgs`  
`struct MeshBindShapeArgs`  
_L1353-1360_
- L1355 _public member_ `ADDRESS mesh;`
- L1356 _public member_ `ADDRESS shape;`
- L1357 _public member_ `uint32 flags;`
- L1358 _public member_ `uint32 bindingMethod;`
- L1359 _public member_ `uint32 ColorUsage;`

#### struct `UE::Mutable::Private::FOperation::MeshApplyShapeArgs`  
`struct MeshApplyShapeArgs`  
_L1362-1367_
- L1364 _public member_ `ADDRESS mesh;`
- L1365 _public member_ `ADDRESS shape;`
- L1366 _public member_ `uint32 flags;`

#### struct `UE::Mutable::Private::FOperation::MeshClipDeformArgs`  
`struct MeshClipDeformArgs`  
_L1369-1376_
- L1371 _public member_ `ADDRESS mesh;`
- L1372 _public member_ `ADDRESS clipShape;`
- L1374 _public member_ `float clipWeightThreshold = 0.9f;`
- L1375 _public member_ `EFaceCullStrategy FaceCullStrategy;`

#### struct `UE::Mutable::Private::FOperation::MeshTransformWithinMeshArgs`  
`struct MeshTransformWithinMeshArgs`  
_L1378-1383_
- L1380 _public member_ `ADDRESS sourceMesh;`
- L1381 _public member_ `ADDRESS boundingMesh;`
- L1382 _public member_ `ADDRESS matrix;`

#### struct `UE::Mutable::Private::FOperation::MeshTransformWithBoneArgs`  
`struct MeshTransformWithBoneArgs`  
_L1385-1391_
- L1387 _public member_ `ADDRESS SourceMesh;`
- L1388 _public member_ `ADDRESS Matrix;`
- L1389 _public member_ `uint32 BoneId;`
- L1390 _public member_ `float ThresholdFactor;`

#### struct `UE::Mutable::Private::FOperation::MeshOptimizeSkinningArgs`  
`struct MeshOptimizeSkinningArgs`  
_L1393-1396_
- L1395 _public member_ `ADDRESS source;`

#### struct `UE::Mutable::Private::FOperation::MeshAddMetadataArgs`  
`struct MeshAddMetadataArgs`  
_L1398-1460_
- L1447 _public member_ `EnumFlags Flags;`
- L1448 _public member_ `int8 BonePosePriority;`
- L1449 _public member_ `int8 SocketPriority;`
- L1450 _public member_ `ADDRESS Source;`
- L1451 _public member_ `PASSTHROUGH_ID SkeletonId;`
- L1452 _public member_ `NameOrUInt32ListIndex GameplayTags;`
- L1453 _public member_ `PassthroughIDOrUInt32ListAddress AssetUserDataIds;`
- L1454 _public member_ `NameOrUInt32ListIndex AnimSlotNames;`
- L1455 _public member_ `PassthroughIDOrUInt32ListAddress AnimInstances;`
- L1456 _public member_ `PASSTHROUGH_ID PhysicsAssetId;` — Main Physics Asset of the mesh
- L1457 _public member_ `PassthroughIDOrUInt32ListAddress AdditionalPhysicsAssetsIds;` — Physics Assets used by AnimBPs
- L1458 _public member_ `StringAddressOrUInt32ListAddress RealTimeMorphNames;`
- L1459 _public member_ `SocketIdOrUInt32ListAddress Sockets;`

#### enum `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::EnumFlags`  
`enum class EnumFlags : uint16`  
_L1400-1415_
- L1402 _public enumerator_ `None = 0`
- L1403 _public enumerator_ `HasGameplayTags = 1 << 0`
- L1404 _public enumerator_ `IsGameplayTagList = 1 << 1`
- L1405 _public enumerator_ `HasAssetUserData = 1 << 2`
- L1406 _public enumerator_ `IsAssetUserDataList = 1 << 4`
- L1407 _public enumerator_ `HasAnimationSlots = 1 << 5`
- L1408 _public enumerator_ `IsAnimationSlotList = 1 << 6`
- L1409 _public enumerator_ `HasAdditionalPhysicsAsset = 1 << 7`
- L1410 _public enumerator_ `IsAdditionalPhysicsAssetList = 1 << 8`
- L1411 _public enumerator_ `HasRealTimeMorphNames = 1 << 9`
- L1412 _public enumerator_ `IsRealTimeMorphNamesList = 1 << 10`
- L1413 _public enumerator_ `HasSockets = 1 << 11`
- L1414 _public enumerator_ `IsSocketsList = 1 << 12`

#### union `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::NameOrUInt32ListIndex`  
`union NameOrUInt32ListIndex`  
_L1417-1421_
- L1419 _public member_ `CONSTANT_NAME NameIndex;`
- L1420 _public member_ `CONSTANT_LIST_UINT32 ListIndex;`

#### union `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::StringAddressOrUInt32ListAddress`  
`union StringAddressOrUInt32ListAddress`  
_L1423-1427_
- L1425 _public member_ `ADDRESS StringAddress;`
- L1426 _public member_ `CONSTANT_LIST_UINT32 ListAddress;`

#### union `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::ResourceIdOrUInt64ListAddress`  
`union ResourceIdOrUInt64ListAddress`  
_L1429-1433_
- L1431 _public member_ `uint64 ResourceId;`
- L1432 _public member_ `ADDRESS ListAddress;`

#### union `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::PassthroughIDOrUInt32ListAddress`  
`union PassthroughIDOrUInt32ListAddress`  
_L1435-1439_
- L1437 _public member_ `PASSTHROUGH_ID PassthroughId;`
- L1438 _public member_ `CONSTANT_LIST_UINT32 ListAddress;`

#### union `UE::Mutable::Private::FOperation::MeshAddMetadataArgs::SocketIdOrUInt32ListAddress`  
`union SocketIdOrUInt32ListAddress`  
_L1441-1445_
- L1443 _public member_ `uint32 SocketId;`
- L1444 _public member_ `CONSTANT_LIST_UINT32 ListAddress;`

#### struct `UE::Mutable::Private::FOperation::MeshSetMaterialSlotIdArgs`  
`struct MeshSetMaterialSlotIdArgs`  
_L1463-1467_
- L1465 _public member_ `ADDRESS Mesh;`
- L1466 _public member_ `uint32 MaterialSlotId;`

#### struct `UE::Mutable::Private::FOperation::FLODNewArgs`  
`struct FLODNewArgs`  
_L1469-1472_
- L1471 _public member_ `CONSTANT_LIST_UINT32 Meshes;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshNewArgs`  
`struct FSkeletalMeshNewArgs`  
_L1474-1480_
- L1476 _public member_ `CONSTANT_LIST_ADDRESS MaterialSlotMaterials;`
- L1477 _public member_ `CONSTANT_LIST_UINT32 MaterialSlotNames;`
- L1478 _public member_ `CONSTANT_LIST_UINT32 MaterialSlotIds;`
- L1479 _public member_ `CONSTANT_LIST_ADDRESS LODs;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshMergeArgs`  
`struct FSkeletalMeshMergeArgs`  
_L1482-1486_
- L1484 _public member_ `ADDRESS BaseMesh;`
- L1485 _public member_ `ADDRESS AddedMesh;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshMorphArgs`  
`struct FSkeletalMeshMorphArgs`  
_L1488-1493_
- L1490 _public member_ `CONSTANT_STRING MorphName;`
- L1491 _public member_ `ADDRESS Base;`
- L1492 _public member_ `ADDRESS Factor;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshReshapeArgs`  
`struct FSkeletalMeshReshapeArgs`  
_L1495-1506_
- L1497 _public member_ `ADDRESS Base;`
- L1498 _public member_ `ADDRESS BaseShape;`
- L1499 _public member_ `ADDRESS TargetShape;`
- L1500 _public member_ `uint32 Flags;`
- L1501 _public member_ `uint32 BindingMethod;`
- L1502 _public member_ `uint32 ColorUsage;`
- L1504 _public member_ `int32 NumBones;`
- L1505 _public member_ `int32 NumPhysics;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshMaterialModifyArgs`  
`struct FSkeletalMeshMaterialModifyArgs`  
_L1508-1513_
- L1510 _public member_ `CONSTANT_NAME MaterialSlotName;`
- L1511 _public member_ `ADDRESS SkeletalMesh;`
- L1512 _public member_ `ADDRESS NewMaterial;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshClipMeshWithMeshArgs`  
`struct FSkeletalMeshClipMeshWithMeshArgs`  
_L1515-1521_
- L1517 _public member_ `ADDRESS Source;`
- L1518 _public member_ `ADDRESS Clip;`
- L1520 _public member_ `EFaceCullStrategy FaceCullStrategy;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshTransformArgs`  
`struct FSkeletalMeshTransformArgs`  
_L1523-1527_
- L1525 _public member_ `ADDRESS Source;`
- L1526 _public member_ `CONSTANT_MATRIX Matrix;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshTransformWithBoneArgs`  
`struct FSkeletalMeshTransformWithBoneArgs`  
_L1529-1535_
- L1531 _public member_ `ADDRESS SourceSkeletalMesh;`
- L1532 _public member_ `ADDRESS Matrix;`
- L1533 _public member_ `uint32 BoneId;`
- L1534 _public member_ `float ThresholdFactor;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshObjectConvertArgs`  
`struct FSkeletalMeshObjectConvertArgs`  
_L1537-1554_
- L1539 _public member_ `ADDRESS SkeletalMesh;`
- L1540 _public member_ `CONSTANT_NAME Name;`
- L1541 _public member_ `int32 NumLODs = 0;`
- L1542 _public member_ `int32 FirstLODAvailable = 0;`
- L1543 _public member_ `uint8 FirstLODResident = 0;`
- L1544 _public member_ `int32 MinLODsDefault = 0;`
- L1545 _public member_ `CONSTANT_LIST_UINT32 MinLODsKeys;`
- L1546 _public member_ `CONSTANT_LIST_INT32 MinLODsValues;`
- L1547 _public member_ `int32 MinQualityLevelLODsDefault = 0;`
- L1548 _public member_ `CONSTANT_LIST_INT32 MinQualityLevelLODsKeys;`
- L1549 _public member_ `CONSTANT_LIST_INT32 MinQualityLevelLODsValues;`
- L1550 _public member_ `CONSTANT_LIST_FLOAT ScreenSize;`
- L1551 _public member_ `CONSTANT_LIST_FLOAT LODHysteresis;`
- L1552 _public member_ `CONSTANT_LIST_BOOL bSupportUniformlyDistributedSampling;`
- L1553 _public member_ `CONSTANT_LIST_BOOL bAllowCPUAccess;`

#### struct `UE::Mutable::Private::FOperation::FSkeletalMeshConvertArgs`  
`struct FSkeletalMeshConvertArgs`  
_L1556-1561_
- L1558 _public member_ `ADDRESS SkeletalMeshObject;`
- L1559 _public member_ `uint32 MeshID;`
- L1560 _public member_ `uint8 ConversionFlags;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddArgs`  
`struct InstanceAddArgs`  
_L1563-1567_
- L1565 _public member_ `ADDRESS instance;`
- L1566 _public member_ `ADDRESS value;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddComponentArgs`  
`struct InstanceAddComponentArgs`  
_L1569-1574_
- L1571 _public member_ `ADDRESS Instance;`
- L1572 _public member_ `ADDRESS Value;`
- L1573 _public member_ `FComponentId ExternalId;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddExtensionDataArgs`  
`struct InstanceAddExtensionDataArgs`  
_L1576-1583_
- L1580 _public member_ `ADDRESS Instance;` — This is a reference to an op that produces the Instance that the FExtensionData will be added to.
- L1582 _public member_ `ADDRESS ExtensionData;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddMaterialArgs`  
`struct InstanceAddMaterialArgs`  
_L1585-1591_
- L1589 _public member_ `ADDRESS Instance;` — This is a reference to an op that produces the Instance that the material will be added to.
- L1590 _public member_ `ADDRESS Material;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddOverrideMaterialArgs`  
`struct InstanceAddOverrideMaterialArgs`  
_L1593-1598_
- L1595 _public member_ `ADDRESS Instance;`
- L1596 _public member_ `ADDRESS Material;`
- L1597 _public member_ `CONSTANT_STRING SlotName;`

#### struct `UE::Mutable::Private::FOperation::InstanceAddOverlayMaterialArgs`  
`struct InstanceAddOverlayMaterialArgs`  
_L1600-1606_
- L1602 _public member_ `ADDRESS Instance;`
- L1603 _public member_ `ADDRESS Material;`
- L1605 _public member_ `CONSTANT_STRING SlotName;`

#### struct `UE::Mutable::Private::FOperation::LayoutPackArgs`  
`struct LayoutPackArgs`  
_L1608-1611_
- L1610 _public member_ `ADDRESS Source;`

#### struct `UE::Mutable::Private::FOperation::LayoutMergeArgs`  
`struct LayoutMergeArgs`  
_L1613-1617_
- L1615 _public member_ `ADDRESS Base;`
- L1616 _public member_ `ADDRESS Added;`

#### struct `UE::Mutable::Private::FOperation::LayoutRemoveBlocksArgs`  
`struct LayoutRemoveBlocksArgs`  
_L1619-1626_
- L1622 _public member_ `ADDRESS Source;` — Layout to be processed and modified.
- L1625 _public member_ `ADDRESS ReferenceLayout;` — Source layout to scan for active blocks.

#### struct `UE::Mutable::Private::FOperation::LayoutFromMeshArgs`  
`struct LayoutFromMeshArgs`  
_L1628-1633_
- L1631 _public member_ `ADDRESS Mesh;` — Source mesh to retrieve the layout from.
- L1632 _public member_ `uint8 LayoutIndex;`

#### struct `UE::Mutable::Private::FOperation::MaterialBreakArgs`  
`struct MaterialBreakArgs`  
_L1635-1640_
- L1637 _public member_ `ADDRESS Material;`
- L1638 _public member_ `CONSTANT_STRING ParameterName;`
- L1639 _public member_ `int8 LayerIndex;`

#### struct `UE::Mutable::Private::FOperation::MaterialBreakImageParameterArgs`  
`struct MaterialBreakImageParameterArgs`  
_L1642-1647_
- L1644 _public member_ `ADDRESS MaterialParameter;`
- L1645 _public member_ `CONSTANT_STRING ParameterName;`
- L1646 _public member_ `int8 LayerIndex;`

#### struct `UE::Mutable::Private::FOperation::ExternalArgs`  
`struct ExternalArgs`  
_L1649-1652_
- L1651 _public member_ `int32 NumOperants;`

#### struct `UE::Mutable::Private::FOperation::ImageParameterConvertArgs`  
`struct ImageParameterConvertArgs`  
_L1654-1657_
- L1656 _public member_ `ADDRESS ImageParameter;`

#### struct `UE::Mutable::Private::FOperation::MaterialModifyArgs`  
`struct MaterialModifyArgs`  
_L1659-1663_
- L1661 _public member_ `ADDRESS Material;`
- L1662 _public member_ `uint32 NumParameters;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define MUTABLE_OP_MAX_INTERPOLATE_COUNT 6`
- L17 _macro_ `#define MUTABLE_OP_MAX_SWIZZLE_CHANNELS 4`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mutable` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L596 _function_ `inline uint32 GetTypeHash(const EOpType& OpType)` (scope `UE::Mutable::Private`)
- L632 _function_ `FORCEINLINE EDataType GetOpDataType(EOpType OpType)` (scope `UE::Mutable::Private`) — Computes the data type of a given op type
- L698 _prototype_ `ENUM_CLASS_FLAGS(EMeshBindShapeFlags);` (scope `UE::Mutable::Private`)
- L892 _enumerator_ `NONE` (scope `UE::Mutable::Private::FOperation::ArithmeticArgs::__anonfa4d7ee60103`)
- L893 _enumerator_ `ADD` (scope `UE::Mutable::Private::FOperation::ArithmeticArgs::__anonfa4d7ee60103`)
- L894 _enumerator_ `SUBTRACT` (scope `UE::Mutable::Private::FOperation::ArithmeticArgs::__anonfa4d7ee60103`)
- L895 _enumerator_ `MULTIPLY` (scope `UE::Mutable::Private::FOperation::ArithmeticArgs::__anonfa4d7ee60103`)
- L896 _enumerator_ `DIVIDE` (scope `UE::Mutable::Private::FOperation::ArithmeticArgs::__anonfa4d7ee60103`)
- L926 _enumerator_ `F_NONE = 0` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`)
- L928 _enumerator_ `F_BINARY_MASK = 1 << 0` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`) — The mask is considered binary : 0 means 0% and any other value means 100%
- L930 _enumerator_ `F_APPLY_TO_ALPHA = 1 << 1` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`) — If the image has 4 channels, apply to the fourth channel as well.
- L932 _enumerator_ `F_USE_MASK_FROM_BLENDED = 1 << 2` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`) — Use the alpha channel of the blended image as mask. Mask should be null.
- L934 _enumerator_ `F_BASE_RGB_FROM_ALPHA = 1 << 3` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`) — Use the alpha channel of the base image as its RGB.
- L936 _enumerator_ `F_BLENDED_RGB_FROM_ALPHA = 1 << 4` (scope `UE::Mutable::Private::FOperation::ImageLayerArgs::__anonfa4d7ee60203`) — Use the alpha channel of the blended image as its RGB.
- L1279 _enumerator_ `Vertex = 1 << 0` (scope `UE::Mutable::Private::FOperation::MeshFormatArgs::__anonfa4d7ee60303`)
- L1280 _enumerator_ `Index = 1 << 1` (scope `UE::Mutable::Private::FOperation::MeshFormatArgs::__anonfa4d7ee60303`)
- L1284 _enumerator_ `IgnoreMissing = 1 << 4` (scope `UE::Mutable::Private::FOperation::MeshFormatArgs::__anonfa4d7ee60303`) — This flag will not add blank channels for the channels in the format mesh but not in the source mesh.
- L1287 _enumerator_ `ResetBufferIndices = 1 << 5` (scope `UE::Mutable::Private::FOperation::MeshFormatArgs::__anonfa4d7ee60303`) — This flag will force the reset of buffer indices to 0.
- L1290 _enumerator_ `OptimizeBuffers = 1 << 6` (scope `UE::Mutable::Private::FOperation::MeshFormatArgs::__anonfa4d7ee60303`) — This flag will add a step to reduce some buffers size by removing components and changing the types if possible.
- L1666 _prototype_ `void SkeletalMeshOptionsUnpack(uint16 ExecutionOptions, bool& bInitialGeneration, uint8& LODIndex, uint8& FirstLODResident, uint8& FirstLODAvailable, uint8& NumLODs);` (scope `UE::Mutable::Private`)
- L1668 _prototype_ `uint16 SkeletalMeshOptionsPack(bool bInitialGeneration, uint8 LODIndex, uint8 FirstLODResident, uint8 FirstLODAvailable, uint8 NumLODs);` (scope `UE::Mutable::Private`)
- L1670 _prototype_ `void SkeletalMeshObjectOptionsUnpack(uint16 ExecutionOptions, bool& bInitialGeneration, bool& bStreamMeshLODs, uint8& LODIndex);` (scope `UE::Mutable::Private`)
- L1672 _prototype_ `uint16 SkeletalMeshObjectOptionsPack(bool bInitialGeneration, bool bStreamMeshLODs, uint8 LODIndex);` (scope `UE::Mutable::Private`)
- L1674 _prototype_ `ENUM_CLASS_FLAGS(FOperation::MeshAddMetadataArgs::EnumFlags);` (scope `UE::Mutable::Private`)
- L1678 _function_ `FORCEINLINE FOperation::ADDRESS MakeProgramAddress(EOpType OpType, uint32 ByteCodeOffset)` (scope `UE::Mutable::Private`)
- L1693 _function_ `FORCEINLINE EDataType GetAddressDataType(FOperation::ADDRESS At)` (scope `UE::Mutable::Private`)
- L1698 _function_ `FORCEINLINE uint32 GetAddressByteCodeOffset(FOperation::ADDRESS At)` (scope `UE::Mutable::Private`)
- L1704 _prototype_ `extern void ForEachReference( const struct FProgram& Program, FOperation::ADDRESS At, const TFunctionRef<void(FOperation::ADDRESS)> );` (scope `UE::Mutable::Private`) — Utility function to apply a function to all operation references to other operations.
- L1706 _function_ `inline EOpType GetSwitchForType( EDataType d )` (scope `UE::Mutable::Private`)
- L1730 _function_ `inline EOpType GetConditionalForType(EDataType Type)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ParallelExecutionUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L7 _namespace_ `namespace ParallelExecutionUtils` (scope `UE::Mutable::Private`)
- L9 _prototype_ `void InvokeBatchParallelFor(int32 Num, TFunctionRef<void(int32)> Body);` (scope `UE::Mutable::Private::ParallelExecutionUtils`)
- L10 _prototype_ `void InvokeBatchParallelForUnbalanced(int32 Num, TFunctionRef<void(int32)> Body);` (scope `UE::Mutable::Private::ParallelExecutionUtils`)
- L11 _prototype_ `void InvokeBatchParallelForSingleThread(int32 Num, TFunctionRef<void(int32)> Body);` (scope `UE::Mutable::Private::ParallelExecutionUtils`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Parameters.h` (Internal)


#### enum `UE::Mutable::Private::EParameterType`  
`enum class EParameterType : uint32`  
_L34-73_
- desc: Model parameter types.
- L37 _public enumerator_ `None` — Undefined parameter type.
- L40 _public enumerator_ `Bool` — Boolean parameter type (true or false)
- L43 _public enumerator_ `Int` — Integer parameter type. It usually has a limited range of possible values that can be queried in the FParameters object.
- L46 _public enumerator_ `Float` — Floating point value in the range of 0.0 to 1.0
- L49 _public enumerator_ `Color` — Floating point RGBA color, with each channel ranging from 0.0 to 1.0
- L52 _public enumerator_ `Projector` — 3D Projector type, defining a position, scale and orientation.Basically used for projected decals.
- L55 _public enumerator_ `Texture` — An externally provided image.
- L58 _public enumerator_ `SkeletalMesh` — An externally provided mesh.
- L61 _public enumerator_ `Material` — An externally provided material
- L64 _public enumerator_ `String` — A text string.
- L67 _public enumerator_ `Matrix` — A 4x4 matrix.
- L69 _public enumerator_ `InstancedStruct`
- L72 _public enumerator_ `Count` — Utility enumeration value, not really a parameter type.

#### enum `UE::Mutable::Private::EProjectorType`  
`enum class EProjectorType : uint32`  
_L83-96_
- desc: Types of 3D projectors.
- L86 _public enumerator_ `Planar` — Standard projector that uses an affine transform.
- L89 _public enumerator_ `Cylindrical` — Projector that wraps the projected image around a cylinder
- L92 _public enumerator_ `Wrapping` — Smart projector that tries to follow the projected surface geometry to minimize streching.
- L95 _public enumerator_ `Count` — Utility enumeration value, not really a projector type.

#### class `UE::Mutable::Private::FRangeIndex`  
`class FRangeIndex`  
_L105-145_
- desc: Type used to set or read multi-dimensional parameter values. If parameters have multiple values because of ranges, FRangeIndex can be used to specify what value is read or set in the methods of the Parameter class. FRangeIndex objects can be reused in multiple calls for the same parameter in the Parameter class interface even after changing the position values.
- L110 _public prototype_ `FRangeIndex() = default;` — Instances of this class must be obtained from a FParameters instance.
- L117 _public prototype_ `int32 GetRangeCount() const;` — Return the number of ranges (or dimensions) used by this index
- L121 _public prototype_ `const FString& GetRangeName( int32 Index ) const;` — Return the name of a range. \param index Index of the range from 0 to GetRangeCount()-1
- L125 _public prototype_ `const FString& GetRangeUid( int32 Index) const;` — Return the Guid of the parameter, resistant to parameter name changes. \param index Index of the parameter from 0 to GetRangeCount()-1
- L129 _public prototype_ `void SetPosition( int32 Index, int32 Position );` — Set the position in one of the dimensions of the index. \param index Index of the parameter from 0 to GetRangeCount()-1
- L133 _public prototype_ `int32 GetPosition( int32 Index) const;` — Return the position in one of the dimensions of the index. \param index Index of the parameter from 0 to GetRangeCount()-1
- L138 _public member_ `TSharedPtr<const FParameters> Parameters;` — Run-time data
- L141 _public member_ `int32 Parameter = -1;` — Index of the parameter for which we are a range index
- L144 _public member_ `TArray<int32> Values;` — Position in the several dimension of the range, as defined in Parameters

#### class `UE::Mutable::Private::TIndirectObject`  
`template<class T> class TIndirectObject`  
_L149-261_
- L151 _private member_ `TUniquePtr<T> StoragePtr;`
- L155 _public function_ `template<typename... TArgs> TIndirectObject(TArgs&&... Args) : StoragePtr(MakeUnique<T>(Forward<TArgs>(Args)...))`
- L159 _public function_ `TIndirectObject(const TIndirectObject<T>& Other) : StoragePtr(MakeUnique<T>())`
- L164 _public function_ `TIndirectObject(TIndirectObject<T>&& Other) : StoragePtr(MoveTemp(Other.StoragePtr))`
- L168 _public function_ `TIndirectObject(const T& Object) : StoragePtr(MakeUnique<T>())`
- L173 _public function_ `TIndirectObject(T&& Object) : StoragePtr(MakeUnique<T>())`
- L178 _public prototype_ `TIndirectObject& operator=(TIndirectObject<T>&&) = default;`
- L180 _public function_ `TIndirectObject& operator=(const TIndirectObject<T>& Other)`
- L186 _public function_ `TIndirectObject& operator=(const T& Object)`
- L192 _public function_ `TIndirectObject& operator=(const T&& Object)`
- L198 _public function_ `const T& Get() const`
- L204 _public function_ `T& Get()`
- L210 _public function_ `operator T&()`
- L215 _public function_ `operator const T&() const`
- L220 _public function_ `T* operator &()`
- L225 _public function_ `const T* operator &() const`
- L230 _public function_ `T& operator *()`
- L235 _public function_ `const T& operator *() const`
- L240 _public function_ `bool operator==(const TIndirectObject<T>& Other) const`
- L245 _public function_ `bool operator==(const T& Object) const`
- L251 _public function_ `void Serialise(FOutputArchive& Arch) const`
- L257 _public function_ `void Unserialise(FInputArchive& Arch)`

#### struct `UE::Mutable::Private::FProjector`  
`struct FProjector`  
_L269-320_
- desc: Description of a projector to project an image on a mesh.
- L271 _public member_ `EProjectorType type = EProjectorType::Planar;`
- L272 _public member_ `FVector3f position = {0,0,0};`
- L273 _public member_ `FVector3f direction = {0,0,0};`
- L274 _public member_ `FVector3f up = {0,0,0};`
- L275 _public member_ `FVector3f scale = {0,0,0};`
- L276 _public member_ `float projectionAngle = 0.0f;`
- L279 _public function_ `inline void GetDirectionSideUp(FVector3f& OutDirection, FVector3f& OutSide, FVector3f& OutUp) const`
- L289 _public function_ `void Serialise( FOutputArchive& arch ) const`
- L300 _public function_ `void Unserialise( FInputArchive& arch )`
- L310 _public function_ `bool operator==( const FProjector& o ) const`

#### struct `UE::Mutable::Private::FShape`  
`struct FShape`  
_L325-371_
- L328 _public member_ `FVector3f position = FVector3f(0,0,0);` — Transform
- L329 _public member_ `FVector3f up = FVector3f(0, 0, 0);`
- L330 _public member_ `FVector3f side = FVector3f(0, 0, 0);`
- L332 _public member_ `FVector3f size = FVector3f(0, 0, 0);`
- L341 _public member_ `uint8 type = 0;`
- L344 _public function_ `void Serialise(FOutputArchive& arch) const`
- L354 _public function_ `void Unserialise(FInputArchive& arch)`
- L363 _public function_ `bool operator==( const FShape& o ) const`

#### enum `UE::Mutable::Private::FShape::Type`  
`enum class Type : uint8`  
_L335-340_
- L337 _public enumerator_ `None = 0`
- L338 _public enumerator_ `Ellipse`
- L339 _public enumerator_ `AABox`

#### struct `UE::Mutable::Private::FParameterDesc`  
`struct FParameterDesc`  
_L402-479_
- L404 _public member_ `FString Name;`
- L407 _public member_ `FGuid UID;` — Unique id (provided externally, so no actual guarantee that it is unique.)
- L409 _public member_ `EParameterType Type = EParameterType::None;`
- L411 _public member_ `FParameterValue DefaultValue;`
- L415 _public member_ `TArray<uint32> Ranges;` — Ranges, if the parameter is multi-dimensional. The indices refer to the Model's program vector of range descriptors.
- L447 _public member_ `TArray<FIntValueDesc> PossibleValues;` — For integer parameters, this contains the description of the possible values. If empty, the integer may have any value.
- L450 _public function_ `bool operator==( const FParameterDesc& other ) const`
- L459 _public function_ `void Serialise( FOutputArchive& arch ) const`
- L470 _public function_ `void Unserialise( FInputArchive& arch )`

#### struct `UE::Mutable::Private::FParameterDesc::FIntValueDesc`  
`struct FIntValueDesc`  
_L418-443_
- desc: Possible values of the parameter in case of being an integer, and its names
- L420 _public member_ `int16 Value;`
- L421 _public member_ `FString Name;`
- L424 _public function_ `bool operator==( const FIntValueDesc& Other ) const`
- L431 _public function_ `void Serialise( FOutputArchive& Arch ) const`
- L438 _public function_ `void Unserialise( FInputArchive& Arch)`

#### struct `UE::Mutable::Private::FRangeDesc`  
`struct FRangeDesc`  
_L482-515_
- L484 _public member_ `FString Name;`
- L485 _public member_ `FString UID;`
- L488 _public member_ `int32 DimensionParameter = -1;` — Parameter that controls the size of this range, if any.
- L491 _public function_ `bool operator==( const FRangeDesc& other ) const`
- L501 _public function_ `void Serialise( FOutputArchive& Arch ) const`
- L509 _public function_ `void Unserialise( FInputArchive& Arch)`

#### class `UE::Mutable::Private::FParameters`  
`class FParameters : public TSharedFromThis<FParameters>`  
_L524-779_
- inherits: `TSharedFromThis<FParameters>`
- desc: This class represents the parameters of a model including description, type and value, and additional resources associated to the parameter. \warning Every object of this class holds a reference to the model that it was created from. This implies that while any instance of a FParameters object is alive, its model will not be freed.
- L533 _public prototype_ `static void Serialise( const FParameters*, FOutputArchive& );` — Serialisation
- L534 _public prototype_ `static TSharedPtr<FParameters> StaticUnserialise( FInputArchive& );`
- L536 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L537 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L540 _public prototype_ `TSharedPtr<FParameters> Clone() const;` — Deep clone this object.
- L547 _public prototype_ `int32 GetCount() const;` — Return the number of parameters
- L551 _public prototype_ `const FString& GetName( int32 Index ) const;` — Return the name of the parameter. \param index Index of the parameter from 0 to GetCount()-1
- L555 _public prototype_ `const FGuid& GetUid( int32 Index) const;` — Return the Guid of the parameter, resistant to parameter name changes. \param index Index of the parameter from 0 to GetCount()-1
- L559 _public prototype_ `int32 Find( const FString& Name ) const;` — Find the parameter index by name. It returns -1 if the parameter doesn't exist.
- L563 _public prototype_ `EParameterType GetType( int32 Index) const;` — Return the type of the parameter. \param index Index of the parameter from 0 to GetCount()-1
- L567 _public prototype_ `TSharedPtr<FRangeIndex> NewRangeIndex( int32 ParamIndex) const;` — Create a new FRangeIndex object to use to access a multi-dimensional parameter. It will return nullptr if the parameter is not multidimensional.
- L571 _public prototype_ `int32 GetValueCount( int32 ParamIndex ) const;` — Return the number of values other than the default that have been set to a specific parameter.
- L576 _public prototype_ `TSharedPtr<FRangeIndex> GetValueIndex( int32 ParamIndex, int32 ValueIndex ) const;` — Return the FRangeIndex of a value that has been set to a parameter. \param paramIndex Index of the parameter from 0 to GetCount()-1 \param valueIndex Index of the value from 0 to GetValueCount()-1
- L580 _public prototype_ `void ClearAllValues( int32 ParamIndex);` — Remove all the multidimensional values for a parameter. The current non-dimensional value is kept.
- L586 _public prototype_ `bool GetBoolValue( int32 Index, const FRangeIndex* Pos =nullptr ) const;` — Return the value of a boolean parameter. \pre The parameter specified by index is a T_BOOL. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L594 _public prototype_ `void SetBoolValue( int32 Index, bool bValue, const FRangeIndex* Pos =nullptr );` — Set the value of a parameter of type boolean. \pre The parameter specified by index is a T_BOOL. \param index Index of the parameter from 0 to GetCount()-1 \param value new value of the parameter \param pos optional parameter to set a specific value for the given multidimensional position. If null, the value is set for all possible positions.
- L598 _public prototype_ `int32 GetIntPossibleValueCount( int32 ParamIndex) const;` — Get the number of possible values for this integer parameter. If the number is zero, it means any integer value is accepted.
- L602 _public prototype_ `int32 GetIntPossibleValue( int32 ParamIndex, int32 ValueIndex) const;` — Get the value of one of the possible values for this integer. The paramIndex is in the range of 0 to GetIntPossibleValueCount()-1
- L606 _public prototype_ `const FString& GetIntPossibleValueName( int32 ParamIndex, int32 ValueIndex ) const;` — Get the name of one of the possible values for this integer. The paramIndex is in the range of 0 to GetIntPossibleValueCount()-1
- L610 _public prototype_ `int32 GetIntValueIndex(int32 ParamIndex, const FString& ValueIndex) const;` — Get the index of the value of one of the possible values for this integer. The paramIndex is in the range of 0 to GetIntPossibleValueCount()-1
- L614 _public prototype_ `int32 GetIntValueIndex(int32 ParamIndex, int32 Value) const;` — Get the index of the value of one of the possible values for this integer. The paramIndex is in the range of 0 to GetIntPossibleValueCount()-1
- L620 _public prototype_ `int32 GetIntValue( int32 Index, const FRangeIndex* Pos=nullptr ) const;` — Return the value of a integer parameter. \pre The parameter specified by index is a T_INT. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L627 _public prototype_ `void SetIntValue( int32 Index, int32 Value, const FRangeIndex* Pos=nullptr );` — If the parameter is of the integer type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param value new value of the parameter. It must be in the possible values for this parameter (see GetIntPossibleValue), or the method will leave the value unchanged. \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L633 _public prototype_ `float GetFloatValue( int32 Index, const FRangeIndex* Pos=nullptr ) const;` — Return the value of a float parameter. \pre The parameter specified by index is a T_FLOAT. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L639 _public prototype_ `void SetFloatValue( int32 Index, float Value, const FRangeIndex* Pos=nullptr );` — If the parameter is of the float type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param value new value of the parameter \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L646 _public prototype_ `void GetColorValue( int32 Index, FVector4f& OutColor, const FRangeIndex* Pos=nullptr ) const;` — Return the value of a color parameter. \pre The parameter specified by index is a T_FLOAT. \param index Index of the parameter from 0 to GetCount()-1 \param OutColor Values where every resulting color channel will be stored \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L652 _public prototype_ `void SetColorValue( int32 Index, FVector4f Color, const FRangeIndex* Pos=nullptr );` — If the parameter is of the color type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param r,g,b new value of the parameter \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L665 _public prototype_ `void GetProjectorValue( int32 ParameterIndex, EProjectorType* OutProjectionType, FVector3f* OutPos, FVector3f* OutDir, FVector3f* OutUp, FVector3f* OutScale, float* OutProjectionAngle, const FRangeIndex* RangePosition=nullptr ) const;` — Return the value of a projector parameter, as a 4x4 matrix. The matrix is supposed to be a linear transform in column-major. \pre The parameter specified by index is a T_PROJECTOR. \param ParameterIndex Index of the parameter from 0 to GetCount()-1 \param OutPos Pointer to where the object-space position coordinates of the projector will be stored. \param OutDir Pointer to where the object-space direction vector of the projector will be stored. \param OutUp Pointer to where the object-space vertically up direction vector of the projector will be stored. This controls the "roll" angle of the projector. \param OutScale Pointer to the projector-space scaling of the projector. \param RangePosition Only for multidimensional parameters: relevant position to get in the ranges
- L683 _public prototype_ `void SetProjectorValue( int32 ParameterIndex, const FVector3f& Pos, const FVector3f& Dir, const FVector3f& Up, const FVector3f& Scale, float ProjectionAngle, const FRangeIndex* RangePosition=nullptr );` — If the parameter is of the projector type, set its value. \param ParameterIndex Index of the parameter from 0 to GetCount()-1 \param pos Object-space position coordinates of the projector. \param dir Object-space direction vector of the projector. \param up Object-space vertically up direction vector of the projector. \param scale Projector-space scaling of the projector. \param projectionAngle [only for Cylindrical projectors], the angle in radians of the projection area on the cylinder surface. \param RangePosition Only for multidimensional parameters: relevant position to set in the ranges
- L696 _public prototype_ `UTexture* GetTextureValue(int32 Index, const FRangeIndex* Pos = nullptr) const;` — Return the value of a Texture parameter. \pre The parameter specified by index is a Texture. \param Index Index of the parameter from 0 to GetCount()-1 \param Pos Only for multidimensional parameters: relevant position to set in the ranges \return The UTexture specified when setting the image value (\see SetTextureValue)
- L699 _public prototype_ `USkeletalMesh* GetSkeletalMeshValue(int32 Index, const FRangeIndex* Pos = nullptr) const;`
- L704 _public prototype_ `void SetTextureValue(int32 Index, UTexture* Value, const FRangeIndex* Pos = nullptr);` — If the parameter is of the Texture type, set its value. \param Index Index of the parameter from 0 to GetCount()-1 \param Pos Only for multidimensional parameters: relevant position to set in the ranges
- L707 _public prototype_ `void SetSkeletalMeshValue(int32 Index, USkeletalMesh* Value, const FRangeIndex* = nullptr);`
- L713 _public prototype_ `void GetStringValue( int32 Index, FString& OutValue, const FRangeIndex* = nullptr) const;` — Return the value of a float parameter. \pre The parameter specified by index is a T_FLOAT. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L719 _public prototype_ `void SetStringValue( int32 Index, const FString& Value, const FRangeIndex* = nullptr );` — If the parameter is of the float type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param value new value of the parameter \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L725 _public prototype_ `void GetMatrixValue( int32 Index, FMatrix44f& OutValue, const FRangeIndex* = nullptr) const;` — Return the value of a matrix parameter. \pre The parameter specified by index is a T_MATRIX. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to get in the ranges
- L731 _public prototype_ `void SetMatrixValue( int32 Index, const FMatrix44f& Value, const FRangeIndex* Pos = nullptr );` — If the parameter is of the matrix type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param value new value of the parameter \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L738 _public prototype_ `UMaterialInterface* GetMaterialValue(int32 Index, const FRangeIndex* RangeIndex = nullptr) const;` — Return the value of a Material parameter. \pre The parameter specified by index is a T_MATERIAL. \param index Index of the parameter from 0 to GetCount()-1 \param pos Only for multidimensional parameters: relevant position to set in the ranges \return The Material interface specified when setting the Material value (\see SetMaterialValue)
- L744 _public prototype_ `void SetMaterialValue(int32 Index, UMaterialInterface* Value, const FRangeIndex* RangeIndex = nullptr);` — If the parameter is of the material type, set its value. \param index Index of the parameter from 0 to GetCount()-1 \param Value Material interface to set as value. \param pos Only for multidimensional parameters: relevant position to set in the ranges
- L751 _public prototype_ `TManagedPtr<const FInstancedStruct> GetInstancedStructValue(int32 Index, const FRangeIndex* RangeIndex = nullptr) const;` — Return the value of a Instanced Struct parameter. @pre The parameter specified by index is a T_INSTANCEDSTRUCT. @param Index Index of the parameter from 0 to GetCount()-1 @param RangeIndex Only for multidimensional parameters: relevant position to set in the ranges @return The Instanced Struct interface specified when setting the Instanced Struct value (\see SetInstancedStructValue)
- L757 _public prototype_ `void SetInstancedStructValue(int32 Index, const TManagedPtr<const FInstancedStruct>& Value, const FRangeIndex* RangeIndex = nullptr);` — If the parameter is of the Instanced Struct type, set its value. \param Index Index of the parameter from 0 to GetCount()-1 \param Value Instanced Struct interface to set as value. \param RangeIndex Only for multidimensional parameters: relevant position to set in the ranges
- L761 _public prototype_ `bool HasSameValue( int32 ThisParamIndex, const TSharedPtr<const FParameters>& Other, int32 OtherParamIndex ) const;` — Utility method to compare the values of a specific parameter with the values of another FParameters object. It returns false if type or values are different.
- L763 _public prototype_ `FProjector GetProjectorValue( int32 index, const FRangeIndex* ) const;`
- L767 _public prototype_ `bool HasMultipleValues(int32 ParamIndex) const;` — Return true if the parameter has any multi-dimensional values set. This is independent to if the model accepts multi-dimensional parameters for this particular parameter.
- L770 _public member_ `TSharedPtr<const FModel> Model;` — Run-time data
- L773 _public member_ `TArray<FParameterValue> Values;` — Values for the parameters if they are not multidimensional.
- L777 _public member_ `TArray< TMap< TArray<int32>, FParameterValue > > MultiValues;` — If the parameter is multidemensional, the values are stored here. The key of the map is the vector of values stored in a FRangeIndex

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Mutable` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L76 _function_ `inline uint32 GetTypeHash(const EParameterType& Type)` (scope `UE::Mutable::Private`)
- L374 _typedef_ `using FParamBoolType = bool;` (scope `UE::Mutable::Private`)
- L375 _typedef_ `using FParamIntType = int32;` (scope `UE::Mutable::Private`)
- L376 _typedef_ `using FParamFloatType = float;` (scope `UE::Mutable::Private`)
- L377 _typedef_ `using FParamColorType = FVector4f;` (scope `UE::Mutable::Private`)
- L378 _typedef_ `using FParamProjectorType = TIndirectObject<FProjector>;` (scope `UE::Mutable::Private`)
- L379 _typedef_ `using FParamTextureType = TStrongObjectPtr<UTexture>;` (scope `UE::Mutable::Private`)
- L380 _typedef_ `using FParamSkeletalMeshType = TStrongObjectPtr<USkeletalMesh>;` (scope `UE::Mutable::Private`)
- L381 _typedef_ `using FParamStringType = TIndirectObject<FString>;` (scope `UE::Mutable::Private`)
- L382 _typedef_ `using FParamMatrixType = TIndirectObject<FMatrix44f>;` (scope `UE::Mutable::Private`)
- L383 _typedef_ `using FParamMaterialType = TStrongObjectPtr<UMaterialInterface>;` (scope `UE::Mutable::Private`)
- L384 _typedef_ `using FParamInstancedStructType = TManagedPtr<const FInstancedStruct>;` (scope `UE::Mutable::Private`) — TSharedPtr always valid and FInstancedStruct always initialized to its type.
- L386 _typedef_ `using FParameterValue = TVariant< FParamBoolType, FParamIntType, FParamFloatType, FParamColorType, FParamProjectorType, FParamTextureType, FParamSkeletalMeshType, FParamStringType, FParamMatrixType, FParamMaterialType, FParamInstancedStructType>;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/PassthroughObject.h` (Internal)


#### class `UE::Mutable::Private::TPassthroughObjectPtr`  
`template<typename T> class TPassthroughObjectPtr`  
_L21-131_
- L23 _private typedef_ `using ObjectType = T;`
- L24 _private typedef_ `using VariantType = TVariant<TStrongObjectPtr<UObject>, PASSTHROUGH_ID>;`
- L30 _public function_ `TPassthroughObjectPtr() : StableSnapshot(VariantType(TInPlaceType<PASSTHROUGH_ID>{}, PASSTHROUGH_ID_INVALID)) , Resource(MakeShared<VariantType>(StableSnapshot))`
- L36 _public function_ `TPassthroughObjectPtr(PASSTHROUGH_ID Id) : StableSnapshot(VariantType(TInPlaceType<PASSTHROUGH_ID>{}, Id)) , Resource(MakeShared<VariantType>(StableSnapshot))`
- L42 _public function_ `TPassthroughObjectPtr(T* Object) : StableSnapshot(VariantType(TInPlaceType<TStrongObjectPtr<UObject>>{}, Object)) , Resource(MakeShared<VariantType>(StableSnapshot))`
- L48 _public prototype_ `TPassthroughObjectPtr(const TPassthroughObjectPtr& Other) = default;`
- L51 _public function_ `template<typename OtherObjectType> TPassthroughObjectPtr(const TPassthroughObjectPtr<OtherObjectType>& Other) : StableSnapshot(Other.StableSnapshot) , Resource(Other.Resource)`
- L57 _public prototype_ `TPassthroughObjectPtr(TPassthroughObjectPtr&& Other) = default;`
- L58 _public prototype_ `TPassthroughObjectPtr& operator=(const TPassthroughObjectPtr& Other) = default;`
- L59 _public prototype_ `TPassthroughObjectPtr& operator=(TPassthroughObjectPtr&& Other) = default;`
- L61 _public function_ `bool operator==(const TPassthroughObjectPtr& Other) const`
- L72 _public function_ `bool IsResolved() const`
- L77 _public function_ `T* Get() const`
- L93 _public function_ `PASSTHROUGH_ID GetId() const`
- L103 _public function_ `PASSTHROUGH_ID Reset()`
- L118 _public function_ `bool IsValid() const`
- L123 _public function_ `explicit operator bool() const`
- L129 _private member_ `VariantType StableSnapshot;`
- L130 _private member_ `TSharedRef<VariantType> Resource;`

#### class `UE::Mutable::Private::FPassthroughObjectLoader`  
`class FPassthroughObjectLoader`  
_L136-167_
- L140 _public function_ `template<typename T> TPassthroughObjectPtr<T> FindChecked(PASSTHROUGH_ID Id)`
- L153 _public function_ `template<typename T> void Add(PASSTHROUGH_ID Id)`
- L161 _public prototype_ `void Load(const TMap<PASSTHROUGH_ID, TSoftObjectPtr<UObject>>& ResolutionMap, TArray<FSoftObjectPath>& AssetsToStream) const;`
- L163 _public prototype_ `void Resolve(TMap<PASSTHROUGH_ID, TSoftObjectPtr<UObject>>& ResolutionMap);`
- L166 _private member_ `TMap<PASSTHROUGH_ID, TPassthroughObjectPtr<UObject>> PassthroughObjects;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _typedef_ `using PASSTHROUGH_ID = uint32;` (scope `UE::Mutable::Private`)
- L16 _variable_ `constexpr PASSTHROUGH_ID PASSTHROUGH_ID_INVALID = TNumericLimits<PASSTHROUGH_ID>::Max();` (scope `UE::Mutable::Private`)
- L18 _prototype_ `PASSTHROUGH_ID GetPassthroughId(const TSoftObjectPtr<UObject>& SoftObjectPtr);` (scope `UE::Mutable::Private`)
- L66 _function_ `friend uint32 GetTypeHash(const TPassthroughObjectPtr& Object)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/PhysicsBody.h` (Internal)


#### struct `UE::Mutable::Private::FBodyShape`  
`struct FBodyShape`  
_L25-37_
- L27 _public member_ `FString Name;`
- L28 _public member_ `uint32 Flags = 0;`
- L30 _public function_ `bool operator==(const FBodyShape& Other) const`
- L35 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L36 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FSphereBody`  
`struct FSphereBody : FBodyShape`  
_L39-51_
- inherits: `FBodyShape`
- L41 _public member_ `FVector3f Position = FVector3f::ZeroVector;`
- L42 _public member_ `float Radius = 0.0f;`
- L44 _public function_ `bool operator==( const FSphereBody& Other ) const`
- L49 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L50 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FBoxBody`  
`struct FBoxBody : FBodyShape`  
_L53-66_
- inherits: `FBodyShape`
- L55 _public member_ `FVector3f Position = FVector3f::ZeroVector;`
- L56 _public member_ `FQuat4f Orientation = FQuat4f::Identity;`
- L57 _public member_ `FVector3f Size = FVector3f::ZeroVector;`
- L59 _public function_ `inline bool operator==( const FBoxBody& Other ) const`
- L64 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L65 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FSphylBody`  
`struct FSphylBody : FBodyShape`  
_L68-86_
- inherits: `FBodyShape`
- L70 _public member_ `FVector3f Position = FVector3f::ZeroVector;`
- L71 _public member_ `FQuat4f Orientation = FQuat4f::Identity;`
- L72 _public member_ `float Radius = 0.0f;`
- L73 _public member_ `float Length = 0.0f;`
- L75 _public function_ `inline bool operator==( const FSphylBody& Other ) const`
- L84 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L85 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FTaperedCapsuleBody`  
`struct FTaperedCapsuleBody : FBodyShape`  
_L88-108_
- inherits: `FBodyShape`
- L90 _public member_ `FVector3f Position;`
- L91 _public member_ `FQuat4f Orientation;`
- L92 _public member_ `float Radius0 = 0.0f;`
- L93 _public member_ `float Radius1 = 0.0f;`
- L94 _public member_ `float Length = 0.0f;`
- L96 _public function_ `inline bool operator==( const FTaperedCapsuleBody& Other ) const`
- L106 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L107 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FConvexBody`  
`struct FConvexBody : FBodyShape`  
_L110-127_
- inherits: `FBodyShape`
- L112 _public member_ `TArray<FVector3f> Vertices;`
- L113 _public member_ `TArray<int32> Indices;`
- L115 _public member_ `FTransform3f Transform = FTransform3f::Identity;`
- L117 _public function_ `inline bool operator==( const FConvexBody& Other ) const`
- L125 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L126 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### struct `UE::Mutable::Private::FPhysicsBodyAggregate`  
`struct FPhysicsBodyAggregate`  
_L129-148_
- L131 _public member_ `TArray<FSphereBody> Spheres;`
- L132 _public member_ `TArray<FBoxBody> Boxes;`
- L133 _public member_ `TArray<FConvexBody> Convex;`
- L134 _public member_ `TArray<FSphylBody> Sphyls;`
- L135 _public member_ `TArray<FTaperedCapsuleBody> TaperedCapsules;`
- L137 _public function_ `inline bool operator==( const FPhysicsBodyAggregate& Other ) const`
- L146 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L147 _public prototype_ `void Unserialise(FInputArchive& Arch);`

#### class `UE::Mutable::Private::FPhysicsBody`  
`class FPhysicsBody`  
_L150-287_
- L154 _public prototype_ `TManagedPtr<FPhysicsBody> Clone() const;`
- L157 _public prototype_ `static void Serialise( const FPhysicsBody*, FOutputArchive& );` — Serialisation
- L158 _public prototype_ `static TManagedPtr<FPhysicsBody> StaticUnserialise( FInputArchive& );`
- L162 _public prototype_ `void SetCustomId(int32 Id);`
- L163 _public prototype_ `int32 GetCustomId() const;`
- L165 _public prototype_ `void SetBodyCount(int32 B);`
- L166 _public prototype_ `int32 GetBodyCount() const;`
- L168 _public prototype_ `void SetBody(int32 BodyIndex, FName BoneName);`
- L170 _public prototype_ `FName GetBodyBoneName(int32 Index) const;`
- L172 _public prototype_ `int32 GetSphereCount(int32 B) const;`
- L173 _public prototype_ `int32 GetBoxCount(int32 B) const;`
- L174 _public prototype_ `int32 GetConvexCount(int32 B) const;`
- L175 _public prototype_ `int32 GetSphylCount(int32 B) const;`
- L176 _public prototype_ `int32 GetTaperedCapsuleCount(int32 B) const;`
- L178 _public prototype_ `void SetSphereCount(int32 B, int32 Count);`
- L179 _public prototype_ `void SetBoxCount(int32 B, int32 Count);`
- L180 _public prototype_ `void SetConvexCount(int32 B, int32 Count);`
- L181 _public prototype_ `void SetSphylCount(int32 B, int32 Count);`
- L182 _public prototype_ `void SetTaperedCapsuleCount(int32 B, int32 Count);`
- L184 _public prototype_ `void SetSphere( int32 B, int32 I, FVector3f Position, float Radius);`
- L188 _public prototype_ `void SetBox( int32 B, int32 I, FVector3f Position, FQuat4f Orientation, FVector3f Size);`
- L192 _public prototype_ `void SetConvexMesh( int32 B, int32 I, TArrayView<const FVector3f> Vertices, TArrayView<const int32> Indices);`
- L196 _public prototype_ `void SetConvexTransform( int32 B, int32 I, const FTransform3f& Transform);`
- L200 _public prototype_ `void SetSphyl( int32 B, int32 I, FVector3f Position, FQuat4f Orientation, float Radius, float Length);`
- L205 _public prototype_ `void SetTaperedCapsule( int32 B, int32 I, FVector3f Position, FQuat4f Orientation, float Radius0, float Radius1, float Length);`
- L210 _public prototype_ `void SetSphereFlags(int32 B, int32 I, uint32 Flags);`
- L211 _public prototype_ `void SetBoxFlags(int32 B, int32 I, uint32 Flags);`
- L212 _public prototype_ `void SetConvexFlags(int32 B, int32 I, uint32 Flags);`
- L213 _public prototype_ `void SetSphylFlags(int32 B, int32 I, uint32 Flags);`
- L214 _public prototype_ `void SetTaperedCapsuleFlags(int32 B, int32 I, uint32 Flags);`
- L216 _public prototype_ `void SetSphereName(int32 B, int32 I, const char* Name);`
- L217 _public prototype_ `void SetBoxName(int32 B, int32 I, const char* Name);`
- L218 _public prototype_ `void SetConvexName(int32 B, int32 I, const char* Name);`
- L219 _public prototype_ `void SetSphylName(int32 B, int32 I, const char* Name);`
- L220 _public prototype_ `void SetTaperedCapsuleName(int32 B, int32 I, const char* Name);`
- L222 _public prototype_ `void GetSphere( int32 B, int32 I, FVector3f& OutPosition, float& OutRadius) const;`
- L226 _public prototype_ `void GetBox( int32 B, int32 I, FVector3f& OutPosition, FQuat4f& OutOrientation, FVector3f& OutSize) const;`
- L230 _public prototype_ `void GetConvex( int32 B, int32 I, TArrayView<const FVector3f>& OutVertices, TArrayView<const int32>& OutIndices, FTransform3f& OutTransform) const;`
- L234 _public prototype_ `void GetConvexMeshView( int32 B, int32 I, TArrayView<FVector3f>& OutVerticesView, TArrayView<int32>& OutIndicesView);`
- L238 _public prototype_ `void GetConvexTransform( int32 B, int32 I, FTransform3f& OutTransform) const;`
- L242 _public prototype_ `void GetSphyl( int32 B, int32 I, FVector3f& OutPosition, FQuat4f& OutOrientation, float& OutRadius, float& OutLength) const;`
- L247 _public prototype_ `void GetTaperedCapsule( int32 B, int32 I, FVector3f& OutPosition, FQuat4f& OutOrientation, float& OutRadius0, float& OutRadius1, float& OutLength) const;`
- L252 _public prototype_ `uint32 GetSphereFlags(int32 B, int32 I) const;`
- L253 _public prototype_ `uint32 GetBoxFlags(int32 B, int32 I) const;`
- L254 _public prototype_ `uint32 GetConvexFlags(int32 B, int32 I) const;`
- L255 _public prototype_ `uint32 GetSphylFlags(int32 B, int32 I) const;`
- L256 _public prototype_ `uint32 GetTaperedCapsuleFlags(int32 B, int32 I) const;`
- L258 _public prototype_ `const FString& GetSphereName(int32 B, int32 I) const;`
- L259 _public prototype_ `const FString& GetBoxName(int32 B, int32 I) const;`
- L260 _public prototype_ `const FString& GetConvexName(int32 B, int32 I) const;`
- L261 _public prototype_ `const FString& GetSphylName(int32 B, int32 I) const;`
- L262 _public prototype_ `const FString& GetTaperedCapsuleName(int32 B, int32 I) const;`
- L264 _public prototype_ `void ConvertBoneIdsToNames(const TMap<uint32, FName>& ConstantNames);`
- L267 _public member_ `int32 CustomId = -1;`
- L270 _public member_ `TArray<FName> BodiesBoneNames;` — Bone name the physics volume aggregate is bound to.
- L271 _public member_ `TArray<uint32> BoneIds;` — Serialized
- L272 _public member_ `TArray<FPhysicsBodyAggregate> Bodies;`
- L274 _public member_ `bool bBodiesModified = false;`
- L276 _public prototype_ `void Serialise(FOutputArchive& Arch) const;`
- L277 _public prototype_ `void Unserialise(FInputArchive& Arch);`
- L280 _public function_ `inline bool operator==(const FPhysicsBody& Other) const`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Mutable` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Platform.h` (Internal)


#### Free symbols / members of external scopes

- L16 _macro_ `#define MUTABLE_DEBUG`

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ProgramCache.h` (Internal)


#### struct `UE::Mutable::Private::FCacheAddress`  
`struct FCacheAddress`  
_L29-55_
- desc: A cache address is the operation plus the context of execution(iteration indices, etc...).
- L32 _public member_ `FOperation::ADDRESS At = 0;` — The meaning of all these fields is the same than the FScheduledOp struct.
- L33 _public member_ `uint16 ExecutionIndex = 0;`
- L34 _public member_ `uint16 ExecutionOptions : 14 = 0;`
- L35 _public member_ `uint16 Type : 2 = static_cast<uint16>(FScheduledOp::EType::Full);`
- L37 _public function_ `FCacheAddress()`
- L41 _public function_ `FCacheAddress(FOperation::ADDRESS InAt, uint16 InExecutionIndex, uint16 InExecutionOptions, FScheduledOp::EType InType = FScheduledOp::EType::Full) : At(InAt), ExecutionIndex(InExecutionIndex), ExecutionOptions(InExecutionOptions), Type(static_cast<uint16>(InType))`
- L46 _public function_ `FCacheAddress(FOperation::ADDRESS InAt, const FScheduledOp& Item) : At(InAt), ExecutionIndex(Item.ExecutionIndex), ExecutionOptions(Item.ExecutionOptions), Type(static_cast<uint16>(Item.Type))`
- L51 _public function_ `FCacheAddress(const FScheduledOp& Item) : At(Item.At), ExecutionIndex(Item.ExecutionIndex), ExecutionOptions(Item.ExecutionOptions), Type(static_cast<uint16>(Item.Type))`

#### class `UE::Mutable::Private::FProgramCache`  
`class FProgramCache`  
_L78-223_
- L80 _private member_ `static constexpr uint32 InternalsAlign = 8;`
- L81 _private member_ `static constexpr uint32 InternalsSize = 1088;`
- L86 _private member_ `} InternalsStorage;`
- L88 _private prototype_ `ProgramCacheInternals::FProgramCacheInternals* GetInternals() const;`
- L115 _public prototype_ `FProgramCache();`
- L117 _public prototype_ `FProgramCache(const FProgramCache&) = delete;`
- L118 _public prototype_ `FProgramCache(FProgramCache&&) = delete;`
- L120 _public prototype_ `~FProgramCache();`
- L122 _public prototype_ `FProgramCache& operator=(const FProgramCache&) = delete;`
- L123 _public prototype_ `FProgramCache& operator=(FProgramCache&&) = delete;`
- L126 _public prototype_ `void Clear(EClearFlags Flags);` — Clear cache.
- L128 _public prototype_ `bool IsSet(FCacheAddress Address);`
- L129 _public prototype_ `void UpdateHitCount(FCacheAddress Address, int8 Differential);`
- L130 _public prototype_ `void LockAddress(FCacheAddress Address);`
- L131 _public prototype_ `void MarkAddressToKeep(FCacheAddress Address);`
- L132 _public prototype_ `void SetAborted(FCacheAddress Address);`
- L133 _public prototype_ `bool IsAborted(FCacheAddress Address);`
- L135 _public prototype_ `[[nodiscard]] bool GetBoolIfSet(FCacheAddress Address, bool& bOutValue);`
- L136 _public prototype_ `[[nodiscard]] bool GetMaterialIfSet(FCacheAddress Address, TManagedPtr<const FMaterial>& bOutValue);`
- L138 _public prototype_ `[[nodiscard]] bool LoadBool(FCacheAddress Address);`
- L139 _public prototype_ `[[nodiscard]] float LoadScalar(FCacheAddress Address);`
- L140 _public prototype_ `[[nodiscard]] int32 LoadInt(FCacheAddress Address);`
- L141 _public prototype_ `[[nodiscard]] FVector4f LoadColor(FCacheAddress Address);`
- L142 _public prototype_ `[[nodiscard]] FMatrix44f LoadMatrix(FCacheAddress Address);`
- L143 _public prototype_ `[[nodiscard]] FProjector LoadProjector(FCacheAddress Address);`
- L144 _public prototype_ `[[nodiscard]] TManagedPtr<const FInstance> LoadInstance(FCacheAddress Address);`
- L145 _public prototype_ `[[nodiscard]] TManagedPtr<const FImage> LoadImage(FCacheAddress Address);`
- L146 _public prototype_ `[[nodiscard]] TManagedPtr<const FMesh> LoadMesh(FCacheAddress Address);`
- L147 _public prototype_ `[[nodiscard]] TManagedPtr<const FLOD> LoadLOD(FCacheAddress Address);`
- L148 _public prototype_ `[[nodiscard]] TManagedPtr<const FSkeletalMesh> LoadSkeletalMesh(FCacheAddress Address);`
- L149 _public prototype_ `[[nodiscard]] TManagedPtr<const FMaterial> LoadMaterial(FCacheAddress Address);`
- L150 _public prototype_ `[[nodiscard]] TManagedPtr<const FLayout> LoadLayout(FCacheAddress Address);`
- L151 _public prototype_ `[[nodiscard]] TManagedPtr<const String> LoadString(FCacheAddress Address);`
- L152 _public prototype_ `[[nodiscard]] TManagedPtr<const FExtensionData> LoadExtensionData(FCacheAddress Address);`
- L153 _public prototype_ `[[nodiscard]] TManagedPtr<const FInstancedStruct> LoadInstancedStruct(FCacheAddress Address);`
- L154 _public prototype_ `[[nodiscard]] FExtendedImageDesc LoadImageDesc(FCacheAddress Address);`
- L155 _public prototype_ `void LoadVoid(FCacheAddress Address);`
- L157 _public prototype_ `void StoreBool(FCacheAddress Address, bool Value);`
- L158 _public prototype_ `void StoreInt(FCacheAddress Address, int32 Value);`
- L159 _public prototype_ `void StoreScalar(FCacheAddress Address, float Value);`
- L160 _public prototype_ `void StoreColor(FCacheAddress Address, const FVector4f& Value);`
- L161 _public prototype_ `void StoreMatrix(FCacheAddress Address, const FMatrix44f& Value);`
- L162 _public prototype_ `void StoreMaterial(FCacheAddress Address, const TManagedPtr<const FMaterial>& Value);`
- L163 _public prototype_ `void StoreProjector(FCacheAddress Address, const FProjector& Value);`
- L164 _public prototype_ `void StoreInstancedStruct(FCacheAddress Address, const TManagedPtr<const FInstancedStruct>& Value);`
- L165 _public prototype_ `void StoreImage(FCacheAddress Address, const TManagedPtr<const FImage>& Value);`
- L166 _public prototype_ `void StoreMesh(FCacheAddress Address, const TManagedPtr<const FMesh>& Value);`
- L167 _public prototype_ `void StoreLOD(FCacheAddress Address, const TManagedPtr<const FLOD>& Value);`
- L168 _public prototype_ `void StoreSkeletalMesh(FCacheAddress Address, const TManagedPtr<const FSkeletalMesh>& Value);`
- L169 _public prototype_ `void StoreLayout(FCacheAddress Address, const TManagedPtr<const FLayout>& Value);`
- L170 _public prototype_ `void StoreString(FCacheAddress Address, const TManagedPtr<const String>& Value);`
- L171 _public prototype_ `void StoreInstance(FCacheAddress Address, const TManagedPtr<const FInstance>& Value);`
- L172 _public prototype_ `void StoreExtensionData(FCacheAddress Address, const TManagedPtr<const FExtensionData>& Value);`
- L173 _public prototype_ `void StoreImageDesc(FCacheAddress Address, const FExtendedImageDesc& Value);`
- L174 _public prototype_ `void StoreVoid(FCacheAddress Address);`
- L176 _public prototype_ `SSIZE_T TryFreeWeakMemory(SSIZE_T NumBytesToFree);`
- L178 _public prototype_ `[[nodiscard]] EAcquireSetResult TryAcquireCachedResultSet(TConstArrayView<FCacheAddress> AddressSet);`
- L179 _public prototype_ `[[nodiscard]] bool TryAcquireCachedResult(FCacheAddress Address);`
- L187 _public prototype_ `[[nodiscard]] bool AcquireCachedResultForScheduling(FCacheAddress Address);` — Tries to acquire any weak result. Returns if the operation needs to schedule. If the result is true, it is mandatory to to execute the operation at some point, otherwise other accesses to the same address will never complete.
- L192 _public prototype_ `[[nodiscard]] bool CheckHitCountsCleared() const;` — Check if all HitCount are zero. This is only for debug purposes.
- L199 _public prototype_ `[[nodiscard]] SSIZE_T CountBytes() const;` — Count number of bytes in the caches. This is only for debug purposes. Returns the number of internals and external bytes used by the caches.
- L206 _public prototype_ `int32 GetOrAddModifiedExecutionIndex(int32 TemplateExecutionIndex, uint16 RangeIndex, int32 RangeValue);` — Adds a copy the element at TemplateExecutionIndex modifing the RangeIndex to RangeValue. Returns the Id of the new ExecutionIndex.
- L211 _public prototype_ `int32 GetExecutionIndexValue(int32 ExecutionIndex, uint16 RangeIndex) const;` — Get the value of the index from the range index in the model.
- L216 _public prototype_ `Tasks::FTaskEvent& RegisterWaitEvent(const TCHAR* DebugName);` — Register WaitEvent
- L221 _public prototype_ `void TriggerWaitEvents();` — Trigger registered WaitEvents.

#### struct `UE::Mutable::Private::FProgramCache::FInternalsStorage`  
`struct alignas(InternalsAlign) FInternalsStorage`  
_L83-86_
- L85 _public member_ `uint8 Data[InternalsSize];`

#### enum `UE::Mutable::Private::FProgramCache::EClearFlags`  
`enum class EClearFlags`  
_L92-106_
- L94 _public enumerator_ `None = 0`
- L96 _public enumerator_ `FreeMemory = 1 << 0`
- L98 _public enumerator_ `Locked = 1 << 1`
- L99 _public enumerator_ `Unlocked = 1 << 2`
- L100 _public enumerator_ `Full = Locked | Unlocked`
- L102 _public enumerator_ `ImageDesc = 1 << 3`
- L103 _public enumerator_ `Void = 1 << 4`
- L105 _public enumerator_ `ForceClearMarkedToKeep = 1 << 5`

#### enum `UE::Mutable::Private::FProgramCache::EAcquireSetResult`  
`enum class EAcquireSetResult : uint8`  
_L108-113_
- L110 _public enumerator_ `Success = 0`
- L111 _public enumerator_ `Failure`
- L112 _public enumerator_ `Abort`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Tasks` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L57 _function_ `inline uint32 GetTypeHash(const FCacheAddress& Address)` (scope `UE::Mutable::Private`)
- L68 _function_ `FORCEINLINE bool operator==(FCacheAddress A, FCacheAddress B)` (scope `UE::Mutable::Private`)
- L73 _namespace_ `namespace ProgramCacheInternals` (scope `UE::Mutable::Private`)
- L225 _prototype_ `ENUM_CLASS_FLAGS(FProgramCache::EClearFlags);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Ptr.h` (Internal)


#### class `UE::Mutable::Private::Ptr`  
`template<class T> class Ptr`  
_L22-143_
- desc: \brief Intrusive smart pointer similar to the one in the boost libraries (intrusive_ptr<>) Some of the objects used by the runtime use reference counting to control their life-cycle. When an objects is returned in such a pointer, the user should keep this pointer valid while the data is in use, and clear it when done by assigning nullptr to it. The data returned in Ptr<T> pointers should never be directly deleted. The underlying lower-level pointer can be obtained with the get() method, but it should never be stored, since it will be valid only while there are valid Ptr<> to the same object. \ingroup runtime
- L26 _public function_ `Ptr( T* p = nullptr, bool add_ref = true )`
- L35 _public function_ `template<class U> Ptr( Ptr<U> const& rhs ) : m_ptr( rhs.get() )`
- L45 _public function_ `Ptr( Ptr const& rhs ) : m_ptr( rhs.m_ptr )` — Assign constructor
- L55 _public function_ `Ptr( Ptr&& rhs )` — Move constructor
- L61 _public function_ `~Ptr()`
- L69 _public function_ `template<class U> Ptr& operator=( Ptr<U> const& rhs )`
- L76 _public function_ `Ptr& operator=( Ptr const& rhs)` — Assign with copy
- L83 _public function_ `Ptr& operator=( Ptr&& rhs)` — Assign with move
- L94 _public function_ `Ptr& operator=( T* rhs)`
- L100 _public function_ `void reset()`
- L105 _public function_ `void reset( T* rhs )`
- L110 _public function_ `T* get() const`
- L115 _public function_ `T& operator*() const`
- L120 _public function_ `T* operator->() const`
- L126 _public function_ `inline explicit operator bool() const`
- L132 _public function_ `void swap( Ptr& rhs)`
- L141 _private member_ `T* m_ptr = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L146 _function_ `template<class T, class U> inline bool operator==( Ptr<T> const& a, Ptr<U> const& b )` (scope `UE::Mutable::Private`)
- L151 _function_ `template<class T, class U> inline bool operator!=( Ptr<T> const& a, Ptr<U> const& b )` (scope `UE::Mutable::Private`)
- L156 _function_ `template<class T, class U> inline bool operator==( Ptr<T> const& a, U* b )` (scope `UE::Mutable::Private`)
- L161 _function_ `template<class T, class U> inline bool operator!=( Ptr<T> const& a, U* b )` (scope `UE::Mutable::Private`)
- L166 _function_ `template<class T, class U> inline bool operator==( T* a, Ptr<U> const& b )` (scope `UE::Mutable::Private`)
- L171 _function_ `template<class T, class U> inline bool operator!=( T* a, Ptr<U> const& b )` (scope `UE::Mutable::Private`)
- L176 _function_ `template<class T> inline bool operator<( Ptr<T> const& a, Ptr<T> const& b )` (scope `UE::Mutable::Private`)
- L181 _function_ `template<class T> void swap( Ptr<T>& lhs, Ptr<T>& rhs )` (scope `UE::Mutable::Private`)
- L186 _function_ `template<class T, class U> Ptr<T> static_pointer_cast( Ptr<U> const & p)` (scope `UE::Mutable::Private`)
- L191 _function_ `template<class T, class U> Ptr<T> const_pointer_cast( Ptr<U> const & p)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Raster.h` (Internal)


#### class `UE::Mutable::Private::RasterVertex`  
`template<int NUM_INTERPOLATORS> class RasterVertex`  
_L13-24_
- L16 _public function_ `RasterVertex() : x(0), y(0)`
- L17 _public function_ `RasterVertex( float aX, float aY ) : x(aX), y(aY)`
- L20 _public member_ `float x,y;` — Raster coordinates of the vertex in image space.
- L20 _public member_ `float x,y;` — Raster coordinates of the vertex in image space.
- L23 _public member_ `float interpolators[NUM_INTERPOLATORS];` — Extra channels to interpolate accross de triangles.

#### class `UE::Mutable::Private::ColorPixelProcessor`  
`class ColorPixelProcessor`  
_L29-43_
- desc: Example rasterizer pixel processor. It only takes the color interpolated and assigns it to the pixel.
- L32 _public function_ `inline void ProcessPixel(uint8* pBufferPos, float interpolatedValues[3]) const`
- L39 _public function_ `inline void operator()(uint8* BufferPos, float InterpolatedValues[3]) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L46 _typedef_ `template<int32 NumInterpolatedValues> using TTriangleRasterPixelProcRefType = TFunctionRef<void(uint8*, float[NumInterpolatedValues])>;` (scope `UE::Mutable::Private`)
- L54 _function_ `template<int32 NUM_INTERPOLATORS, typename INT=int64> void Triangle( uint8* Buffer, int32 BufferSize, int Width, int Height, int PixelSize , const RasterVertex<NUM_INTERPOLATORS> &av1 , const RasterVertex<NUM_INTERPOLATORS> &av2 , const RasterVertex<NUM_INTERPOLATORS> &av3 , TTriangleRasterPixelProcRefType<NUM_INTERPOLATORS> PixelProc , bool cullBackface = true )` (scope `UE::Mutable::Private`) — Templatized rasterizer. It is not very efficient on the interpolating side, but the cost per pixel is supposed to be huge compared to the raster process (for lightmaps or normalmaps). TODO Optimize anyway. TODO Option for two sided? right now it culls back facing.

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/RefCounted.h` (Internal)


#### class `UE::Mutable::Private::RefCounted`  
`class RefCounted`  
_L22-65_
- desc: Base class for all reference counted objects. Any subclass of this class can be managed using smart pointers through the Ptr<T> template. \warning This base allow multi-threaded manipulation of smart pointers, since the count increments and decrements are atomic.
- L26 _public function_ `inline void IncRef() const`
- L31 _public function_ `inline void DecRef() const`
- L42 _public function_ `inline bool IsUnique() const`
- L47 _public prototype_ `RefCounted(const RefCounted&) = delete;`
- L48 _public prototype_ `RefCounted(const RefCounted&&) = delete;`
- L49 _public prototype_ `RefCounted& operator=(const RefCounted&) = delete;`
- L50 _public prototype_ `RefCounted& operator=(const RefCounted&&) = delete;`
- L54 _protected function_ `RefCounted()`
- L59 _protected prototype_ `inline virtual ~RefCounted() = default;`
- L63 _private member_ `mutable std::atomic<int32> m_refCount;`

#### class `UE::Mutable::Private::FResource`  
`class FResource`  
_L82-92_
- L87 _public prototype_ `virtual int32 GetDataSize() const = 0;` — Return the size in bytes of all the LODs of the image.
- L90 _public prototype_ `virtual ~FResource() = default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L68 _function_ `inline void mutable_ptr_add_ref(const RefCounted* p)` (scope `UE::Mutable::Private`)
- L74 _function_ `inline void mutable_ptr_release(const RefCounted* p)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Registry.h` (Internal)


#### class `TRegistry`  
`template <typename KeyType, typename ValueType> class TRegistry : public TSharedFromThis<TRegistry<KeyType, ValueType>>`  
_L10-230_
- inherits: `TSharedFromThis<TRegistry<KeyType,ValueType>>`
- L110 _public function_ `friend uint32 GetTypeHash(const FHandle& Handle)`
- L136 _private function_ `friend uint32 GetTypeHash(const FKeyContainer& KeyContainer)`
- L152 _public function_ `FHandle Add(const KeyType& Key, const ValueType& Value)`
- L174 _public function_ `ValueType* Find(const KeyType& Key)`
- L189 _private function_ `const KeyType& GetKey(int32 Id) const`
- L194 _private function_ `const ValueType& GetValue(int32 Id) const`
- L199 _private function_ `void Increment(uint32 Id)`
- L207 _private function_ `void Decrement(uint32 Id)`
- L221 _private member_ `static constexpr uint32 ID_NONE = TNumericLimits<uint32>::Max();`
- L224 _private member_ `uint32 GlobalId = 0;` — Global incremental Id counter.
- L226 _private member_ `TMap<uint32, FEntry> Entries;`
- L227 _private member_ `TMap<FKeyContainer, uint32> KeyIndex;`
- L229 _private member_ `FCriticalSection CriticalSection;`

#### class `TRegistry::FHandle`  
`class FHandle`  
_L13-119_
- L18 _public prototype_ `FHandle() = default;`
- L21 _private function_ `FHandle(uint32 InId, const TWeakPtr<TRegistry>& InWeakRegistry)`
- L28 _public function_ `FHandle(const FHandle& Other)`
- L33 _public function_ `FHandle(FHandle&& Other)`
- L38 _public function_ `operator bool() const`
- L43 _public function_ `FHandle& operator=(const FHandle& Other)`
- L56 _public function_ `FHandle& operator=(FHandle&& Other)`
- L67 _public function_ `bool operator==(const FHandle& Other) const`
- L72 _public function_ `~FHandle()`
- L80 _public function_ `const KeyType* GetKey() const`
- L92 _public function_ `const ValueType* GetValue() const`
- L105 _public function_ `FString ToString() const`
- L116 _private member_ `uint32 Id = ID_NONE;`
- L118 _private member_ `TWeakPtr<TRegistry> WeakRegistry;`

#### struct `TRegistry::FKeyContainer`  
`struct FKeyContainer`  
_L122-140_
- L124 _public member_ `TSharedRef<KeyType> Key;`
- L126 _public function_ `bool operator==(const FKeyContainer& Other) const`
- L131 _public function_ `bool operator==(const KeyType& Other) const`

#### struct `TRegistry::FEntry`  
`struct FEntry`  
_L142-149_
- L144 _public member_ `uint32 RefCount = 0;`
- L146 _public member_ `FKeyContainer KeyContainer;`
- L148 _public member_ `ValueType Value;`

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/ResourceID.h` (Internal)


#### struct `UE::Mutable::Private::FGeneratedImageKey`  
`struct FGeneratedImageKey`  
_L13-20_
- desc: Image
- L15 _public member_ `FOperation::ADDRESS Address = 0;`
- L17 _public member_ `TMemoryTrackedArray<uint8> ParameterValuesBlob;`
- L19 _public prototype_ `bool operator==(const FGeneratedImageKey&) const = default;`

#### struct `UE::Mutable::Private::FGeneratedImageData`  
`struct FGeneratedImageData`  
_L22-24_

#### struct `UE::Mutable::Private::FGeneratedMaterialKey`  
`struct FGeneratedMaterialKey`  
_L35-42_
- desc: Material
- L37 _public member_ `FOperation::ADDRESS Address = 0;`
- L39 _public member_ `TMemoryTrackedArray<uint8> ParameterValuesBlob;`
- L41 _public prototype_ `bool operator==(const FGeneratedMaterialKey&) const = default;`

#### struct `UE::Mutable::Private::FGeneratedMaterialData`  
`struct FGeneratedMaterialData`  
_L44-46_

#### struct `UE::Mutable::Private::FGeneratedSkeletalMeshKey`  
`struct FGeneratedSkeletalMeshKey`  
_L58-65_
- desc: SkeletalMesh
- L60 _public member_ `FOperation::ADDRESS Address = 0;`
- L62 _public member_ `TMemoryTrackedArray<uint8> ParameterValuesBlob;`
- L64 _public prototype_ `bool operator==(const FGeneratedSkeletalMeshKey&) const = default;`

#### struct `UE::Mutable::Private::FGeneratedSkeletalMeshData`  
`struct FGeneratedSkeletalMeshData`  
_L67-69_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L26 _prototype_ `uint32 GetTypeHash(const FGeneratedImageKey& Key);` (scope `UE::Mutable::Private`)
- L28 _typedef_ `typedef TRegistry<FGeneratedImageKey, FGeneratedImageData>::FHandle FImageId;` (scope `UE::Mutable::Private`)
- L30 _typedef_ `typedef TRegistry<FGeneratedImageKey, FGeneratedImageData> FImageIdRegistry;` (scope `UE::Mutable::Private`)
- L32 _prototype_ `uint32 GetTypeHashPersistent(const FImageId& Id);` (scope `UE::Mutable::Private`)
- L48 _prototype_ `uint32 GetTypeHash(const FGeneratedMaterialKey& Key);` (scope `UE::Mutable::Private`)
- L50 _typedef_ `typedef TRegistry<FGeneratedMaterialKey, FGeneratedMaterialData>::FHandle FMaterialId;` (scope `UE::Mutable::Private`)
- L52 _typedef_ `typedef TRegistry<FGeneratedMaterialKey, FGeneratedMaterialData> FMaterialIdRegistry;` (scope `UE::Mutable::Private`)
- L54 _prototype_ `uint32 GetTypeHashPersistent(const FMaterialId& Id);` (scope `UE::Mutable::Private`)
- L71 _prototype_ `uint32 GetTypeHash(const FGeneratedSkeletalMeshKey& Key);` (scope `UE::Mutable::Private`)
- L73 _typedef_ `typedef TRegistry<FGeneratedSkeletalMeshKey, FGeneratedSkeletalMeshData>::FHandle FSkeletalMeshId;` (scope `UE::Mutable::Private`)
- L75 _typedef_ `typedef TRegistry<FGeneratedSkeletalMeshKey, FGeneratedSkeletalMeshData> FSkeletalMeshIdRegistry;` (scope `UE::Mutable::Private`)
- L77 _prototype_ `uint32 GetTypeHashPersistent(const FSkeletalMeshId& Id);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/RomManager.h` (Internal)


#### struct `UE::Mutable::Private::MemoryCounters::FStreamingMemoryCounter`  
`struct FStreamingMemoryCounter`  
_L18-21_
- L20 _public prototype_ `static std::atomic<SSIZE_T>& Get();`

#### class `UE::Mutable::Private::FRomManager`  
`class FRomManager`  
_L26-71_
- L29 _public prototype_ `FRomManager(FModel& InModel);`
- L31 _public prototype_ `void Serialise(FModelWriter& Streamer, bool bDropData);`
- L34 _public prototype_ `template<typename Type> void SetRom(uint32 RomIndex, const TManagedPtr<const Type>& Rom);`
- L37 _public prototype_ `template<typename Type> Tasks::TTask<TManagedPtr<const Type>> GetRom(uint32 RomIndex, TSharedRef<FModelReader> ModelReader);`
- L39 _public prototype_ `void UnloadRoms();`
- L41 _public prototype_ `int64 EnsureBudgetBelow(int64 BytesToFree);`
- L43 _public prototype_ `int64 GetRomBytes() const;`
- L46 _private prototype_ `uint32 GetRomDiskSize(int32 RomIndex) const;`
- L48 _private member_ `const FModel& Model;`
- L50 _private member_ `mutable FMutex CriticalSection;`
- L60 _private member_ `TMemoryTrackedArray<FRomWeight> RomWeights;`
- L65 _private member_ `mutable TMap<uint32, Tasks::TTask<TManagedPtr<const FMesh>>> ConstantMeshesStreamed;` — Constant mesh data is split in 2 sets: ConstantMeshesStreamed constains data that is streamed in and out. Index with FConstantResourceIndex::Index, when Streamable is 1. This part is empty for an unused Model, and shouldn't be serialised.
- L70 _private member_ `mutable TMap<uint32, Tasks::TTask<TManagedPtr<const FImage>>> ConstantImageLODsStreamed;` — Constant image mip data is split in 2 sets: ConstantImageLODsStreamed constains data that is streamed in and out. Index with FConstantResourceIndex::Index, when Streamable is 1. This part is empty for an unused Model, and shouldn't be serialised.

#### struct `UE::Mutable::Private::FRomManager::FRomWeight`  
`struct FRomWeight`  
_L52-58_
- L54 _public member_ `uint32 RomIndex = INDEX_NONE;`
- L55 _public member_ `uint32 RomTick = 0;`
- L57 _public prototype_ `bool operator<(const FRomWeight& Other) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _namespace_ `namespace MemoryCounters` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Serialisation.h` (Internal)


#### class `UE::Mutable::Private::FModelReader`  
`class FModelReader`  
_L53-100_
- L62 _public prototype_ `virtual ~FModelReader() = default;` — Ensure virtual destruction.
- L70 _public typedef_ `typedef int32 FOperationID;` — Identifier of reading data operations sent to this interface. Negative values indicate an error.
- L72 _public prototype_ `virtual bool DoesBlockExist(const FModel*, uint32 BlockKey) = 0;`
- L85 _public prototype_ `virtual FOperationID BeginReadBlock(const FModel*, uint32 BlockKey, void* Buffer, uint64 Size, EDataType DataType, TFunction<void(bool bSuccess)>* CompletionCallback = nullptr) = 0;` — \brief Start a data request operation. \param Model. \param BlockKey key identifying the model data fragment that is requested. This key interpretation depends on the implementation of the ModelStreamer, \param Buffer is an already-allocated buffer big enough to receive the expected data. \param size is the size of the pBuffer buffer, which must match the size of the data requested with the key identifiers. \param CompletionCallback Optional callback. Copied inside the called function. Will always be called. \return a previously unused identifier, now used for this operation, that can be used in calls to the other methods of this interface. If the return value is negative it indicates an unrecoverable error.
- L92 _public prototype_ `virtual bool IsReadCompleted(FOperationID) = 0;` — Check if a data request operation has been completed. This is a weak check than *may* return true if the given operation has completed, but it is not mandatory. It is used as a hint by the System to optimise its opertaions. There is no guarantee that this method will ever be called, and it is safe to always return false.
- L99 _public prototype_ `virtual bool EndRead(FOperationID) = 0;` — Complete a data request operation.This method has to block until a data request issued with BeginReadBlock has been completed. After returning from this call, the ID cannot be used any more to identify the same operation and becomes free. \return true if the data was loaded successfully.

#### class `UE::Mutable::Private::FModelWriter`  
`class FModelWriter`  
_L104-130_
- L113 _public prototype_ `virtual ~FModelWriter() = default;` — Ensure virtual destruction.
- L120 _public prototype_ `virtual void OpenWriteFile(uint32 BlockKey, bool bIsStreamable) = 0;`
- L123 _public prototype_ `virtual void Write(const void* Buffer, uint64 Size) = 0;`
- L127 _public prototype_ `virtual void CloseWriteFile() = 0;` — \brief Close the file open for writing in a previous call to OpenWriteFile in this object.

#### class `UE::Mutable::Private::FInputStream`  
`class FInputStream`  
_L134-146_
- desc: Interface for any input stream to be use with InputArchives.
- L139 _public prototype_ `virtual ~FInputStream() = default;` — Ensure virtual destruction.
- L145 _public prototype_ `virtual void Read( void* Data, uint64 Size ) = 0;` — Read a byte buffer \param pData destination buffer, must have at least size bytes allocated. \param size amount of bytes to read from the stream.

#### class `UE::Mutable::Private::FOutputStream`  
`class FOutputStream`  
_L150-163_
- desc: Interface for any output stream to be used with OutputArchives.
- L155 _public prototype_ `virtual ~FOutputStream() = default;` — Ensure virtual destruction.
- L161 _public prototype_ `virtual void Write( const void* Data, uint64 Size ) = 0;` — Write a byte buffer \param pData source buffer where data will be read from. \param size amount of data to write to the stream.

#### class `UE::Mutable::Private::FInputArchive`  
`class FInputArchive`  
_L167-185_
- desc: Archive containing data to be deserialised.
- L174 _public prototype_ `FInputArchive( FInputStream* );` — Construct form an input stream.The stream will not be owned by the archive and the caller must make sure it is not modified or destroyed while serialisation is happening.
- L177 _public prototype_ `virtual ~FInputArchive() = default;` — Ensure virtual destruction.
- L180 _public member_ `FInputStream* Stream = nullptr;` — Not owned.
- L183 _public member_ `TArray< TManagedPtr<void> > History;` — Already read pointers.

#### class `UE::Mutable::Private::FOutputArchive`  
`class FOutputArchive`  
_L189-204_
- desc: Archive where data can be serialised to.
- L196 _public prototype_ `FOutputArchive( FOutputStream* );` — Construct form an output stream.The stream will not be owned by the archive and the caller must make sure it is not modified or destroyed while serialisation is happening.
- L199 _public member_ `FOutputStream* Stream = nullptr;` — Not owned.
- L202 _public member_ `TMap< const void*, int32 > History;` — Already written pointers and their ids.

#### class `UE::Mutable::Private::FOutputMemoryStream`  
`class FOutputMemoryStream : public FOutputStream`  
_L208-237_
- inherits: `FOutputStream`
- L215 _public prototype_ `FOutputMemoryStream( uint64 Reserve = 0 );` — Create the stream with an optional buffer size in bytes. The internal buffer will be enlarged as much as necessary.
- L218 _public prototype_ `virtual void Write( const void* Data, uint64 Size ) override;` — FOutputStream interface
- L225 _public prototype_ `const uint8* GetBuffer() const;` — Get the serialised data buffer pointer. This pointer invalidates after a Write operation has been done, and you need to get it again.
- L228 _public prototype_ `int32 GetBufferSize() const;` — Get the amount of data in the stream, in bytes.
- L231 _public prototype_ `void Reset();` — Clear the internal buffer.
- L235 _private member_ `TArray64<uint8> Buffer;`

#### class `UE::Mutable::Private::FOutputSizeStream`  
`class FOutputSizeStream : public FOutputStream`  
_L241-257_
- inherits: `FOutputStream`
- desc: This stream doesn't store any data: it just counts the amount of data serialised.
- L246 _public prototype_ `void Write(const void* Data, uint64 Size) override;` — FOutputStream interface
- L251 _public prototype_ `uint64 GetBufferSize() const;` — Get the amount of data serialised, in bytes.
- L255 _private member_ `uint64 WrittenBytes = 0;`

#### class `UE::Mutable::Private::FOutputHashStream`  
`class FOutputHashStream : public FOutputStream`  
_L261-274_
- inherits: `FOutputStream`
- desc: This stream doesn't store any data: it just calculates of a hash of the data as it receives it.
- L265 _public prototype_ `void Write(const void* Data, uint64 Size) override;` — FOutputStream interface
- L270 _public prototype_ `uint64 GetHash() const;` — Return the hash of the data written so far.
- L273 _private member_ `uint64 Hash = 0;`

#### class `UE::Mutable::Private::FInputMemoryStream`  
`class FInputMemoryStream : public FInputStream`  
_L401-427_
- inherits: `FInputStream`
- L412 _public prototype_ `FInputMemoryStream( const void* pBuffer, uint64 size );` — Create the stream using an external buffer. The buffer will not be owned by this object, so it cannot be deallocated while this objects is in use.
- L418 _public prototype_ `void Read( void* pData, uint64 size ) override;`
- L423 _private member_ `const void* Buffer = nullptr;`
- L424 _private member_ `uint64 Size = 0;`
- L425 _private member_ `uint64 Pos = 0;`

#### struct `UE::Mutable::Private::TVariantLoadFromInputArchiveCaller`  
`template <typename T, typename VariantType> struct TVariantLoadFromInputArchiveCaller`  
_L481-489_
- L484 _public function_ `static void Load(FInputArchive& Ar, VariantType& OutVariant)` — Default construct the type and load it from the FArchive

#### struct `UE::Mutable::Private::TVariantLoadFromInputArchiveLookup`  
`template <typename... Ts> struct TVariantLoadFromInputArchiveLookup`  
_L493-505_
- L495 _public typedef_ `using VariantType = TVariant<Ts...>;`
- L499 _public function_ `static void Load(SIZE_T TypeIndex, FInputArchive& Ar, VariantType& OutVariant)` — Load the type at the specified index from the FArchive and emplace it into the TVariant

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Mutable` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L37 _macro_ `#define MUTABLE_DEFINE_POD_SERIALISABLE(Type) \`
- L41 _macro_ `#define MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(Type) \`
- L47 _macro_ `#define MUTABLE_DEFINE_ENUM_SERIALISABLE(Type) \`
- L278 _function_ `template<typename Type> void operator<<(FOutputArchive& Arch, const Type& Value)` (scope `UE::Mutable::Private`)
- L284 _function_ `template<typename Type> void operator>>(FInputArchive& Arch, Type& Value)` (scope `UE::Mutable::Private`)
- L289 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(float);` (scope `UE::Mutable::Private`)
- L290 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(double);` (scope `UE::Mutable::Private`)
- L292 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(int8);` (scope `UE::Mutable::Private`)
- L293 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(int16);` (scope `UE::Mutable::Private`)
- L294 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(int32);` (scope `UE::Mutable::Private`)
- L295 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(int64);` (scope `UE::Mutable::Private`)
- L297 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(uint8);` (scope `UE::Mutable::Private`)
- L298 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(uint16);` (scope `UE::Mutable::Private`)
- L299 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(uint32);` (scope `UE::Mutable::Private`)
- L300 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(uint64);` (scope `UE::Mutable::Private`)
- L302 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FUintVector2);` (scope `UE::Mutable::Private`)
- L303 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FIntVector2);` (scope `UE::Mutable::Private`)
- L304 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(UE::Math::TIntVector2<uint16>);` (scope `UE::Mutable::Private`)
- L305 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(UE::Math::TIntVector2<int16>);` (scope `UE::Mutable::Private`)
- L306 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FVector2f);` (scope `UE::Mutable::Private`)
- L307 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FVector4f);` (scope `UE::Mutable::Private`)
- L308 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FMatrix44f);` (scope `UE::Mutable::Private`)
- L309 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FRichCurveKey);` (scope `UE::Mutable::Private`)
- L311 _prototype_ `MUTABLE_DEFINE_POD_SERIALISABLE(FGuid);` (scope `UE::Mutable::Private`)
- L313 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(float);` (scope `UE::Mutable::Private`)
- L314 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(double);` (scope `UE::Mutable::Private`)
- L315 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(uint8);` (scope `UE::Mutable::Private`)
- L316 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(uint16);` (scope `UE::Mutable::Private`)
- L317 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(uint32);` (scope `UE::Mutable::Private`)
- L318 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(uint64);` (scope `UE::Mutable::Private`)
- L319 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(int8);` (scope `UE::Mutable::Private`)
- L320 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(int16);` (scope `UE::Mutable::Private`)
- L321 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(int32);` (scope `UE::Mutable::Private`)
- L322 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(int64);` (scope `UE::Mutable::Private`)
- L324 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FVector2f);` (scope `UE::Mutable::Private`)
- L325 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FMatrix44f);` (scope `UE::Mutable::Private`)
- L326 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FIntVector2);` (scope `UE::Mutable::Private`)
- L327 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(TCHAR);` (scope `UE::Mutable::Private`)
- L328 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FRichCurveKey);` (scope `UE::Mutable::Private`)
- L330 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FUintVector2);` (scope `UE::Mutable::Private`)
- L331 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(UE::Math::TIntVector2<uint16>);` (scope `UE::Mutable::Private`)
- L332 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(UE::Math::TIntVector2<int16>);` (scope `UE::Mutable::Private`)
- L333 _prototype_ `MUTABLE_DEFINE_POD_VECTOR_SERIALISABLE(FVector4f);` (scope `UE::Mutable::Private`)
- L336 _prototype_ `void operator<<(FOutputArchive&, const FString&);` (scope `UE::Mutable::Private`)
- L337 _prototype_ `void operator>>(FInputArchive&, FString&);` (scope `UE::Mutable::Private`)
- L340 _prototype_ `void operator<<(FOutputArchive&, const FRichCurve&);` (scope `UE::Mutable::Private`)
- L341 _prototype_ `void operator>>(FInputArchive&, FRichCurve&);` (scope `UE::Mutable::Private`)
- L345 _prototype_ `void operator<<(FOutputArchive&, const FName&);` (scope `UE::Mutable::Private`)
- L346 _prototype_ `void operator>>(FInputArchive&, FName&);` (scope `UE::Mutable::Private`)
- L349 _prototype_ `void operator<<(FOutputArchive&, const FMeshToMeshVertData&);` (scope `UE::Mutable::Private`)
- L350 _prototype_ `void operator>>(FInputArchive&, FMeshToMeshVertData&);` (scope `UE::Mutable::Private`)
- L354 _function_ `template<typename T, typename Alloc> void operator<<(FOutputArchive& Arch, const TArray<T, Alloc>& V)` (scope `UE::Mutable::Private`)
- L366 _function_ `template<typename T, typename Alloc> void operator>>(FInputArchive& Arch, TArray<T, Alloc>& V)` (scope `UE::Mutable::Private`)
- L380 _prototype_ `void operator<<(FOutputArchive&, const bool&);` (scope `UE::Mutable::Private`) — Bool size is not a standard
- L381 _prototype_ `void operator>>(FInputArchive&, bool&);` (scope `UE::Mutable::Private`)
- L385 _function_ `template<typename T> void operator<<(FOutputArchive& Arch, const TStrongObjectPtr<T>& V)` (scope `UE::Mutable::Private`)
- L391 _function_ `template<typename T> void operator>>(FInputArchive& Arch, TStrongObjectPtr<T>& V)` (scope `UE::Mutable::Private`)
- L396 _prototype_ `void operator<<(FOutputArchive& Arch, const TManagedPtr<const FInstancedStruct>& V);` (scope `UE::Mutable::Private`)
- L397 _prototype_ `void operator>>(FInputArchive& Arch, TManagedPtr<const FInstancedStruct>& V);` (scope `UE::Mutable::Private`)
- L430 _macro_ `#define MUTABLE_IMPLEMENT_POD_SERIALISABLE(Type) \`
- L442 _macro_ `#define MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(Type) \`
- L468 _function_ `template <typename... Ts> void operator<<(FOutputArchive& Ar, const TVariant<Ts...>& Variant)` (scope `UE::Mutable::Private`) — TVariant custom serialize. Based on the default serialization.
- L474 _function_ `` (scope `UE::Mutable::Private::operator <<`)
- L509 _function_ `template <typename... Ts> void operator>>(FInputArchive& Ar, TVariant<Ts...>& Variant)` (scope `UE::Mutable::Private`)
- L518 _macro_ `#define MUTABLE_IMPLEMENT_ENUM_SERIALISABLE(Type) \`
- L533 _function_ `template<typename T0, typename T1> inline void operator<<(FOutputArchive& Arch, const std::pair<T0, T1>& V)` (scope `UE::Mutable::Private`)
- L540 _function_ `template<typename T0, typename T1> inline void operator>>(FInputArchive& Arch, std::pair<T0, T1>& V)` (scope `UE::Mutable::Private`)
- L547 _function_ `template<typename T, uint32 Size, uint32 Align> void operator<<(FOutputArchive& Arch, const TStaticArray<T, Size, Align>& V)` (scope `UE::Mutable::Private`)
- L556 _function_ `template<typename T, uint32 Size, uint32 Align> void operator>>(FInputArchive& Arch, TStaticArray<T, Size, Align>& V)` (scope `UE::Mutable::Private`)
- L567 _function_ `template< typename K, typename T > inline void operator<< (FOutputArchive& Arch, const TMap<K, T>& V)` (scope `UE::Mutable::Private`)
- L578 _function_ `template< typename K, typename T > inline void operator>> (FInputArchive& Arch, TMap<K, T>& V)` (scope `UE::Mutable::Private`)
- L595 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(float);` (scope `UE::Mutable::Private`) — Unreal POD Serializables
- L596 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(double);` (scope `UE::Mutable::Private`)
- L597 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(uint8);` (scope `UE::Mutable::Private`)
- L598 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(uint16);` (scope `UE::Mutable::Private`)
- L599 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(uint32);` (scope `UE::Mutable::Private`)
- L600 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(uint64);` (scope `UE::Mutable::Private`)
- L601 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(int8);` (scope `UE::Mutable::Private`)
- L602 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(int16);` (scope `UE::Mutable::Private`)
- L603 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(int32);` (scope `UE::Mutable::Private`)
- L604 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(int64);` (scope `UE::Mutable::Private`)
- L605 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(TCHAR);` (scope `UE::Mutable::Private`)
- L607 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FIntVector2);` (scope `UE::Mutable::Private`)
- L608 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FUintVector2);` (scope `UE::Mutable::Private`)
- L609 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(UE::Math::TIntVector2<uint16>);` (scope `UE::Mutable::Private`)
- L610 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(UE::Math::TIntVector2<int16>);` (scope `UE::Mutable::Private`)
- L611 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FVector2f);` (scope `UE::Mutable::Private`)
- L612 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FVector4f);` (scope `UE::Mutable::Private`)
- L613 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FMatrix44f);` (scope `UE::Mutable::Private`)
- L614 _prototype_ `MUTABLE_IMPLEMENT_POD_VECTOR_SERIALISABLE(FRichCurveKey);` (scope `UE::Mutable::Private`)
- L620 _function_ `inline void operator<< (FOutputArchive& Arch, const TManagedPtr<const T>& Ptr)` (scope `UE::Mutable::Private`)
- L647 _function_ `inline void operator>> (FInputArchive& Arch, TManagedPtr<const T>& Ptr)` (scope `UE::Mutable::Private`)
- L684 _function_ `template< typename T > inline void operator<< ( FOutputArchive& arch, const Ptr<T>& p )` (scope `UE::Mutable::Private`)
- L690 _function_ `template< typename T > inline void operator>> ( FInputArchive& arch, Ptr<T>& p )` (scope `UE::Mutable::Private`)
- L699 _function_ `template<typename T0, typename T1> inline void operator<<(FOutputArchive& arch, const TPair<T0,T1>& v)` (scope `UE::Mutable::Private`)
- L705 _function_ `template<typename T0, typename T1> inline void operator>>(FInputArchive& arch, TPair<T0, T1>& v)` (scope `UE::Mutable::Private`)
- L715 _function_ `template< typename T > inline void operator<< (FOutputArchive& arch, const UE::Math::TQuat<T>& v)` (scope `UE::Mutable::Private`) — TODO: As POD?
- L724 _function_ `template< typename T > inline void operator>> (FInputArchive& arch, UE::Math::TQuat<T>& v)` (scope `UE::Mutable::Private`)
- L736 _function_ `template< typename T > inline void operator<< (FOutputArchive& arch, const UE::Math::TVector<T>& v)` (scope `UE::Mutable::Private`) — TODO: As POD?
- L744 _function_ `template< typename T > inline void operator>> (FInputArchive& arch, UE::Math::TVector<T>& v)` (scope `UE::Mutable::Private`)
- L754 _function_ `template< typename T > inline void operator<< (FOutputArchive& arch, const UE::Math::TRotator<T>& R)` (scope `UE::Mutable::Private`)
- L762 _function_ `template< typename T > inline void operator>> (FInputArchive& arch, UE::Math::TRotator<T>& R)` (scope `UE::Mutable::Private`)
- L772 _function_ `template< typename T > inline void operator<< (FOutputArchive& arch, const UE::Math::TTransform<T>& v)` (scope `UE::Mutable::Private`)
- L780 _function_ `template< typename T > inline void operator>> (FInputArchive& arch, UE::Math::TTransform<T>& v)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Settings.h` (Internal)


#### class `UE::Mutable::Private::FSettings`  
`class FSettings`  
_L14-48_
- desc: Settings class that can be used to create a customised System instance.
- L19 _public prototype_ `void SetProfile( bool bEnabled );` — Record internal profiling data. Disabled by default.
- L26 _public prototype_ `void SetWorkingMemoryBytes( uint64 Bytes );` — Limit the maximum memory in bytes used by the mutable core.A low value will force more streaming and higher instance construction times, but will use less memory while building objects. Defaults to 0, which disables the limit.
- L40 _public prototype_ `void SetImageCompressionQuality( int32 Quality );` — Set the quality for the image compression algorithms. \param quality Quality level of the compression. Higher quality increases the instance generation time. The value is in the range 0 to 4 with 0 being the fastest. It defaults to 0, which is the fastes for runtime. Tools may want ot set it higher, and low performance profiles to lower. Genreal rules are: 0 - Fastest for runtime 1 - Best for runtime 2 - Fast for tools 3 - Best for tools 4 - Maximum, with no time limits.
- L44 _public member_ `uint64 WorkingMemoryBytes = 0;`
- L45 _public member_ `int32 ImageCompressionQuality = 0;`
- L46 _public member_ `bool bProfile = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/SkeletalMesh.h` (Internal)


#### class `UE::Mutable::Private::FSkeletalMesh`  
`class FSkeletalMesh : public FResource`  
_L18-73_
- inherits: `FResource`
- L22 _public function_ `virtual int32 GetDataSize() const override` — FResource interface
- L24 _public function_ `TManagedPtr<FSkeletalMesh> Clone() const`
- L53 _public member_ `TPassthroughObjectPtr<USkeletalMesh> PassthroughObject;`
- L55 _public member_ `TArray<TManagedPtr<const FLOD>> LODs;`
- L57 _public member_ `TArray<TVariant<FOperation::ADDRESS, TManagedPtr<const FMaterial>>> MaterialSlotMaterials;`
- L58 _public member_ `TArray<FName> MaterialSlotNames;`
- L59 _public member_ `TArray<uint32> MaterialSlotIds;`
- L61 _public member_ `uint8 FirstLODAvailable = MAX_uint8;` — TODO SKMPIN SKO Only
- L62 _public member_ `uint8 FirstLODResident = MAX_uint8;` — TODO SKMPIN SKO Only
- L64 _public member_ `FPerPlatformInt MinLODs;`
- L65 _public member_ `FPerQualityLevelInt MinQualityLevelLODs;`
- L67 _public member_ `TArray<float> ScreenSize;`
- L68 _public member_ `TArray<float> LODHysteresis;`
- L69 _public member_ `TArray<bool> bSupportUniformlyDistributedSampling;`
- L70 _public member_ `TArray<bool> bAllowCPUAccess;`
- L72 _public member_ `FName Name;` — TODO SKMPIN SKO Only

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Skeleton.h` (Internal)


#### union `UE::Mutable::Private::FBoneIdOrIndex`  
`union FBoneIdOrIndex`  
_L19-38_
- L21 _public member_ `uint32 Id;`
- L22 _public member_ `int32 Index;`
- L24 _public function_ `inline void Serialise(FOutputArchive& Arch) const`
- L29 _public function_ `inline void Unserialise(FInputArchive& Arch)`
- L34 _public function_ `inline bool operator==(const FBoneIdOrIndex& Other) const`

#### class `UE::Mutable::Private::FSkeleton`  
`class FSkeleton`  
_L41-91_
- desc: Skeleton object.
- L50 _public prototype_ `TManagedPtr<FSkeleton> Clone() const;` — Deep clone this skeleton.
- L53 _public prototype_ `static void Serialise( const FSkeleton*, FOutputArchive& );` — Serialisation
- L54 _public prototype_ `static TManagedPtr<FSkeleton> StaticUnserialise( FInputArchive& );`
- L61 _public prototype_ `int32 AddBone(const FName InBoneName, const int16 InParentIndex);`
- L62 _public prototype_ `int32 FindOrAddBone(const FName InBoneName, const int16 InParentIndex);`
- L64 _public prototype_ `int32 GetNumBones() const;`
- L69 _public member_ `TArray<FName> BoneNames;` — FNames of the bones. Serialized in the program as ConstantNames.
- L72 _public member_ `TArray<uint32> BoneIds;` — FName Id in the ConstantNames map.
- L76 _public member_ `TArray<int16> BoneParents;` — For each bone, index of the parent bone in the bone vectors. -1 means no parent. This array must have the same size than the m_bones array.
- L79 _public prototype_ `void Serialise(FOutputArchive&) const;`
- L82 _public prototype_ `void Unserialise(FInputArchive&);`
- L85 _public function_ `inline bool operator==(const FSkeleton& Other) const`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/System.h` (Internal)


#### enum `ETextureCompressionStrategy`  
`enum class ETextureCompressionStrategy : uint8`  
_L51-61_
- reflection: `UENUM()`
- desc: Despite being an UEnum, this is not always version-serialized (in MutableTools). Beware of changing the enum options or order.
- L54 _public enumerator_ `None` — Don't change the generated format.
- L57 _public enumerator_ `DontCompressRuntime` — If a texture depends on run-time parameters for an object state, don't compress.
- L60 _public enumerator_ `NeverCompress` — Never compress the textures for this state.

#### enum `UE::Mutable::Private::EExecutionStrategy`  
`enum class EExecutionStrategy : uint8`  
_L77-90_
- L80 _public enumerator_ `None = 0` — Undefined.
- L83 _public enumerator_ `MinimizeMemory` — Always try to run operations that reduce working memory first.
- L86 _public enumerator_ `MaximizeConcurrency` — Always try to run operations that unlock more operations first.
- L89 _public enumerator_ `Count` — Utility value with the number of error types.

#### class `UE::Mutable::Private::FExternalResourceProvider`  
`class FExternalResourceProvider`  
_L94-110_
- desc: Interface to request external images used as parameters.
- L98 _public prototype_ `virtual ~FExternalResourceProvider() = default;` — Ensure virtual destruction
- L101 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetImageAsync(UTexture* Texture, uint8 MipmapsToSkip, bool bLoadMipTail, TFunction<void(UE::Mutable::Private::TManagedPtr<FImage>)>& ResultCallback) = 0;` — Returns the completion event and a cleanup function that must be called once event is completed.
- L102 _public function_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetReferencedImageAsync(int32 Id, uint8 MipmapsToSkip, TFunction<void(UE::Mutable::Private::TManagedPtr<FImage>)>& ResultCallback)`
- L104 _public prototype_ `virtual FExtendedImageDesc GetImageDesc(UTexture* Texture) = 0;`
- L107 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetMeshAsync(USkeletalMesh* SkeleltalMesh, int32 BaseLODIndex, int32 BaseSectionIndex, int32 LODBias, uint8 InConversionFlags, TFunction<void(UE::Mutable::Private::TManagedPtr<FMesh>)>& ResultCallback) = 0;` — Returns the completion event and a cleanup function that must be called once event is completed.
- L108 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetSkeletalMeshAsync( USkeletalMesh* SkeleltalMesh, int32 InLODBegin, int32 InLODEnd, int32 InGeometryLODBegin, int32 InGeometryLODEnd, uint8 InConversionFlags, TFunction<void(UE::Mutable::Private::TManagedPtr<FSkeletalMesh>)>& ResultCallback) = 0;`

#### class `UE::Mutable::Private::FLiveInstanceLogger`  
`class FLiveInstanceLogger`  
_L136-171_
- desc: Class to log update messages
- L141 _public prototype_ `void SetLogger(TSharedPtr<IMutableEditorLogger> InInstanceLogger);` — Set the logger class to print the messages to an editor widget
- L146 _public prototype_ `void LogUpdateMessage(const FString& Message, ELogVerbosity::Type Verbosity = ELogVerbosity::Error);` — Prints the message into the Logs console/file and also prints it into an editor widget. Use this function instead of UE_LOG to print important messages.
- L150 _public function_ `template<typename... Types> UE_REWRITE void LogInfo(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)` — TODO: Use UTF8CHAR or ANSICHAR to save program space.
- L156 _public function_ `template<typename... Types> UE_REWRITE void LogWarn(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)`
- L162 _public function_ `template<typename... Types> UE_REWRITE void LogError(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)`
- L170 _private member_ `TSharedPtr<IMutableEditorLogger> InstanceLogger;` — Pointer to the editor log list to print all the messages related to the instance update.

#### struct `UE::Mutable::Private::FLiveInstance`  
`struct FLiveInstance`  
_L176-198_
- desc: Data for an instance that is currently being processed in the mutable system. This means it is between a BeginUpdate and EndUpdate, or during an "atomic" operation (like generate a single resource).
- L178 _public member_ `int32 State = 0;`
- L179 _public member_ `uint32 LODMask = 0;`
- L180 _public member_ `TManagedPtr<const FInstance> Instance;`
- L181 _public member_ `TSharedPtr<FModel> Model;`
- L183 _public member_ `TSharedPtr<const FParameters> Parameters;`
- L186 _public member_ `TSharedRef<FProgramCache> Cache = MakeShared<FProgramCache>();` — Cached data for the generation of this instance.
- L188 _public member_ `TSharedPtr<FImageIdRegistry> ImageIdRegistry;`
- L189 _public member_ `TSharedPtr<FMaterialIdRegistry> MaterialIdRegistry;`
- L190 _public member_ `TSharedPtr<FSkeletalMeshIdRegistry> SkeletalMeshIdRegistry;`
- L192 _public member_ `TSharedPtr<FExternalResourceProvider> ExternalResourceProvider;`
- L193 _public member_ `TSharedPtr<FPassthroughObjectLoader> PassthroughObjectLoader;`
- L195 _public member_ `TSharedPtr<FLiveInstanceLogger> UpdateLogger;`
- L197 _public member_ `FImageOperator::FImagePixelFormatFunc PixelFormatOverride;`

#### struct `UE::Mutable::Private::FWorkingMemoryManager`  
`struct FWorkingMemoryManager`  
_L202-267_
- desc: Struct to manage all the memory allocated for resources used during mutable operation.
- L204 _public typedef_ `using MemoryCounter = MemoryCounters::FInternalMemoryCounter;`
- L207 _public typedef_ `template<class Type> using TMemoryTrackedArray = TArray<Type, FDefaultMemoryTrackingAllocator<MemoryCounter>>;`
- L210 _public typedef_ `template<class KeyType, class ValueType> using TMemoryTrackedMap = TMap<KeyType, ValueType, FDefaultMemoryTrackingSetAllocator<MemoryCounter>>;`
- L213 _public member_ `int64 BudgetBytes = 0;` — Maximum working memory that mutable should be using.
- L216 _public member_ `int64 BudgetExcessBytes = 0;` — Maximum excess memory reached during the current operation.
- L219 _public member_ `mutable FMutex LiveInstancesMutex;` — Data for each mutable instance that is being updated.
- L220 _public member_ `TMemoryTrackedArray<TWeakPtr<FLiveInstance>> LiveInstances;`
- L225 _public prototype_ `bool EnsureBudgetBelow(int64 AdditionalMemory, const TSharedPtr<FLiveInstance>& InCurrentLiveInstance);` — Make sure the working memory is below the internal budget, even counting with the passed additional memory. Return true if it succeeded, false otherwise.
- L228 _public prototype_ `bool IsMemoryBudgetFull() const;` — Return true if the memory budget is 90% full.
- L231 _public prototype_ `int64 GetCurrentMemoryBytes() const;` — Calculate the current usage of memory as used to calculate the budget.
- L233 _public prototype_ `int32 GetRomBytes() const;`
- L236 _public function_ `int32 GetCacheBytes() const` — Calculate the amount of bytes in data cached in the level 0 and 1 cache in all live instances.
- L266 _public prototype_ `void LogWorkingMemory(const class CodeRunner* CurrentRunner) const;`

#### struct `UE::Mutable::Private::FGetImageResult`  
`struct FGetImageResult`  
_L270-275_
- L272 _public member_ `TManagedPtr<const FImage> MutableImage;`
- L274 _public member_ `bool bWasOperationSuccessful = true;`

#### struct `UE::Mutable::Private::FGetMaterialResult`  
`struct FGetMaterialResult`  
_L277-282_
- L279 _public member_ `TManagedPtr<const FMaterial> MutableMaterial;`
- L281 _public member_ `bool bWasOperationSuccessful = true;`

#### struct `UE::Mutable::Private::FGetSkeletalMeshResult`  
`struct FGetSkeletalMeshResult`  
_L284-289_
- L286 _public member_ `TManagedPtr<const FSkeletalMesh> MutableSkeletalMesh;`
- L288 _public member_ `bool bWasOperationSuccessful = true;`

#### class `UE::Mutable::Private::FSystem`  
`class FSystem`  
_L293-434_
- desc: Main system class to load models and build instances.
- L297 _public member_ `static constexpr uint32 AllLODs = 0xffffffff;` — This constant can be used in place of the lodMask in methods like BeginUpdate
- L302 _public prototype_ `FSystem( const FSettings& Settings = FSettings());` — Constructor of a system object to build data. \param Settings Optional class with the settings to use in this system. The default value configures a production-ready system.
- L305 _public prototype_ `void SetStreamingInterface(const TSharedPtr<FModelReader>& );` — Set a new provider for model data.
- L310 _public prototype_ `void SetWorkingMemoryBytes( uint64 Bytes );` — Set the working memory limit, overrding any set in the settings when the system was created. Refer to Settings::SetWorkingMemoryBudget for more information.
- L316 _public prototype_ `TSharedRef<FLiveInstance> NewInstance(const TSharedPtr<FModel>& Model, const TSharedPtr<UE::Mutable::Private::FImageIdRegistry>& InImageIdRegistry, const TSharedPtr<UE::Mutable::Private::FMaterialIdRegistry>& InMaterialIdRegistry, const TSharedPtr<UE::Mutable::Private::FSkeletalMeshIdRegistry>& InSkeletalMeshIdRegistry, const TSharedPtr<FExternalResourceProvider>& ExternalResourceProvider, const TSharedPtr<FPassthroughObjectLoader>& PassthroughObjectLoader, const FImageOperator::FImagePixelFormatFunc& PixelFormatOverride, const TSharedPtr<FLiveInstanceLogger>& LiveInstanceLogger);` — Create a new instance from the given model. The instance can then be configured through calls to BeginUpdate/EndUpdate. A call to NewInstance must be paired to a call to ReleasesInstance when the instance is no longer needed.
- L330 _public prototype_ `TSharedRef<FLiveInstance> NewBuildInstance(const TSharedPtr<FModel>& InModel, const TSharedPtr<const FParameters>& InParameters, const TSharedPtr<FExternalResourceProvider>& ExternalResourceProvider);` — Create a ready to use new FLiveInstance to be used during the mutable build operations. It will not be taken into consideration for any update operation as the life cycle of the returned object is expected to be short and contained during the compilation operation. It does not require further initialization as it is fully capable of operating as is.
- L348 _public prototype_ `void BeginUpdate_GameThread(const TSharedRef<FLiveInstance>& LiveInstance, uint32 LodMask);` — \brief Update an instance with a new parameter set and/or state. \warning a call to BeginUpdate must be paired with a call to EndUpdate once the returned data has been processed. \param LiveInstance The instance to update, as created by a NewInstance call. \param InParams The parameters that customize this instance. \param StateIndex The index of the state this instance will be set to. The states range from 0 to Model::GetStateCount-1 \param LodMask Bitmask selecting the levels of detail to build (i-th bit selects i-th lod). \return the instance data with all the LOD, components, and ids to generate the meshes and images. The returned Instance is only valid until the next call to EndUpdate with the same instanceID parameter. Very fast. Can be called in the Game Thread.
- L351 _public prototype_ `TManagedPtr<const FInstance> BeginUpdate_MutableThread(const TSharedRef<FLiveInstance>& LiveInstance, bool bClearCacheLayer1);` — Potentially expensive. Must be called in the Mutable Thread.
- L355 _public prototype_ `UE::Tasks::TTask<FExtendedImageDesc> GetImageDesc(UE::Tasks::FTask Prerequisite, const TSharedRef<FLiveInstance>& LiveInstance, const FImageId& ImageId);` — Only valid between BeginUpdate and EndUpdate Calculate the description of an image, without generating it.
- L361 _public prototype_ `UE::Tasks::TTask<FGetImageResult> GetImage(UE::Tasks::FTask Prerequisite, const TSharedRef<FLiveInstance>& LiveInstance, const FImageId& ImageId, int32 MipsToSkip = 0);` — Only valid between BeginUpdate and EndUpdate \param MipsToSkip Number of mips to skip compared from the full image. If 0, all mip levels will be generated. If more levels than possible to discard are specified, the image will still contain a minimum number of mips specified at model compile time.
- L363 _public prototype_ `UE::Tasks::TTask<FGetSkeletalMeshResult> GetSkeletalMesh(UE::Tasks::FTask Prerequisite, const TSharedRef<FLiveInstance>& LiveInstance, const FSkeletalMeshId& SkeletalMeshId, uint16 ExecutionOptions);`
- L367 _public prototype_ `FExtendedImageDesc GetImageDescInline(const TSharedRef<FLiveInstance>& LiveInstance, const FImageId& ImageId);` — Only valid between BeginUpdate and EndUpdate Calculate the description of an image, without generating it.
- L373 _public prototype_ `TManagedPtr<const FImage> GetImageInline(const TSharedRef<FLiveInstance>& LiveInstance, const FImageId& ImageId, int32 MipsToSkip = 0);` — Only valid between BeginUpdate and EndUpdate \param MipsToSkip Number of mips to skip compared from the full image. If 0, all mip levels will be generated. If more levels than possible to discard are specified, the image will still contain a minimum number of mips specified at model compile time.
- L375 _public prototype_ `UE::Tasks::TTask<FGetMaterialResult> GetMaterial(UE::Tasks::FTask Prerequisite, const TSharedRef<FLiveInstance>& LiveInstance, const FMaterialId& MaterialId);`
- L381 _public prototype_ `void EndUpdate(const TSharedRef<FLiveInstance>& LiveInstance, bool bClearRoms, bool bFreeCache);` — Invalidate and free the last Instance data returned by a call to BeginUpdate with the same instance index. After a call to this method, that Instance cannot be used any more and its content is undefined. \param instance The index of the instance whose last data will be invalidated.
- L386 _public prototype_ `void GetParameterRelevancy(const TSharedRef<FLiveInstance>& LiveInstance, TArray<uint32>& OutRelevantParameters);` — Calculate the relevancy of every parameter. Some parameters may be unused depending on the values of other parameters. This is useful to hide irrelevant parameters in dynamic user interfaces.
- L388 _public prototype_ `static FImageId GetImageId(const TSharedPtr<FImageIdRegistry>& Registry, const FModel& Model, const FParameters& Params, FOperation::ADDRESS RootAt);`
- L390 _public prototype_ `static FMaterialId GetMaterialId(const TSharedPtr<FMaterialIdRegistry>& Registry, const FModel& Model, const FParameters& Params, FOperation::ADDRESS RootAt);`
- L392 _public prototype_ `static FSkeletalMeshId GetSkeletalMeshId(const TSharedPtr<FSkeletalMeshIdRegistry>& Registry, const FModel& Model, const FParameters& Params, FOperation::ADDRESS RootAt);`
- L395 _public prototype_ `FSystem( const FSystem& ) = delete;` — Prevent copy, move and assignment.
- L396 _public prototype_ `FSystem& operator=( const FSystem& ) = delete;`
- L397 _public prototype_ `FSystem( FSystem&& ) = delete;`
- L398 _public prototype_ `FSystem& operator=( FSystem&& ) = delete;`
- L400 _public prototype_ `bool BuildBool(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L401 _public prototype_ `int32 BuildInt(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L402 _public prototype_ `float BuildScalar(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L403 _public prototype_ `FVector4f BuildColor(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L404 _public prototype_ `TManagedPtr<const String> BuildString(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L405 _public prototype_ `TManagedPtr<const FImage> BuildImage(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress, int32 MipsToSkip);`
- L406 _public prototype_ `TManagedPtr<const FMesh> BuildMesh(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InRootAddress, EMeshContentFlags MeshContentFilter);`
- L407 _public prototype_ `TManagedPtr<const FInstance> BuildInstance(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress);`
- L408 _public prototype_ `TManagedPtr<const FLayout> BuildLayout(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L409 _public prototype_ `FProjector BuildProjector(const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS InAddress) ;`
- L412 _public member_ `FSettings Settings;`
- L415 _public member_ `TSharedPtr<FModelReader> StreamInterface;` — Data streaming interface, if any.
- L417 _public member_ `FWorkingMemoryManager WorkingMemoryManager;`
- L420 _public member_ `static std::atomic<uint32> RomTick;` — Increased each time a rom is loaded. Used to keep track of which roms to evict.
- L422 _public prototype_ `static bool CheckForUpdatedParameters(const TSharedRef<FLiveInstance>& LiveInstance, const TSharedPtr<const FParameters>& InOldParameters);`
- L427 _public prototype_ `bool RunCodeInline( const TSharedRef<FLiveInstance>& InLiveInstance, FOperation::ADDRESS, uint16 ExecutionOptions = 0);` — Runs the mutable code @return true if the execution was successful and false otherwise
- L433 _public prototype_ `void UpdateStats();` — Update some mutable core unreal stats.

#### Free symbols / members of external scopes

- L38 _macro_ `#define UE_API MUTABLERUNTIME_API`
- L44 _macro_ `#define UE_MUTABLE_ENABLE_SLOW_TRACES 0` — If set to 1, this enables some expensive Unreal Insights traces, but can lead to 5x slower mutable operation. Other cheaper traces are enabled at all times.
- L63 _prototype_ `MUTABLE_DEFINE_ENUM_SERIALISABLE(ETextureCompressionStrategy);`
- L66 _namespace_ `namespace UE`
- L66 _namespace_ `namespace Mutable` (scope `UE`)
- L66 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L114 _function_ `inline void UpdateLLMStats()` (scope `UE::Mutable::Private`) — Call the tick of the LLM system (we do this to simulate a frame since the LLM system is not entirelly designed to run over a program)
- L127 _variable_ `constexpr uint64 AllParametersMask = TNumericLimits<uint64>::Max();` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/SystemTypes.h` (Internal)


#### struct `UE::Mutable::Private::FScheduledOp`  
`struct FScheduledOp`  
_L14-84_
- desc: This structure stores the data about an ongoing mutable operation that needs to be executed.
- L16 _public member_ `static constexpr int32 NumStageBits = 6;`
- L17 _public member_ `static constexpr int32 MaxNumStages = (1 << NumStageBits) - 1;`
- L19 _public prototype_ `inline FScheduledOp() = default;`
- L21 _public function_ `inline FScheduledOp(FOperation::ADDRESS InAt, const FScheduledOp& InOpTemplate, uint8 InStage = 0, uint32 InCustomState = 0) : At(InAt) , CustomState(InCustomState) , ExecutionIndex(InOpTemplate.ExecutionIndex) , ExecutionOptions(InOpTemplate.ExecutionOptions) , Type(InOpTemplate.Type) , Stage(InStage)`
- L32 _public function_ `static inline FScheduledOp FromOpAndOptions(FOperation::ADDRESS InAt, const FScheduledOp& InOpTemplate, uint16 InExecutionOptions)`
- L47 _public member_ `FOperation::ADDRESS At = 0;` — Address of the operation
- L51 _public member_ `uint32 CustomState = 0;` — Additional custom state data that the operation can store. This is usually used to pass information between execution stages of an operation.
- L57 _public member_ `uint16 ExecutionIndex = 0;` — Index of the operation execution: This is used for iteration of different ranges. It is an index into the CodeRunner::GetMemory()::m_rangeIndex vector. executionIndex 0 is always used for empty ExecutionIndex, which is the most common one.
- L61 _public member_ `uint16 ExecutionOptions : 14 = 0;` — Additional execution options. Set externally to this op, it usually alters the result. For example, this is used to keep track of the mipmaps to skip in image operations.
- L72 _public member_ `uint16 Type : 2 = static_cast<uint16>(EType::Full);`
- L77 _public member_ `uint8 Stage : NumStageBits = 0;` — Internal stage of the operation. Stage 0 is usually scheduling of children, and 1 is execution. Some instructions may have more steges to schedule children that are optional for execution, etc.
- L80 _public member_ `static constexpr uint64 CallstackMaxDepth = 16;`
- L81 _public member_ `uint64 StackDepth = 0;`
- L82 _public member_ `uint64 ScheduleCallstack[CallstackMaxDepth];`

#### enum `UE::Mutable::Private::FScheduledOp::EType`  
`enum class EType : uint8`  
_L64-71_
- desc: Type of calculation we are requesting for this operation.
- L67 _public enumerator_ `Full` — Execute the operation to calculate the full result
- L70 _public enumerator_ `ImageDesc` — Execute the operation to obtain the descriptor of an image or mesh.

#### Free symbols / members of external scopes

- L8 _macro_ `#define MUTABLE_DEBUG_CODERUNNER_TASK_SCHEDULE_CALLSTACK 0`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L86 _function_ `inline uint32 GetTypeHash(const FScheduledOp& Op)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/TVariant.h` (Internal)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _function_ `template<typename ...T> bool operator==(const TVariant<T...>& ValueA, const TVariant<T...>& ValueB)` (scope `UE::Mutable::Private`) — TVariant currently does not support this operator. Once supported remove it.
- L24 _function_ `` (scope `UE::Mutable::Private::operator ==`)
- L25 _typedef_ `using Type = typename TDecay<decltype(StoredValueA)>::Type;` (scope `UE::Mutable::Private::operator ==::__anona4545aeb0102`)

### `Plugins/Mutable/Source/MutableRuntime/Internal/MuR/Types.h` (Internal)


#### enum `EFaceCullStrategy`  
`enum class EFaceCullStrategy : uint8`  
_L20-24_
- reflection: `UENUM()`
- desc: This type is used in some mesh clip operations. Warning: this type is used compiled COs. Any relevant change to the option order requires and update in the CustomizableObjectPrivate::ECustomizableObjectVersions
- L22 _public enumerator_ `AllVerticesCulled = 0 UMETA(DisplayName = "Remove face if all vertices removed")`
- L23 _public enumerator_ `OneVertexCulled = 1 UMETA(DisplayName = "Remove face if one vertex removed")`

#### enum `EClipVertexSelectionType`  
`enum class EClipVertexSelectionType : uint8`  
_L30-35_
- desc: This type is used in some mesh clip operations. Warning: this type is used compiled COs. Any relevant change to the option order requires and update in the CustomizableObjectPrivate::ECustomizableObjectVersions
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `Shape = 1`
- L34 _public enumerator_ `BoneHierarchy = 2`

#### enum `UE::Mutable::Private::EMemoryInitPolicy`  
`enum class EMemoryInitPolicy`  
_L44-48_
- L46 _public enumerator_ `Uninitialized`
- L47 _public enumerator_ `Zeroed`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Mutable` (scope `UE`)
- L38 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L51 _function_ `inline uint32 GetTypeHash(const FInstancedStruct& InstancedStruct)` (scope `UE::Mutable::Private`)
- L65 _function_ `inline uint32 GetTypeHash(const float& Key)` (scope `UE::Mutable::Private`)
- L71 _function_ `inline uint32 GetTypeHash(const FRichCurveKey& Key)` (scope `UE::Mutable::Private`)
- L90 _function_ `template<typename T> uint32 GetTypeHash(const TArray<T>& Key)` (scope `UE::Mutable::Private`)
- L104 _function_ `template<typename K, typename V> bool operator==(const TMap<K,V>& A, const TMap<K,V>& B )` (scope `UE::Mutable::Private`)
- L110 _function_ `inline uint32 GetTypeHash(const FRichCurve& Curve)` (scope `UE::Mutable::Private`)
- L116 _function_ `inline uint32 GetTypeHash(const FPerPlatformInt& Key)` (scope `UE::Mutable::Private`)
- L127 _function_ `inline uint32 GetTypeHash(const FPerQualityLevelInt& Key)` (scope `UE::Mutable::Private`)
- L138 _function_ `inline bool operator==(const FPerPlatformInt& A, const FPerPlatformInt& B)` (scope `UE::Mutable::Private`)
- L149 _function_ `inline bool operator==(const FPerQualityLevelInt& A, const FPerQualityLevelInt& B)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/BitWriterResourceKey.h` (Private)


#### class `FBitWriterResourceKey`  
`class FBitWriterResourceKey : public FBitWriter`  
_L8-14_
- inherits: `FBitWriter`
- L11 _public prototype_ `FBitWriterResourceKey(int64 InMaxBits, bool AllowResize = false);`
- L13 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Value) override;`

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/BlockCompression/BlockCompression.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define MIRO_INCLUDE_BC 0`
- L16 _macro_ `#define MIRO_INCLUDE_ASTC 0`
- L23 _macro_ `#define MIRO_EXCLUDE_QUALITY_ABOVE MUTABLE_EXCLUDE_IMAGE_COMPRESSION_QUALITY`

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/CodeRunner.h` (Private)


#### class `UE::Mutable::Private::CodeRunner`  
`class CodeRunner : public TSharedFromThis<CodeRunner>`  
_L28-661_
- inherits: `TSharedFromThis<CodeRunner>`
- desc: Code execution of the mutable virtual machine.
- L34 _public prototype_ `static TSharedRef<CodeRunner> Create( const TSharedRef<FLiveInstance>& InLiveInstance, const FSettings& InSettings, FSystem& InSystem, EExecutionStrategy, FOperation::ADDRESS At, uint16 ExecutionOptions, FScheduledOp::EType Type);`
- L45 _public prototype_ `explicit CodeRunner( const TSharedRef<FLiveInstance>& InLiveInstance, FPrivateToken, const FSettings& InSettings, FSystem& InSystem, EExecutionStrategy, FOperation::ADDRESS At, uint16 ExecutionOptions, FScheduledOp::EType Type);` — Private constructor to prevent stack allocation. In general we can not call AsShared() if the lifetime is bounded.
- L120 _protected prototype_ `TSharedPtr<FRangeIndex> BuildCurrentOpRangeIndex( const FScheduledOp&, int32 ParameterIndex);`
- L122 _protected prototype_ `void RunCode( const FScheduledOp&);`
- L124 _protected prototype_ `void RunCode_Conditional(const FScheduledOp&);`
- L125 _protected prototype_ `void RunCode_Switch(const FScheduledOp&);`
- L126 _protected prototype_ `void RunCode_Instance(const FScheduledOp&);`
- L127 _protected prototype_ `void RunCode_InstanceAddResource(const FScheduledOp&);`
- L130 _protected prototype_ `bool RunCode_ConstantResource(const FScheduledOp&);` — Return false in case of failure.
- L132 _protected prototype_ `void RunCode_Mesh(const FScheduledOp&);`
- L133 _protected prototype_ `void RunCode_Image(const FScheduledOp&);`
- L134 _protected prototype_ `void RunCode_Layout(const FScheduledOp&);`
- L135 _protected prototype_ `void RunCode_Bool(const FScheduledOp&);`
- L136 _protected prototype_ `void RunCode_Int(const FScheduledOp&);`
- L137 _protected prototype_ `void RunCode_Scalar(const FScheduledOp&);`
- L138 _protected prototype_ `void RunCode_String(const FScheduledOp&);`
- L139 _protected prototype_ `void RunCode_Color(const FScheduledOp&);`
- L140 _protected prototype_ `void RunCode_Projector(const FScheduledOp&);`
- L141 _protected prototype_ `void RunCode_Matrix(const FScheduledOp&);`
- L142 _protected prototype_ `void RunCode_Material(const FScheduledOp&);`
- L144 _protected prototype_ `void RunCodeImageDesc(const FScheduledOp&);`
- L146 _protected prototype_ `void LaunchWaitForOthersTask(Tasks::FTaskEvent Event, uint64 ReentryCounter = 0);`
- L160 _public prototype_ `TTuple<UE::Tasks::FTask, TFunction<void()>> LoadExternalImageAsync(FExternalResourceId Id, uint8 MipmapsToSkip, TFunction<void(TManagedPtr<FImage>)>& ResultCallback);` — Load an external image asynchronously, returns an event to wait for complition and a cleanup function that must be called once the event has completed.
- L161 _public prototype_ `UE::Mutable::Private::FExtendedImageDesc GetExternalImageDesc(UTexture* Id);`
- L164 _public prototype_ `TTuple<UE::Tasks::FTask, TFunction<void()>> LoadExternalMeshAsync(FExternalResourceId Id, int32 BaseLODIndex, int32 BaseSectionIndex, int32 LODBias, uint8 ConversionFlags, TFunction<void(TManagedPtr<FMesh>)>& ResultCallback);` — Load an external mesh asynchronously, returns an event to wait for complition and a cleanup function that must be called once the event has completed.
- L167 _public prototype_ `TTuple<UE::Tasks::FTask, TFunction<void()>> LoadExternalSkeletalMeshAsync(FExternalResourceId Id, int32 LODBegin, int32 LODEnd, int32 GeometryLODBegin, int32 GeometryLODEnd, uint8 ConversionFlags, TFunction<void(TManagedPtr<FSkeletalMesh>)>& ResultCallback);` — Load an external skeletal mesh asynchronously, returns an event to wait for complition and a cleanup function that must be called once the event has completed.
- L170 _public member_ `FSettings Settings;` — Settings that may affect the execution of some operations, like image conversion quality.
- L173 _public member_ `const TSharedRef<FLiveInstance> LiveInstance;` — Instance whose data is being used by this runner.
- L180 _public member_ `TArray<FScheduledOpData> HeapData;` — Heap of intermediate data pushed by some instructions and referred by others. It is not released until no operations are pending.
- L184 _protected member_ `TMap<FOperation::ADDRESS, FExtendedImageDesc> ImageDescResults;` — Image descriptor intermediate results.
- L185 _protected member_ `TArray<int32> ImageDescConstantImages;`
- L187 _protected prototype_ `void Run(TUniquePtr<FProfileContext>&& ProfileContext, bool bForceInlineExecution);`
- L190 _public prototype_ `void StartRun(bool bForceInlineExecution);`
- L193 _public prototype_ `FExtendedImageDesc GetImageDescResult(FOperation::ADDRESS ResultAddres);`
- L195 _public prototype_ `FProgramCache& GetMemory();`
- L197 _public prototype_ `FLiveInstanceLogger& GetLogger();`
- L298 _public function_ `void AddOp(const FScheduledOp& Op, DepsTypes&&... InDeps)`
- L316 _public function_ `void AddOp(const FScheduledOp& Op, TArrayView<const FScheduledOp> InDeps)`
- L330 _public function_ `int32 GetInternalMemoryBytes() const` — Calculate an approximation of memory used by manging structures in this class.
- L339 _public prototype_ `FString PrintDependencyGraph();`
- L343 _protected member_ `EExecutionStrategy ExecutionStrategy = EExecutionStrategy::None;` — Strategy to choose the order of execution of operations.
- L346 _protected member_ `bool bForceSerialTaskExecution = false;` — If this flag is enabled, issued operation stage that use tasks will be executed in the mutable thread instead of in a generic worker thread.
- L349 _protected member_ `TArray<FTask> ClosedTasks;` — List of pending operations that we don't know if they cannot be run yet because of dependencies.
- L352 _protected member_ `TArray<FScheduledOp> OpenTasks;` — List of tasks that can be run because they don't have any unmet dependency.
- L355 _protected member_ `TArray<TSharedPtr<FIssuedTask>> IssuedTasksOnHold;` — List of tasks that are ready to run concurrently.
- L358 _protected member_ `TArray<TSharedPtr<FIssuedTask>> IssuedTasks;` — List of tasks that have been set to run concurrently and their completion is unknown.
- L362 _public function_ `inline FExtendedImageDesc LoadImageDesc(const FCacheAddress& From)`
- L367 _public function_ `inline bool LoadBool(const FCacheAddress& From) const`
- L372 _public function_ `inline float LoadInt(const FCacheAddress& From) const`
- L377 _public function_ `inline float LoadScalar(const FCacheAddress& From) const`
- L382 _public function_ `inline FVector4f LoadColor(const FCacheAddress& From) const`
- L387 _public function_ `inline FMatrix44f LoadMatrix(const FCacheAddress& From) const`
- L392 _public function_ `inline TManagedPtr<const FMaterial> LoadMaterial(const FCacheAddress& From) const`
- L397 _public function_ `inline TManagedPtr<const String> LoadString(const FCacheAddress& From) const`
- L402 _public function_ `inline FProjector LoadProjector(const FCacheAddress& From) const`
- L407 _public function_ `inline TManagedPtr<const FMesh> LoadMesh(const FCacheAddress& From) const`
- L412 _public function_ `inline TManagedPtr<const FLOD> LoadLOD(const FCacheAddress& From) const`
- L417 _public function_ `inline TManagedPtr<const FSkeletalMesh> LoadSkeletalMesh(const FCacheAddress& From) const`
- L422 _public function_ `inline TManagedPtr<const FImage> LoadImage(const FCacheAddress& From) const`
- L427 _public function_ `inline TManagedPtr<const FLayout> LoadLayout(const FCacheAddress& From) const`
- L432 _public function_ `inline TManagedPtr<const FInstance> LoadInstance(const FCacheAddress& From) const`
- L437 _public function_ `inline TManagedPtr<const FExtensionData> LoadExtensionData(const FCacheAddress& From) const`
- L442 _public function_ `inline TManagedPtr<const FInstancedStruct> LoadInstancedStruct(const FCacheAddress& From) const`
- L447 _public function_ `inline void StoreImageDesc(const FCacheAddress& To, const FExtendedImageDesc& ImageDesc)`
- L452 _public function_ `inline void StoreBool(const FCacheAddress& To, bool Value)`
- L457 _public function_ `inline void StoreInt(const FCacheAddress& To, int32 Value)`
- L462 _public function_ `inline void StoreScalar(const FCacheAddress& To, float Value)`
- L467 _public function_ `inline void StoreString(const FCacheAddress& To, TManagedPtr<const String> Value)`
- L472 _public function_ `inline void StoreColor(const FCacheAddress& To, const FVector4f& Value)`
- L477 _public function_ `inline void StoreMatrix(const FCacheAddress& To, const FMatrix44f& Value)`
- L482 _public function_ `inline void StoreMaterial(const FCacheAddress& To, TManagedPtr<const FMaterial> Value)`
- L487 _public function_ `inline void StoreProjector(const FCacheAddress& To, const FProjector& Value)`
- L492 _public function_ `inline void StoreMesh(const FCacheAddress& To, const TManagedPtr<const FMesh>& Resource)`
- L497 _public function_ `inline void StoreLOD(const FCacheAddress& To, TManagedPtr<const FLOD> Resource)`
- L502 _public function_ `inline void StoreSkeletalMesh(const FCacheAddress& To, TManagedPtr<const FSkeletalMesh> Resource)`
- L507 _public function_ `inline void StoreImage(const FCacheAddress& To, const TManagedPtr<const FImage>& Resource)`
- L512 _public function_ `inline void StoreLayout(const FCacheAddress& To, const TManagedPtr<const FLayout>& Resource)`
- L517 _public function_ `inline void StoreInstance(const FCacheAddress& To, const TManagedPtr<const FInstance>& Resource)`
- L522 _public function_ `inline void StoreExtensionData(const FCacheAddress& To, const TManagedPtr<const FExtensionData>& Resource)`
- L527 _public function_ `inline void StoreInstancedStruct(const FCacheAddress& To, const TManagedPtr<const FInstancedStruct>& Resource)`
- L532 _public function_ `inline TManagedPtr<FImage> CreateImage(uint32 SizeX, uint32 SizeY, uint32 Lods, EImageFormat Format, EInitializationType Init)`
- L538 _public function_ `TManagedPtr<FImage> CreateImageLike( const FImage* Ref, EInitializationType Init)`
- L544 _public function_ `inline TManagedPtr<FImage> CloneOrTakeOver(TManagedPtr<const FImage>&& Resource)`
- L565 _public function_ `[[nodiscard]] inline TManagedPtr<FMesh> CreateMesh(int32 BudgetReserveSize = 0)`
- L573 _public function_ `[[nodiscard]] inline TManagedPtr<FMesh> CloneOrTakeOver(TManagedPtr<const FMesh>&& Resource)`
- L595 _public function_ `template<typename T> TPassthroughObjectPtr<T> FindPassthrough(PASSTHROUGH_ID Id)`
- L610 _public member_ `bool bUnrecoverableError = false;` — This flag is turned on when a streaming error or similar happens. Results are not usable. This should only happen in-editor.
- L612 _public member_ `FSystem& System;`
- L615 _public member_ `FModel& Model;` — Dereference optimization. LiveInstance keeps them alive.
- L616 _public member_ `const FProgram& Program;`
- L617 _public member_ `const FParameters& Parameters;`
- L619 _public member_ `TSharedPtr<FExternalResourceProvider> ExternalResourceProvider;`
- L623 _private function_ `inline TManagedPtr<FImage> CreateImageImp(uint32 SizeX, uint32 SizeY, uint32 Lods, EImageFormat Format, EInitializationType Init)`
- L634 _private function_ `bool EnsureBudgetBelow( uint64 AdditionalMemory ) const`
- L639 _private prototype_ `void AddChildren(TArrayView<const FScheduledOp> Deps);`
- L643 _private prototype_ `TSharedPtr<FIssuedTask> IssueOp(FScheduledOp item);` — Try to create a concurrent task for the given op. Return null if not possible.
- L646 _private prototype_ `void UpdateTraces();` — Update debug stats.
- L649 _private prototype_ `bool ShouldIssueTask() const;`
- L652 _private prototype_ `void LaunchIssuedTask(const TSharedPtr<FIssuedTask>& TaskToIssue, bool& bOutFailed);`
- L656 _private member_ `FOperation::ADDRESS RootOPAddress = 0;`
- L658 _private member_ `uint8 RootOpExecutionOptions;`
- L660 _private member_ `FScheduledOp::EType RootOpType;`

#### struct `UE::Mutable::Private::CodeRunner::FPrivateToken`  
`struct FPrivateToken`  
_L31-31_
- desc: The private token allows only members or friends to call MakeShared.
- L31 _public prototype_ `struct FPrivateToken` — The private token allows only members or friends to call MakeShared.

#### struct `UE::Mutable::Private::CodeRunner::FProfileContext`  
`struct FProfileContext`  
_L56-61_
- L58 _public member_ `FMutex Mutex;`
- L59 _public member_ `uint32 NumRunOps = 0;`
- L60 _public member_ `uint32 RunOpsPerType[int32(EOpType::COUNT)] = {};`

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData`  
`struct FScheduledOpData`  
_L65-115_
- desc: Type of data sometimes stored in the code runner heap to pass info between operation stages.
- L114 _public member_ `TManagedPtr<const FResource> Resource;`

#### union `UE::Mutable::Private::CodeRunner::FScheduledOpData::(anonymous)`  
``  
_L68-112_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L70-73_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L76-80_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L83-86_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L89-95_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L98-105_

#### struct `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::(anonymous)`  
``  
_L108-110_

#### struct `UE::Mutable::Private::CodeRunner::FExternalResourceId`  
`struct FExternalResourceId`  
_L149-157_
- L152 _public member_ `PASSTHROUGH_ID ReferenceResourceId = PASSTHROUGH_ID_INVALID;` — If it is an image or mesh reference.
- L155 _public member_ `UTexture* ImageParameter = nullptr;` — If it is an image or mesh parameter.
- L156 _public member_ `USkeletalMesh* MeshParameter = nullptr;`

#### struct `UE::Mutable::Private::CodeRunner::FTask`  
`struct FTask`  
_L199-218_
- L201 _public function_ `FTask()`
- L202 _public function_ `FTask(const FScheduledOp& InOp, TConstArrayView<FScheduledOp> InDeps) : Op(InOp)`
- L216 _public member_ `FScheduledOp Op;`
- L217 _public member_ `TArray<FCacheAddress, TInlineAllocator<3>> Deps;`

#### class `UE::Mutable::Private::CodeRunner::FIssuedTask`  
`class FIssuedTask`  
_L220-242_
- L223 _public member_ `const FScheduledOp Op;`
- L225 _public member_ `UE::Tasks::FTask Event = {};`
- L227 _public function_ `FIssuedTask(const FScheduledOp& InOp) : Op(InOp)`
- L228 _public prototype_ `virtual ~FIssuedTask() = default;`
- L231 _public function_ `virtual bool Prepare(CodeRunner*, bool& bOutFailed)`
- L232 _public function_ `virtual void DoWork()`
- L235 _public prototype_ `virtual bool Complete(CodeRunner*) = 0;` — Return true if succeeded.
- L238 _public function_ `virtual bool IsComplete(CodeRunner*)` — Return true if the task has been completed.

#### class `UE::Mutable::Private::CodeRunner::FLoadMeshRomTask`  
`class FLoadMeshRomTask : public CodeRunner::FIssuedTask`  
_L245-271_
- inherits: `CodeRunner::FIssuedTask`
- L248 _public function_ `FLoadMeshRomTask( const FScheduledOp& InOp, int32 InFirstIndex, EMeshContentFlags InRomContentFlags, EMeshContentFlags InExecutionContentFlags) : FIssuedTask(InOp) , FirstIndex(InFirstIndex) , RomContentFlags(InRomContentFlags) , ExecutionContentFlags(InExecutionContentFlags)`
- L261 _public prototype_ `virtual bool Prepare(CodeRunner*, bool& bOutFailed) override;` — FIssuedTask interface
- L262 _public prototype_ `virtual bool Complete(CodeRunner*) override;`
- L265 _private member_ `int32 FirstIndex = -1;`
- L266 _private member_ `EMeshContentFlags RomContentFlags = EMeshContentFlags::None;`
- L267 _private member_ `EMeshContentFlags ExecutionContentFlags = EMeshContentFlags::None;`
- L270 _private member_ `TMap<int32, Tasks::TTask<TManagedPtr<const FMesh>>> RomsStreamed;` — Key is the rom index. Value is the future of the streamed rom.

#### class `UE::Mutable::Private::CodeRunner::FLoadImageRomsTask`  
`class FLoadImageRomsTask : public CodeRunner::FIssuedTask`  
_L273-292_
- inherits: `CodeRunner::FIssuedTask`
- L276 _public function_ `FLoadImageRomsTask(const FScheduledOp& InOp, int32 InImageIndexBegin, int32 InImageIndexEnd) : FIssuedTask(InOp) , ImageIndexBegin(InImageIndexBegin) , ImageIndexEnd(InImageIndexEnd)`
- L284 _public prototype_ `virtual bool Prepare(CodeRunner*, bool& bOutFailed) override;` — FIssuedTask interface
- L285 _public prototype_ `virtual bool Complete(CodeRunner*) override;`
- L288 _private member_ `int32 ImageIndexBegin = -1;`
- L289 _private member_ `int32 ImageIndexEnd = -1;`
- L291 _private member_ `TMap<int32, Tasks::TTask<TManagedPtr<const FImage>>> RomsStreamed;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L71 _member_ `float Bifactor;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350208`)
- L72 _member_ `int32 Min, Max;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350208`)
- L72 _member_ `int32 Min, Max;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350208`)
- L73 _member_ `} Interpolate;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L77 _member_ `int32 Iterations;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350308`)
- L78 _member_ `EImageFormat OriginalBaseFormat;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350308`)
- L79 _member_ `bool bBlendOnlyOneMip;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350308`)
- L80 _member_ `} MultiLayer;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L84 _member_ `uint8 Mip;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350408`)
- L85 _member_ `float MipValue;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350408`)
- L86 _member_ `} RasterMesh;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L90 _member_ `uint16 SizeX;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350508`)
- L91 _member_ `uint16 SizeY;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350508`)
- L92 _member_ `uint16 ScaleXEncodedHalf;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350508`)
- L93 _member_ `uint16 ScaleYEncodedHalf;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350508`)
- L94 _member_ `float MipValue;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350508`)
- L95 _member_ `} ImageTransform;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L99 _member_ `uint16 NumElemsToProcess;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350608`)
- L100 _member_ `uint8 SourceLOD : 7;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350608`)
- L101 _member_ `uint8 bHasBlocksToCompose : 1;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350608`)
- L103 _member_ `uint8 SourceNumLODs : 7;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350608`)
- L104 _member_ `uint8 bSplitInMultipleIterations : 1;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350608`)
- L105 _member_ `} MultiCompose;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L109 _member_ `FOperation::ADDRESS ImageAddress;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a::__anondb3994350708`)
- L110 _member_ `} MaterialBreak;` (scope `UE::Mutable::Private::CodeRunner::FScheduledOpData::__anondb399435010a`)
- L665 _prototype_ `extern FImageOperator MakeImageOperator(CodeRunner* Runner);` (scope `UE::Mutable::Private`) — Helper function to create the memory-tracked image operator.
- L668 _prototype_ `TSharedPtr<FRangeIndex> BuildCurrentOpRangeIndex(const FScheduledOp& Item, const FParameters& Params, const FModel& InModel, FProgramCache& ProgramCache, int32 ParameterIndex);` (scope `UE::Mutable::Private`)
- L672 _namespace_ `namespace UE`
- L672 _namespace_ `namespace Mutable` (scope `UE`)
- L672 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L672 _namespace_ `namespace Private` (scope `UE::Mutable::Private`)
- L674 _prototype_ `FString DumpItemScheduledCallstack(const FScheduledOp& Item);` (scope `UE::Mutable::Private::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/CodeRunnerBegin.h` (Private)


#### struct `UE::Mutable::Private::FScheduledOpInline`  
`struct FScheduledOpInline`  
_L19-58_
- L21 _public function_ `explicit FScheduledOpInline(FOperation::ADDRESS InAt = 0, const uint16 InStage = 0, const uint16 InExecutionIndex = 0, bool bInEvaluate = true) : At(InAt), Stage(InStage), bEvaluate(bInEvaluate), ExecutionIndex(InExecutionIndex)`
- L29 _public function_ `explicit FScheduledOpInline(FOperation::ADDRESS InAt, const FScheduledOpInline& InOpTemplate) : At(InAt), bEvaluate(InOpTemplate.bEvaluate), ExecutionIndex(InOpTemplate.ExecutionIndex)`
- L36 _public function_ `explicit FScheduledOpInline(FOperation::ADDRESS InAt, const FScheduledOpInline& InOpTemplate, bool bInEvaluate) : At(InAt), bEvaluate(bInEvaluate), ExecutionIndex(InOpTemplate.ExecutionIndex)`
- L43 _public function_ `FScheduledOpInline(const FScheduledOpInline& InOpTemplate, uint16 InStage) : At(InOpTemplate.At), Stage(InStage), bEvaluate(InOpTemplate.bEvaluate), ExecutionIndex(InOpTemplate.ExecutionIndex)`
- L51 _public prototype_ `bool operator==(const FScheduledOpInline& Other) const;`
- L53 _public member_ `FOperation::ADDRESS At = 0;`
- L54 _public member_ `uint8 Stage = 0;`
- L55 _public member_ `uint8 bEvaluate = 0;`
- L56 _public member_ `uint16 ExecutionIndex = 0;`
- L57 _public member_ `FOperation::ADDRESS CustomState = 0;`

#### struct `UE::Mutable::Private::FCacheAddressInline`  
`struct FCacheAddressInline`  
_L64-81_
- L66 _public function_ `FCacheAddressInline(const FOperation::ADDRESS& InAt)`
- L71 _public function_ `FCacheAddressInline(const FScheduledOpInline& Item)`
- L77 _public member_ `FOperation::ADDRESS At = 0;`
- L78 _public member_ `uint16 ExecutionIndex = 0;`
- L80 _public prototype_ `bool operator==(const FCacheAddressInline&) const = default;`

#### class `UE::Mutable::Private::FOpSet`  
`class FOpSet`  
_L87-99_
- L90 _public prototype_ `FOpSet(int32 NumElements);`
- L92 _public prototype_ `bool Contains(const FCacheAddressInline& Item);`
- L94 _public prototype_ `void Add(const FCacheAddressInline& Item);`
- L98 _private member_ `TSet<FCacheAddressInline> IndexOther;` — TBitArray<> Index0;

#### class `UE::Mutable::Private::FStack`  
`class FStack : public TArray<FStackValue, TInlineAllocator<32>>`  
_L103-107_
- inherits: `TArray<FStackValue,TInlineAllocator<32>>`
- L106 _public prototype_ `FStackValue Pop();`

#### class `UE::Mutable::Private::CodeRunnerBegin`  
`class CodeRunnerBegin`  
_L109-158_
- L112 _public prototype_ `CodeRunnerBegin( const TSharedRef<FLiveInstance>& InLiveInstance, uint32 InLodMask);`
- L116 _public prototype_ `void RunCode(const FScheduledOpInline& Root);`
- L119 _private prototype_ `FScheduledOpInline PopOp();`
- L120 _private prototype_ `void PushOp(const FScheduledOpInline& Item);`
- L122 _private prototype_ `void StoreNone(const FCacheAddressInline& To);`
- L124 _private prototype_ `void StoreInt(const FCacheAddressInline& To, int32 Value);`
- L125 _private prototype_ `void StoreFloat(const FCacheAddressInline& To, float Value);`
- L126 _private prototype_ `void StoreBool(const FCacheAddressInline& To, bool Value);`
- L128 _private prototype_ `int32 LoadInt(const FCacheAddressInline& To);`
- L129 _private prototype_ `float LoadFloat(const FCacheAddressInline& To);`
- L130 _private prototype_ `bool LoadBool(const FCacheAddressInline& To);`
- L132 _private member_ `TSharedPtr<const FModel> Model;`
- L133 _private member_ `TSharedPtr<const FParameters> Params;`
- L135 _private member_ `const FProgram& Program;`
- L137 _private member_ `uint32 LodMask;`
- L140 _private member_ `TArray<FScheduledOpInline, TInlineAllocator<256, TAlignedHeapAllocator<PLATFORM_CACHE_LINE_SIZE>>> Items;` — Operations we have yet to process.
- L145 _private member_ `FStack Stack;` — Stack of data objects generated during the evaluation of the mutable tree. Can be used to pass data from one stage/op to another during the tree evaluation process
- L148 _private member_ `FOpSet Executed;` — Collection of operations already processed.
- L151 _private member_ `TMap<FCacheAddressInline, float> ResultsFloat;` — Data caches with the already resolved data. Used to prevent the reevaluation of branches that have already been evaluated.
- L152 _private member_ `TMap<FCacheAddressInline, bool> ResultsBool;`
- L153 _private member_ `TMap<FCacheAddressInline, int32> ResultsInt;`
- L155 _private member_ `TSharedPtr<FProgramCache> ProgramCache;`
- L157 _private member_ `TSharedPtr<FPassthroughObjectLoader> PassthroughObjectLoader;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L61 _prototype_ `uint32 GetTypeHash(const FScheduledOpInline& Op);` (scope `UE::Mutable::Private`)
- L84 _prototype_ `uint32 GetTypeHash(const FCacheAddressInline& Address);` (scope `UE::Mutable::Private`)
- L101 _typedef_ `using FStackValue = TVariant<bool, int32, float, TManagedPtr<const String>, TManagedPtr<const FInstance>, TManagedPtr<const FMaterial>>;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/Config.h` (Private)
_(no declarations extracted)_

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/GeometryUtils.h` (Private)


#### struct `UE::Mutable::Private::GeometryUtils::FMeshGeometry`  
`struct FMeshGeometry`  
_L17-33_
- L21 _public prototype_ `FMeshGeometry() = default;`
- L23 _public member_ `TConstArrayView<FVector3f> Positions;`
- L24 _public member_ `TConstArrayView<UE::Geometry::FIndex3i> Triangles;`
- L27 _public member_ `TConstArrayView<FVector3f> Normals;` — Optional, no elements indicate the data is not avaliable.
- L30 _public member_ `TArray<FVector3f> OptionalPositionsStorage;` — It can be used for storing the a format conversion.
- L31 _public member_ `TArray<FVector3f> OptionalNormalsStorage;`
- L32 _public member_ `TArray<UE::Geometry::FIndex3i> OptionalTrianglesStorage;`

#### struct `UE::Mutable::Private::GeometryUtils::FMeshAdapter`  
`struct FMeshAdapter`  
_L35-97_
- L37 _public member_ `FMeshGeometry& Mesh;`
- L39 _public function_ `FMeshAdapter(FMeshGeometry& InMesh) : Mesh(InMesh)`
- L44 _public function_ `int32 MaxTriangleID() const`
- L49 _public function_ `int32 MaxVertexID() const`
- L54 _public function_ `bool IsTriangle(int32 Index) const`
- L59 _public function_ `bool IsVertex(int32 Index) const`
- L64 _public function_ `int32 TriangleCount() const`
- L69 _public function_ `FORCEINLINE int32 VertexCount() const`
- L74 _public function_ `FORCEINLINE uint64 GetChangeStamp() const`
- L79 _public function_ `FORCEINLINE UE::Geometry::FIndex3i GetTriangle(int32 Index) const`
- L84 _public function_ `FORCEINLINE FVector3d GetVertex(int32 Index) const`
- L89 _public function_ `FORCEINLINE void GetTriVertices(int32 TriIndex, FVector3d& V0, FVector3d& V1, FVector3d& V2) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _namespace_ `namespace GeometryUtils` (scope `UE::Mutable::Private`)
- L99 _prototype_ `void GetMergedGeometryFromMeshes(TArrayView<TNotNull<const FMesh*>> Meshes, bool bNeedsNormals, FMeshGeometry& OutResult);` (scope `UE::Mutable::Private::GeometryUtils`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/ImageComputeUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L9 _namespace_ `namespace ImageComputeUtils` (scope `UE::Mutable::Private`)
- L11 _prototype_ `void Lerp_U8(uint8* Dest, const uint8* A, const uint8* B, const uint8* Factor, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L13 _prototype_ `void Vec4ToVec1_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L14 _prototype_ `void Vec4ToVec3_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L15 _prototype_ `void Vec3ToVec1_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L16 _prototype_ `void Vec3ToVec4_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L17 _prototype_ `void Vec1ToVec3_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L18 _prototype_ `void Vec1ToVec4_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L20 _prototype_ `void Vec4SelectX_U8(uint8* Dest, const uint8* A, const uint8* B, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L21 _prototype_ `void Vec4SelectY_U8(uint8* Dest, const uint8* A, const uint8* B, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L22 _prototype_ `void Vec4SelectZ_U8(uint8* Dest, const uint8* A, const uint8* B, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L23 _prototype_ `void Vec4SelectW_U8(uint8* Dest, const uint8* A, const uint8* B, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L25 _prototype_ `void Vec4SwizzleWWWWAndConvertToVec1_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L26 _prototype_ `void Vec4SwizzleWWWWAndConvertToVec3_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L27 _prototype_ `void Vec4SwizzleXXXX_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L28 _prototype_ `void Vec4SwizzleWWWW_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L29 _prototype_ `void Vec4SwizzleZYXW_U8(uint8* Dest, const uint8* Src, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L31 _prototype_ `void Vec4Fill_U8(uint8* Dest, FColor Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L32 _prototype_ `void Vec3Fill_U8(uint8* Dest, FColor Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L33 _prototype_ `void Vec1Fill_U8(uint8* Dest, FColor Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L35 _prototype_ `void Vec4Fill_U16(uint16* Dest, Math::TIntVector4<uint16> Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L36 _prototype_ `void Vec3Fill_U16(uint16* Dest, Math::TIntVector4<uint16> Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L37 _prototype_ `void Vec1Fill_U16(uint16* Dest, Math::TIntVector4<uint16> Value, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)
- L39 _prototype_ `bool TestZero_U8(const uint8* Data, int32 NumElems);` (scope `UE::Mutable::Private::ImageComputeUtils`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/ImageFormatUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L11 _namespace_ `namespace SubImageFormat` (scope `UE::Mutable::Private`)
- L14 _prototype_ `miro::SubImageDecompression::FuncRefType SelectDecompressionFunction(EImageFormat DestFormat, EImageFormat SrcFormat);` (scope `UE::Mutable::Private::SubImageFormat`)
- L15 _prototype_ `miro::SubImageCompression::FuncRefType SelectCompressionFunction(EImageFormat DestFormat, EImageFormat SrcFormat);` (scope `UE::Mutable::Private::SubImageFormat`)
- L17 _typedef_ `using UncompressedFormatFuncType = void(FImageSize, FImageSize, FImageSize, const uint8*, uint8*);` (scope `UE::Mutable::Private::SubImageFormat`)
- L18 _prototype_ `UncompressedFormatFuncType* SelectUncompressedFormatFunction(EImageFormat DestFormat, EImageFormat SrcFormat);` (scope `UE::Mutable::Private::SubImageFormat`)
- L20 _prototype_ `void SubImageVec3ToVec4_U8(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* From, uint8* To);` (scope `UE::Mutable::Private::SubImageFormat`)
- L21 _prototype_ `void SubImageVec4ToVec3_U8(FImageSize FromSize, FImageSize ToSize, FImageSize SubSize, const uint8* From, uint8* To);` (scope `UE::Mutable::Private::SubImageFormat`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/ImageRLE.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L30 _prototype_ `extern void CompressRLE_L(uint32& OutCompressedSize, int32 Width, int32 Rows, const uint8* BaseData, uint8* DestData, uint32 DestDataSize);` (scope `UE::Mutable::Private`)
- L35 _prototype_ `extern uint32 UncompressRLE_L(int32 Width, int32 Rows, const uint8* BaseData, uint8* pDestData);` (scope `UE::Mutable::Private`)
- L39 _prototype_ `extern uint64 GetBeginTokenIterativeDecodeRLE_L(const uint8* Src, int32 NumRows);` (scope `UE::Mutable::Private`)
- L40 _prototype_ `extern void IterativeDecodeRLE_L(uint8* Dest, const uint8* Src, uint64& InOutDecodeToken, int32 NumElems);` (scope `UE::Mutable::Private`)
- L48 _prototype_ `extern void CompressRLE_L1(uint32& OutCompressedSize, int32 Width, int32 Rows, const uint8* BaseData, uint8* DestData, uint32 DestDataSize);` (scope `UE::Mutable::Private`)
- L54 _prototype_ `extern uint32 UncompressRLE_L1(int32 Width, int32 Rows, const uint8* pBaseData, uint8* pDestData);` (scope `UE::Mutable::Private`)
- L68 _prototype_ `extern void CompressRLE_RGBA(uint32& OutCompressedSize, int32 Width, int32 Rows, const uint8* pBaseDataByte, uint8* DestData, uint32 DestDataSize);` (scope `UE::Mutable::Private`)
- L73 _prototype_ `extern void UncompressRLE_RGBA(int32 Width, int32 Rows, const uint8* pBaseData, uint8* pDestDataB);` (scope `UE::Mutable::Private`)
- L87 _prototype_ `extern void CompressRLE_RGB(uint32& OutCompressedSize, int32 Width, int32 Rows, const uint8* pBaseDataByte, uint8* DestData, uint32 DestDataSize);` (scope `UE::Mutable::Private`)
- L92 _prototype_ `extern void UncompressRLE_RGB(int32 Width, int32 Rows, const uint8* pBaseData, uint8* pDestDataB);` (scope `UE::Mutable::Private`)
- L97 _function_ `inline void UncompressRLE_L(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L115 _function_ `inline void CompressRLE_L(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L149 _function_ `inline void CompressRLE_L1(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L183 _function_ `inline void UncompressRLE_L1(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L201 _function_ `inline void CompressRLE_RGB(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L235 _function_ `inline void UncompressRLE_RGB(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L253 _function_ `inline void CompressRLE_RGBA(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)
- L287 _function_ `inline void UncompressRLE_RGBA(const FImage* BaseImage, FImage* DestImage)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/ImageResizeUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L11 _namespace_ `namespace SubImageResize` (scope `UE::Mutable::Private`)
- L13 _typedef_ `using SubImageResizeFuncType = void(FVector2f, FVector2f, FImageSize, FImageSize, FImageSize, FImageSize, uint8*, const uint8*);` (scope `UE::Mutable::Private::SubImageResize`)
- L15 _prototype_ `SubImageResizeFuncType* SelectSubImageResizeFunc(EImageFormat Format);` (scope `UE::Mutable::Private::SubImageResize`)
- L17 _prototype_ `void SubImageResizeLinearByLessThanTwoVec1_U8( FVector2f OneOverScalingFactor, FVector2f SrcSubPixelOffset, FImageSize DestSize, FImageSize DestSubSize, FImageSize SrcSize, FImageSize SrcSubSize, uint8* RESTRICT SubDest, const uint8* RESTRICT SubSrc);` (scope `UE::Mutable::Private::SubImageResize`)
- L25 _prototype_ `void SubImageResizeLinearByLessThanTwoVec3_U8( FVector2f OneOverScalingFactor, FVector2f SrcSubPixelOffset, FImageSize DestSize, FImageSize DestSubSize, FImageSize SrcSize, FImageSize SrcSubSize, uint8* RESTRICT SubDest, const uint8* RESTRICT SubSrc);` (scope `UE::Mutable::Private::SubImageResize`)
- L33 _prototype_ `void SubImageResizeLinearByLessThanTwoVec4_U8( FVector2f OneOverScalingFactor, FVector2f SrcSubPixelOffset, FImageSize DestSize, FImageSize DestSubSize, FImageSize SrcSize, FImageSize SrcSubSize, uint8* RESTRICT SubDest, const uint8* RESTRICT SubSrc);` (scope `UE::Mutable::Private::SubImageResize`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageApplyComposite.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L9 _prototype_ `void ImageNormalComposite(FImage* ResultImage, const FImage* BaseImage, const FImage* NormalImage, int32 NormalRoughnessOutputChannel, float Power);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageBinarise.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L17 _function_ `inline void ImageBinarise(FImage* DestImage, const FImage* AImage, float Threshold)` (scope `UE::Mutable::Private`)
- L39 _function_ `` (scope `UE::Mutable::Private::ImageBinarise`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageBlend.h` (Private)


#### struct `UE::Mutable::Private::FNormalCompositeIdentityFunctor`  
`struct FNormalCompositeIdentityFunctor`  
_L277-283_
- L279 _public function_ `uint32 operator()(uint32 Base, uint32) const`

#### struct `UE::Mutable::Private::FNormalCompositeFunctor`  
`struct FNormalCompositeFunctor`  
_L286-295_
- L288 _public member_ `const uint8 Channel;`
- L289 _public member_ `const float Power;`
- L291 _public function_ `uint32 operator()(uint32 Base, uint32 Normal) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L11 _function_ `inline uint32 BlendChannel( uint32` (scope `UE::Mutable::Private`) — base
- L17 _function_ `inline uint32 BlendChannelMasked( uint32 base, uint32 blended, uint32 mask )` (scope `UE::Mutable::Private`)
- L26 _function_ `inline uint32 ScreenChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L34 _function_ `inline uint32 ScreenChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L42 _function_ `inline uint32 SoftLightChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L52 _function_ `inline uint32 SoftLightChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L60 _function_ `inline uint32 HardLightChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L77 _function_ `inline uint32 HardLightChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L86 _function_ `inline uint32 BurnChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L98 _function_ `inline uint32 BurnChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L106 _function_ `inline uint32 DodgeChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L114 _function_ `inline uint32 DodgeChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L122 _function_ `inline uint32 LightenChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L129 _function_ `inline uint32 LightenChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L136 _function_ `inline uint32 MultiplyChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L143 _function_ `inline uint32 MultiplyChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L150 _function_ `inline uint32 OverlayChannelMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L158 _function_ `inline uint32 OverlayChannel(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`)
- L165 _function_ `FORCEINLINE VectorRegister4Int VectorBlendChannelMasked( const VectorRegister4Int& Base, const VectorRegister4Int& Blended, const VectorRegister4Int& Mask)` (scope `UE::Mutable::Private`)
- L178 _function_ `FORCEINLINE int32 VectorLightenChannel(int32 Base, int32 Blended)` (scope `UE::Mutable::Private`)
- L184 _function_ `inline uint32 CombineNormal(uint32 base, uint32 blended)` (scope `UE::Mutable::Private`) — Combine layer oprations get packed color.
- L210 _function_ `inline uint32 CombineNormalMasked(uint32 base, uint32 blended, uint32 mask)` (scope `UE::Mutable::Private`)
- L240 _function_ `inline uint32 NormalComposite( const uint32 Base, const uint32 Normal, const uint8 Channel, const float Power )` (scope `UE::Mutable::Private`) — Combine layer oprations get packed color.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageColorMap.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _function_ `inline void ImageColorMap(FImage* DestImage, const FImage* SourceImage, const FImage* MaskImage, const FImage* MapImage, bool bOnlyOneMip)` (scope `UE::Mutable::Private`)
- L49 _function_ `` (scope `UE::Mutable::Private::ImageColorMap`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageDisplace.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `inline uint8 MutableEncodeOffset(int32 X, int32 Y)` (scope `UE::Mutable::Private`)
- L26 _function_ `inline void MutableDecodeOffset(uint8 C, int32& X, int32& Y)` (scope `UE::Mutable::Private`)
- L35 _function_ `inline void ImageMakeGrowMap(FImage* ResultImage, FImage* MaskImage, int32 InBorder)` (scope `UE::Mutable::Private`)
- L71 _function_ `` (scope `UE::Mutable::Private::ImageMakeGrowMap`)
- L84 _function_ `` (scope `UE::Mutable::Private::ImageMakeGrowMap::__anon543fe5070102`)
- L144 _function_ `inline void ImageDisplace(FImage* ResultImage, const FImage* SourceImage, const FImage* MapImage)` (scope `UE::Mutable::Private`)
- L184 _function_ `` (scope `UE::Mutable::Private::ImageDisplace`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageGradient.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L12 _function_ `inline void ImageGradient( FImage* pDest, const FVector4f& c0, const FVector4f& c1 )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageInterpolate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _function_ `inline void ImageInterpolate(FImage* DestImage, const FImage* BImage, float Factor)` (scope `UE::Mutable::Private`)
- L38 _function_ `` (scope `UE::Mutable::Private::ImageInterpolate`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageInvert.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `template<bool bUseVectorImpl = false> inline void ImageInvert(FImage* AImage)` (scope `UE::Mutable::Private`) — Invert the color (RGB or L) components of an image. Leave alpha untouched.
- L34 _function_ `` (scope `UE::Mutable::Private::ImageInvert`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageLayer.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L11 _typedef_ `using FBlendFuncType = void(uint8*, const uint8*, const uint8*, int32);` (scope `UE::Mutable::Private`)
- L13 _namespace_ `namespace OpImageLayerBlendOps` (scope `UE::Mutable::Private`)
- L15 _prototype_ `void Blend (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L16 _prototype_ `void Screen (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L17 _prototype_ `void SoftLight(uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L18 _prototype_ `void HardLight(uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L19 _prototype_ `void Dodge (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L20 _prototype_ `void Lighten (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L21 _prototype_ `void Burn (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L22 _prototype_ `void Multiply (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L23 _prototype_ `void Overlay (uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerBlendOps`)
- L26 _typedef_ `using FCombineFuncType = void(uint8*, const uint8*, const uint8*, int32);` (scope `UE::Mutable::Private`)
- L27 _namespace_ `namespace OpImageLayerCombineOps` (scope `UE::Mutable::Private`)
- L29 _prototype_ `void NormalCombine(uint8* Dest, const uint8* Base, const uint8* Blen, int32 NumElems);` (scope `UE::Mutable::Private::OpImageLayerCombineOps`)
- L34 _prototype_ `void ImageBlendOnBaseNoAlpha(FImage* BaseImage, const FImage* MaskImage, const FImage* BlendedImage, const box<FIntVector2>& Rect);` (scope `UE::Mutable::Private`) — Blend a subimage on the base using a mask
- L36 _prototype_ `FBlendFuncType* SelectBlendFunc(EBlendType BlendType);` (scope `UE::Mutable::Private`)
- L38 _prototype_ `void ImageLayerBlend( FImage* Dest, const FImage* Base, const FImage* Blend, const FImage* Mask, FBlendFuncType* ColorBlendFunc, FBlendFuncType* AlphaBlendFunc, int32 LODBegin, int32 LODEnd, bool bApplyColorBlendToAlpha, bool bUseMaskFromBlendAlpha, bool bUseBaseSourceFromBaseAlpha, bool bUseBlendSourceFromBlendAlpha, uint8 BlendAlphaSourceChannel);` (scope `UE::Mutable::Private`)
- L48 _prototype_ `void ImageLayerBlendConstant( FImage* Dest, const FImage* Base, const FImage* Mask, const FVector4f& Constant, FBlendFuncType* ColorBlendFunc, FBlendFuncType* AlphaBlendFunc, int32 LODBegin, int32 LODEnd, bool bApplyColorBlendToAlpha, bool bUseMaskFromBlendAlpha, bool bUseBaseSourceFromBaseAlpha, bool bUseBlendSourceFromBlendAlpha, uint8 BlendAlphaSourceChannel);` (scope `UE::Mutable::Private`)
- L58 _prototype_ `void ImageLayerCombine( FImage* Dest, const FImage* Base, const FImage* Blend, const FImage* Mask, FCombineFuncType* CombineFunc, int32 LODBegin, int32 LODEnd);` (scope `UE::Mutable::Private`)
- L63 _prototype_ `void ImageLayerCombineConstant( FImage* Dest, const FImage* Base, const FImage* Mask, const FVector4f& Constant, FCombineFuncType* CombineFunc, int32 LODBegin, int32 LODEnd);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageLuminance.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L12 _function_ `inline void ImageLuminance(FImage* DestImage, const FImage* AImage)` (scope `UE::Mutable::Private`)
- L26 _function_ `` (scope `UE::Mutable::Private::ImageLuminance`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageMultiCompose.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Mutable` (scope `UE`)
- L6 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L29 _prototype_ `void ImageMultiCompose(FImage& Base, const FImage& Source, TConstArrayView<FIntRect> DstRectsInPixels, TConstArrayView<FIntRect> SrcRectsInPixels, TConstArrayView<int32> SourceLODPerRect, int32 CompressionQuality);` (scope `UE::Mutable::Private`) — Composes an image using multiple rects from the same source image. @param Base                Base image where the composing Rects will be copied. @param Source              Source image from where the composing Rects data will be extracted. @param DstRectsInPixels    Rects in pixels of regions of the Base image to be composed. @param SrcRectsInPixels    Rects in pixels of regions of the Source image to compose, i-th SrcRectsInPixels region content will be copied to i-th DstRectsInPixels region. SrcRectsInPixels must have the same number of elements than DstRectsInPixels. @param SourceLODPerRect    Source LOD index where the i-th SrcRect is extracted from. Number of pixels in SrcRect are expected to be based on the Source image's LOD index dimensions. SourceLODPerRect must have the same number of elements than SrcRectsInPixels. @param CompressionQuality Quality level used by the block compression functions.
- L40 _prototype_ `float ImageMultiComposeComputeBestLODForSrcRect(const FIntRect& DstRectInPixels, const FIntRect& SrcRectInPixels);` (scope `UE::Mutable::Private`) — Computes the best LOD bias for an image going from SrcRectInPixels dimensions to DstRectInPixels dimensions. @param DstRectInPixels The destination rect used for getting the dimensions used for the computation. @param SrcRectInPixels The source rect used for getting the dimensions used for the computation. @return                LOD bias needed to apply to SrcRect to get the dimensions closest to DstRect.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageRasterMesh.h` (Private)


#### class `UE::Mutable::Private::WhitePixelProcessor`  
`class WhitePixelProcessor`  
_L15-27_
- L18 _public function_ `inline void ProcessPixel(uint8* pBufferPos, float[1]) const`
- L23 _public function_ `inline void operator()(uint8* BufferPos, float Interpolators[1]) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L30 _function_ `inline void ImageRasterMesh( const FMesh* pMesh, FImage* pImage, int32 LayoutIndex, uint64 BlockId, UE::Math::TIntVector2<uint16> CropMin, UE::Math::TIntVector2<uint16> UncroppedSize )` (scope `UE::Mutable::Private`)
- L118 _function_ `` (scope `UE::Mutable::Private::ImageRasterMesh`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageSaturate.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `template<bool bUseVectorImpl = false> inline void ImageSaturate(FImage* AImage, float Factor)` (scope `UE::Mutable::Private`)
- L40 _function_ `` (scope `UE::Mutable::Private::ImageSaturate`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageTransform.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `inline void ImageTransform( FImage* pDestImage, const FImage* pImage, FTransform2f Transform, float MipFactor, EAddressMode AddressMode, bool bUseVectorImplCvar)` (scope `UE::Mutable::Private`)
- L30 _function_ `` (scope `UE::Mutable::Private::ImageTransform`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpImageTransformPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L19 _prototype_ `template<int32 NumChannels, EAddressMode, bool bUseVectorImpl> void ImageTransformImpl(uint8* DestData, FIntVector2 DestSize, FIntRect DestCropRect, const uint8* Src0Data, FIntVector2 Src0Size, const uint8* Src1Data, FIntVector2 Src1Size, float MipFactor, const FTransform2f& Transform);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpLayoutPack.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Mutable` (scope `UE`)
- L6 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L10 _prototype_ `extern void LayoutPack3(FLayout* Result, const FLayout* SourceLayout);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpLayoutRemoveBlocks.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _function_ `inline TManagedPtr<FLayout> LayoutFromMesh_RemoveBlocks(const FMesh* InMesh, int32 InLayoutIndex)` (scope `UE::Mutable::Private`)
- L120 _function_ `inline TManagedPtr<FLayout> LayoutRemoveBlocks(const FLayout* Source, const FLayout* ReferenceLayout)` (scope `UE::Mutable::Private`)
- L142 _function_ `inline TManagedPtr<FLayout> LayoutMerge(const FLayout* pA, const FLayout* pB )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshApplyLayout.h` (Private)


#### struct `UE::Mutable::Private::MeshApplyLayout::Box`  
`struct Box`  
_L46-49_
- L48 _public member_ `FVector2f min, size;`
- L48 _public member_ `FVector2f min, size;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `inline void MeshApplyLayout( FMesh* Applied, const FLayout* InLayout, int32 TexCoordsIndex )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshApplyPose.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _function_ `inline void SetPoseAsReference(FMesh* InOutResult, const FMesh* PoseMesh, const TArray<int32>& BoneToPoseIndex)` (scope `UE::Mutable::Private`)
- L45 _function_ `inline void MeshApplyPose(FMesh* Result, const FMesh* BaseMesh, const FMesh* PoseMesh, bool& bOutSuccess)` (scope `UE::Mutable::Private`) — Reference version
- L185 _function_ `` (scope `UE::Mutable::Private::MeshApplyPose`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshBind.h` (Private)


#### struct `UE::Mutable::Private::FReshapeVertexBindingData`  
`struct FReshapeVertexBindingData`  
_L38-105_
- L41 _public member_ `uint32 TriangleIndex_BindingType_NotValid;` — Index of the shape triangle and the type of binding, Cluster or Vertex.
- L44 _public member_ `FVector2f PositionBaryCoords;` — Barycentric coordinates on the shape triangle
- L47 _public member_ `FVector3f D;` — Distance along the normals of the shape triangle.
- L66 _public member_ `float Weight;` — Weight of the effect for this binding. Ranged between 0 and 1 where 0 denotes no effect at all and 1 full effect.
- L68 _public function_ `FORCEINLINE uint32 GetTriangleIndex() const`
- L73 _public function_ `FORCEINLINE bool IsClusterBinding() const`
- L78 _public function_ `FORCEINLINE bool IsValidBinding() const`
- L83 _public function_ `FORCEINLINE void SetTriangleIndex(uint32 Index)`
- L90 _public function_ `FORCEINLINE void SetClusterBinding(bool Value)`
- L97 _public function_ `FORCEINLINE void SetBindNotValid(bool Value)`

#### union `UE::Mutable::Private::FReshapeVertexBindingData::(anonymous)`  
``  
_L50-62_

#### struct `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::(anonymous)`  
``  
_L52-55_

#### struct `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::(anonymous)`  
``  
_L58-61_

#### struct `UE::Mutable::Private::FReshapeVertexBindingDataBufferDescriptor`  
`struct FReshapeVertexBindingDataBufferDescriptor`  
_L108-123_
- L110 _public member_ `constexpr static int32 ElementSize = sizeof(FReshapeVertexBindingData);`
- L111 _public member_ `constexpr static int32 Channels = 4;`
- L112 _public member_ `constexpr static EMeshBufferSemantic Semantics[Channels] = { EMeshBufferSemantic::TriangleIndex, EMeshBufferSemantic::BarycentricCoords, EMeshBufferSemantic::Distance, EMeshBufferSemantic::Other };`
- L113 _public member_ `constexpr static EMeshBufferFormat Formats[Channels] = { EMeshBufferFormat::UInt32, EMeshBufferFormat::Float32, EMeshBufferFormat::Float32, EMeshBufferFormat::Float32 };`
- L114 _public member_ `constexpr static int32 Components[Channels] = { 1, 2, 3, 3+3+1 };`
- L115 _public member_ `constexpr static int32 Offsets[Channels] = { 0, 1*4, (1+2)*4, (1+2+3)*4 };`
- L117 _public member_ `const int32 SemanticIndices[Channels] = { 0, 0, 0, 0 };`
- L119 _public function_ `FReshapeVertexBindingDataBufferDescriptor(int32 DataSetIndex) : SemanticIndices`

#### struct `UE::Mutable::Private::FReshapePointBindingData`  
`struct FReshapePointBindingData`  
_L125-131_
- L127 _public member_ `float S, T;`
- L127 _public member_ `float S, T;`
- L128 _public member_ `FVector3f D;`
- L129 _public member_ `int32 Triangle;`
- L130 _public member_ `float Weight;`

#### struct `UE::Mutable::Private::FReshapePointBindingDataBufferDescriptor`  
`struct FReshapePointBindingDataBufferDescriptor`  
_L135-150_
- L137 _public member_ `constexpr static int32 ElementSize = sizeof(FReshapeVertexBindingData);`
- L138 _public member_ `constexpr static int32 Channels = 4;`
- L139 _public member_ `constexpr static EMeshBufferSemantic Semantics[Channels] = { EMeshBufferSemantic::BarycentricCoords, EMeshBufferSemantic::Distance, EMeshBufferSemantic::TriangleIndex, EMeshBufferSemantic::Other };`
- L140 _public member_ `constexpr static EMeshBufferFormat Formats[Channels] = { EMeshBufferFormat::Float32, EMeshBufferFormat::Float32, EMeshBufferFormat::Int32, EMeshBufferFormat::Float32 };`
- L141 _public member_ `constexpr static int32 Components[Channels] = { 2, 3, 1, 1 };`
- L142 _public member_ `constexpr static int32 Offsets[Channels] = { 0, 8, 20, 24 };`
- L144 _public member_ `const int32 SemanticIndices[Channels] = { 0, 0, 0, 0 };`
- L146 _public function_ `FReshapePointBindingDataBufferDescriptor(int32 DataSetIndex) : SemanticIndices`

#### struct `UE::Mutable::Private::FIntBufferDescriptor`  
`struct FIntBufferDescriptor`  
_L152-165_
- L154 _public member_ `constexpr static int32 ElementSize = sizeof(int32);`
- L155 _public member_ `constexpr static int32 Channels = 1;`
- L156 _public member_ `constexpr static EMeshBufferSemantic Semantics[Channels] = { EMeshBufferSemantic::Other };`
- L157 _public member_ `constexpr static EMeshBufferFormat Formats[Channels] = { EMeshBufferFormat::Int32 };`
- L158 _public member_ `constexpr static int32 Components[Channels] = { 1 };`
- L159 _public member_ `constexpr static int32 Offsets[Channels] = { 0 };`
- L160 _public member_ `constexpr static int32 SemanticIndices[Channels] = { 0 };`
- L162 _public function_ `FIntBufferDescriptor()`

#### struct `UE::Mutable::Private::FClipDeformVertexBindingData`  
`struct FClipDeformVertexBindingData`  
_L171-180_
- desc: Structure used for vertex bing data in vertexbuffers for Clip deform operations.
- L174 _public member_ `float S, T;` — Barycentric coordinates on the shape triangle
- L174 _public member_ `float S, T;` — Barycentric coordinates on the shape triangle
- L177 _public member_ `int32 Triangle;` — Index of the shape triangle.
- L179 _public member_ `float Weight;`

#### struct `UE::Mutable::Private::FClipDeformVertexBindingDataBufferDescriptor`  
`struct FClipDeformVertexBindingDataBufferDescriptor`  
_L183-197_
- L185 _public member_ `constexpr static int32 Channels = 3;`
- L186 _public member_ `constexpr static EMeshBufferSemantic Semantics[Channels] = { EMeshBufferSemantic::BarycentricCoords, EMeshBufferSemantic::TriangleIndex, EMeshBufferSemantic::Other };`
- L187 _public member_ `constexpr static EMeshBufferFormat Formats[Channels] = { EMeshBufferFormat::Float32, EMeshBufferFormat::Int32, EMeshBufferFormat::Float32 };`
- L188 _public member_ `constexpr static int32 Components[Channels] = { 2, 1, 1 };`
- L189 _public member_ `constexpr static int32 Offsets[Channels] = { 0, 8, 12 };`
- L191 _public member_ `const int32 SemanticIndices[Channels] = { 0, 0, 0 };`
- L193 _public function_ `FClipDeformVertexBindingDataBufferDescriptor(int32 DataSetIndex) : SemanticIndices`

#### struct `UE::Mutable::Private::FMeshBindColorChannelUsageMasks`  
`struct FMeshBindColorChannelUsageMasks`  
_L199-203_
- L201 _public member_ `uint32 MaskWeight = 0;`
- L202 _public member_ `uint32 ClusterId = 0;`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Mutable` (scope `UE`)
- L34 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L36 _typedef_ `using FShapeMeshTree = UE::Geometry::TMeshAABBTree3<GeometryUtils::FMeshAdapter>;` (scope `UE::Mutable::Private`)
- L53 _member_ `FVector3f NormalBaryCoords;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::__anon73da38e90208`) — NormalBaryCoords.Z is not used.
- L54 _member_ `FVector3f NormalD;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::__anon73da38e90208`)
- L55 _member_ `} Vertex;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a`)
- L59 _member_ `FVector3f AttachmentPoint;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::__anon73da38e90308`)
- L60 _member_ `FVector3f AttachmentNormal;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a::__anon73da38e90308`)
- L61 _member_ `} Cluster;` (scope `UE::Mutable::Private::FReshapeVertexBindingData::__anon73da38e9010a`)
- L167 _typedef_ `using ReshapePoseBindingType = FReshapePointBindingData;` (scope `UE::Mutable::Private`)
- L168 _typedef_ `using ReshapePhysicsBindingType = FReshapePointBindingData;` (scope `UE::Mutable::Private`)
- L209 _function_ `inline float GetVertexMaskWeight(const UntypedMeshBufferIteratorConst& ColorIter, const FMeshBindColorChannelUsageMasks& ChannelUsages)` (scope `UE::Mutable::Private`)
- L219 _function_ `inline uint32 GetVertexClusterId(const UntypedMeshBufferIteratorConst& ColorIter, const FMeshBindColorChannelUsageMasks& ChannelUsages)` (scope `UE::Mutable::Private`)
- L231 _function_ `FORCEINLINE FVector2f ComputeBarycentric(const FVector3f& Point, const FVector3f& A, const FVector3f& B, const FVector3f& C)` (scope `UE::Mutable::Private`)
- L253 _function_ `inline void BindReshapePoint( FShapeMeshTree& ShapeMeshTree, const FVector3f& Point, const FVector3f& Normal, float MaskWeight, FReshapeVertexBindingData& OutBindData, const float ValidityTolerance = UE_KINDA_SMALL_NUMBER)` (scope `UE::Mutable::Private`)
- L340 _function_ `inline void FindRigidClusters(const FMesh* Mesh, const FMeshBindColorChannelUsageMasks& ColorUsageMasks, TArray<TArray<int32>>& OutClusters, int32& OutNonRigidClusterIdx)` (scope `UE::Mutable::Private`)
- L397 _function_ `inline void FindBindingForCluster( const FMesh* BaseMesh, FShapeMeshTree& ShapeMeshTree, const TArray<int32>& Cluster, FReshapeVertexBindingData& OutBindingData, float BindTolerance)` (scope `UE::Mutable::Private`)
- L435 _function_ `inline TTuple<TArray<FReshapePointBindingData>, TArray<int32>, TArray<int32>> BindPhysicsBodies( TArray<const FPhysicsBody*> PhysicsBodies, FShapeMeshTree& ShapeMeshTree, const FMesh& Mesh, const FSkeleton& Skeleton, TConstArrayView<FName> PhysicsToDeform, bool bInvertSelection)` (scope `UE::Mutable::Private`)
- L710 _function_ `inline TArray<FReshapeVertexBindingData> BindVerticesReshape( const FMesh* BaseMesh, FShapeMeshTree& ShapeMeshTree, const FMeshBindColorChannelUsageMasks& ColorUsageMasks)` (scope `UE::Mutable::Private`)
- L766 _function_ `` (scope `UE::Mutable::Private::BindVerticesReshape`)
- L828 _function_ `inline void GenerateAndAddLaplacianData(FMesh& InOutMesh)` (scope `UE::Mutable::Private`)
- L945 _function_ `inline TTuple<TArray<FReshapePointBindingData>, TArray<int32>> BindPose( const FMesh& Mesh, const FSkeleton& Skeleton, FShapeMeshTree& ShapeMeshTree, TConstArrayView<FName> BonesToDeform, bool bInvertSelection)` (scope `UE::Mutable::Private`)
- L1001 _function_ `inline FMeshBindColorChannelUsageMasks MakeColorChannelUsageMasks(FMeshBindColorChannelUsages Usages)` (scope `UE::Mutable::Private`)
- L1031 _function_ `inline void MeshBindShapeReshape( FMesh* Result, UE::Geometry::TMeshAABBTree3<GeometryUtils::FMeshAdapter>& ShapeMeshTree, TConstArrayView<FName> BonesToDeform, TConstArrayView<FName> PhysicsToDeform, EMeshBindShapeFlags BindFlags, FMeshBindColorChannelUsages ColorChannelUsages, bool& bOutSuccess)` (scope `UE::Mutable::Private`)
- L1184 _function_ `inline void BindClipDeformPointClosestProject( FShapeMeshTree& ShapeMeshTree, const FVector3f& Point, FClipDeformVertexBindingData& OutBindData, float ValidityTolerance )` (scope `UE::Mutable::Private`)
- L1255 _function_ `inline void BindClipDeformPointClosestToSurface( const FShapeMeshTree& ShapeMeshTree, const FVector3f& Point, FClipDeformVertexBindingData& OutBindData)` (scope `UE::Mutable::Private`)
- L1296 _function_ `inline void BindClipDeformPointNormalProject( const FShapeMeshTree& ShapeMeshTree, const FVector3f& Point, const FVector3f& Normal, FClipDeformVertexBindingData& OutBindData)` (scope `UE::Mutable::Private`)
- L1331 _function_ `inline TArray<FClipDeformVertexBindingData> BindVerticesClipDeform( const FMesh* BaseMesh, FShapeMeshTree& ShapeMeshTree, EShapeBindingMethod BindingMethod )` (scope `UE::Mutable::Private`)
- L1402 _function_ `inline void MeshBindShapeClipDeform(FMesh* Result, UE::Geometry::TMeshAABBTree3<GeometryUtils::FMeshAdapter>& ShapeTree, EShapeBindingMethod BindingMethod, bool& bOutSuccess)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshClipDeform.h` (Private)


#### struct `UE::Mutable::Private::FClipDeformShapeMeshDescriptorApply`  
`struct FClipDeformShapeMeshDescriptorApply`  
_L32-38_
- L34 _public member_ `TArrayView<const FVector3f> Positions;`
- L35 _public member_ `TArrayView<const FVector3f> Normals;`
- L36 _public member_ `TArrayView<const float> Weights;`
- L37 _public member_ `TArrayView<const UE::Geometry::FIndex3i> Triangles;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Mutable` (scope `UE`)
- L29 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L41 _function_ `inline bool GetDeform( const FVector3f& Position, const FVector3f& Normal, const FClipDeformShapeMeshDescriptorApply& ShapeMesh, const FClipDeformVertexBindingData& Binding, FVector3f& OutPosition, FQuat4f& OutRotation, float& OutWeight)` (scope `UE::Mutable::Private`) — Method to actually deform a point
- L110 _function_ `inline void MeshClipDeform(FMesh* Result, const FMesh* BaseMesh, const FMesh* ShapeMesh, const float ClipWeightThreshold, bool bRemoveIfAllVerticesCulled, bool& bOutSuccess )` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshClipMorphPlane.h` (Private)


#### struct `UE::Mutable::Private::FVertexBoneInfo`  
`struct FVertexBoneInfo`  
_L43-47_
- L45 _public member_ `TArray<int32, TFixedAllocator<16>> BoneIndices;`
- L46 _public member_ `TArray<int32, TFixedAllocator<16>> BoneWeights;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `inline bool PointInBoundingBox(const FVector3f& Point, const FShape& SelectionShape)` (scope `UE::Mutable::Private`)
- L30 _function_ `inline bool VertexIsInMaxRadius(const FVector3f& Position, const FVector3f& Origin, float VertexSelectionBoneMaxRadius)` (scope `UE::Mutable::Private`)
- L49 _function_ `inline bool VertexIsAffectedByBone(int32 VertexIdx, const TBitArray<>& BoneIsAffected, const TArray<FVertexBoneInfo>& VertexInfo)` (scope `UE::Mutable::Private`)
- L74 _function_ `inline void MeshClipMorphPlane(FMesh* Result, const FMesh* pBase, const FVector3f& Origin, const FVector3f& Normal, float Dist, float Factor, float Radius, float Radius2, float Angle, const FShape& SelectionShape, bool bRemoveIfAllVerticesCulled, bool& bOutSuccess, FName BoneName = NAME_None, float VertexSelectionBoneMaxRadius = -1.f)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshClipWithMesh.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L19 _namespace_ `namespace GeometryUtils` (scope `UE::Mutable::Private`)
- L29 _prototype_ `extern void MeshClipMeshClassifyVertices(TBitArray<>& VertexInClipMesh, const FMesh* Base, const FMesh* ClipMesh);` (scope `UE::Mutable::Private`) — Generate a classification list for which vertex of pBase is fully contained in pClipMesh
- L31 _prototype_ `void MeshClipMeshClassifyVerticesWithAABBTree(TBitArray<>& VertexInsideClipVolume, TNotNull<const FMesh*> Mesh, UE::Geometry::TMeshAABBTree3<GeometryUtils::FMeshAdapter>& ClipVolumeTree);` (scope `UE::Mutable::Private`)
- L34 _prototype_ `extern void MeshClipWithMesh(FMesh* Result, const FMesh* Base, const FMesh* ClipMesh, bool bRemoveAllVerticesCulled, bool& bOutSuccess);` (scope `UE::Mutable::Private`)
- L37 _prototype_ `extern void MeshMaskClipMesh(FMesh* Result, const FMesh* Base, const FMesh* ClipMesh, bool& bOutSuccess);` (scope `UE::Mutable::Private`) — Generate a mask mesh with the faces of the base mesh inside the clip mesh.
- L40 _prototype_ `extern void MakeMeshMaskFromUVMask(FMesh* Result, const FMesh* Base, const FMesh* BaseForUVs, const FImage* Mask, uint8 LayoutIndex, bool& bOutSuccess);` (scope `UE::Mutable::Private`) — Generate a mask mesh with the faces of the base mesh that have all 3 vertices marked in the given mask.
- L43 _prototype_ `extern void MeshMaskDiff(FMesh* Result, const FMesh* Base, const FMesh* Fragment, bool& bOutSuccess);` (scope `UE::Mutable::Private`) — Generate a mask mesh with the faces of the base mesh matching the fragment.
- L46 _prototype_ `extern void MakeMeshMaskFromLayout(FMesh* Result, const FMesh* Base, const FMesh* BaseForUVs, const FLayout* Mask, uint8 LayoutIndex, bool& bOutSuccess);` (scope `UE::Mutable::Private`) — Generate a mask mesh with the faces of the base mesh that have all 3 vertices inside any block of the given layout.
- L49 _prototype_ `extern bool IsMeshClosed(const FMesh* Mesh);` (scope `UE::Mutable::Private`) — Return true if the mesh is closed. Usually used to validate clipping meshes.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshComputeNormals.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mutable` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L21 _function_ `inline float ComputeTangentBasisDeterminantSign(const FVector3f& N, const FVector3f& T, const FVector3f& B)` (scope `UE::Mutable::Private`)
- L30 _function_ `inline void OrthogonalizeTangentSpace( const FVector3f* NormalPtr, FVector3f* TangentPtr, FVector3f* BiNormalPtr, float TangentBasisDeterminantSign)` (scope `UE::Mutable::Private`)
- L47 _function_ `inline void ComputeMeshNormals(FMesh& DestMesh)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshDifference.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _function_ `inline void MeshDifference( FMesh* Result, const FMesh* pBase, const FMesh* pTarget, int32 numChannels, const EMeshBufferSemantic* semantics, const int32* semanticIndices, bool ignoreTexCoords, bool& bOutSuccess)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshExtractLayoutBlock.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _prototype_ `void MeshExtractLayoutBlock(TNotNull<FMesh*> Result, uint32 LayoutIndex, TArrayView<uint64> BlockIds);` (scope `UE::Mutable::Private`) — Extract all vertices that have a layout block from the passed list on the given channel in place.
- L17 _prototype_ `void MeshExtractLayoutBlock(TNotNull<FMesh*> Result, uint32 LayoutIndex);` (scope `UE::Mutable::Private`) — Extract all vertices that have a valid layout block on the given channel in place.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshGeometryOperation.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L23 _function_ `inline TSharedPtr<UE::Geometry::FDynamicMesh3> MutableToDynamicMesh(const FMesh* MutableMesh, TArray<int>& VertexMutableToDyn)` (scope `UE::Mutable::Private`)
- L81 _function_ `inline void UpdateMutableMesh(FMesh* MutableMesh, const UE::Geometry::FDynamicMesh3* DynMesh, const TArray<int>& VertexMutableToDyn)` (scope `UE::Mutable::Private`)
- L108 _function_ `inline void MeshGeometryOperation(FMesh* Result, const FMesh* MeshA, const FMesh* MeshB, float ScalarA, float ScalarB, bool& bOutSuccess)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshMorph.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _prototype_ `void MeshMorph(FMesh* Mesh, const FName& MorphName, float Factor);` (scope `UE::Mutable::Private`) — Morph Parameter Meshes. Mesh contains the deltas in morph buffer. Deltas are compressed using the engine format.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshRemove.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _prototype_ `extern void MeshRemoveMaskInline(FMesh* Mesh, const FMesh* Mask, bool bRemoveIfAllVerticesCulled);` (scope `UE::Mutable::Private`) — Remove a list of vertices and related faces from a mesh. The list of vertices is stored in a specially formatted Mask mesh. If bRemoveIfAllVerticesCulled is true, a face is remove if all its vertices have the bit set in VerticesToCull. If bRemoveIfAllVerticesCulled is false, remove a face if at least one vertex is removed.
- L27 _prototype_ `extern void MeshRemoveVerticesWithCullSet(FMesh* Result, const TBitArray<>& VerticesToCull, bool bRemoveIfAllVerticesCulled);` (scope `UE::Mutable::Private`) — Remove a set of vertices and related faces from a mesh in-place. VertexToCull is a bitset where if bit i-th is set, the vertex i-th will be removed if all faces referencing this vertex need to be removed. If bRemoveIfAllVerticesCulled is true, a face is remove if all its vertices have the bit set in VerticesToCull. If bRemoveIfAllVerticesCulled is false, remove a face if at least one vertex is removed.
- L32 _prototype_ `extern void MeshRemoveRecreateSurface(FMesh* Result, const TBitArray<>& UsedVertices, const TBitArray<>& UsedFaces);` (scope `UE::Mutable::Private`) — Recreates the Surface and Surfaces Submeshes given a set of vertices and faces remaining after mesh removal.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshReshape.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L12 _prototype_ `void MeshApplyShape(FMesh* Mesh, GeometryUtils::FMeshGeometry& TargetShape, EMeshBindShapeFlags BindFlags, bool& bOutSuccess, FLiveInstanceLogger& MessageLogger);` (scope `UE::Mutable::Private`) — Rebuild the (previously bound) mesh data for a new shape.

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshSmoothing.h` (Private)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Mutable` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L24 _function_ `inline TArray<int32> MakeUniqueVertexMap(TArrayView<const FVector3f> Vertices)` (scope `UE::Mutable::Private`)
- L58 _function_ `` (scope `UE::Mutable::Private::MakeUniqueVertexMap`)
- L72 _function_ `inline TArray<TArray<int32, TInlineAllocator<8>>> BuildVertexFaces(TArrayView<const uint32> Indices, const TArray<int32>& UniqueVertexMap)` (scope `UE::Mutable::Private`)
- L93 _function_ `FORCEINLINE uint32 GetEdgeLowVertex(uint64 Edge)` (scope `UE::Mutable::Private`)
- L98 _function_ `FORCEINLINE uint32 GetEdgeHighVertex(uint64 Edge)` (scope `UE::Mutable::Private`)
- L103 _function_ `FORCEINLINE uint64 MakeEdge(uint32 E0, uint32 E1)` (scope `UE::Mutable::Private`)
- L109 _function_ `inline TMap<uint64, UE::Geometry::FIndex2i> BuildEdgesFaces(TArrayView<const uint32> Indices, const TArray<int32>& UniqueVertexMap)` (scope `UE::Mutable::Private`)
- L116 _function_ `` (scope `UE::Mutable::Private::BuildEdgesFaces`)
- L151 _function_ `FORCEINLINE int32 FindEdgeOtherVertex(uint64 Edge, uint32 V)` (scope `UE::Mutable::Private`)
- L157 _function_ `FORCEINLINE int32 FindOppositeFace(UE::Geometry::FIndex2i EdgeFaces, int32 Face)` (scope `UE::Mutable::Private`)
- L172 _function_ `FORCEINLINE uint32 FindFaceVertexNotInEdge(uint64 Edge, const UE::Geometry::FIndex3i& F)` (scope `UE::Mutable::Private`)
- L182 _function_ `FORCEINLINE int32 FindNextFaceVertex(int32 V, const UE::Geometry::FIndex3i& F)` (scope `UE::Mutable::Private`)
- L192 _function_ `inline TTuple<TArray<int32>, TArray<int32>> BuildVertexRings( const TArrayView<const uint32> Indices, const TArray<int32>& UniqueVertexMap, const TArray<TArray<int32, TInlineAllocator<8>>>& VertexFaces, const TMap<uint64, UE::Geometry::FIndex2i>& EdgesFaces)` (scope `UE::Mutable::Private`)
- L204 _function_ `` (scope `UE::Mutable::Private::BuildVertexRings`)
- L460 _function_ `inline void RemoveLaplacianData(FMesh& Mesh)` (scope `UE::Mutable::Private`)
- L464 _function_ `` (scope `UE::Mutable::Private::RemoveLaplacianData`)
- L476 _function_ `inline void SmoothMeshLaplacian(FMesh& Mesh, bool bRemoveData, int32 Iterations = 1)` (scope `UE::Mutable::Private`)
- L480 _typedef_ `using BufferEntryType = TPair<EMeshBufferType, FMeshBufferSet>;` (scope `UE::Mutable::Private::SmoothMeshLaplacian`)
- L483 _function_ `[](const BufferEntryType& E)` (scope `UE::Mutable::Private::SmoothMeshLaplacian`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshTransform.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _function_ `inline void MeshTransform(FMesh* Result, const FMesh* pBase, const FMatrix44f& transform, bool& bOutSuccess)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshTransformWithBone.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _prototype_ `extern void MeshTransformWithBoneInline(FMesh* Mesh, const FMatrix44f& Transform, FName BoneName, const float Threshold);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpMeshTransformWithMesh.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L12 _prototype_ `extern void MeshTransformWithMesh(FMesh* Result, const FMesh* SourceMesh, const FMesh* BoundingMesh, const FMatrix44f& Transform, bool& bOutSuccess);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/OpSkeletalMeshMerge.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Mutable` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L9 _prototype_ `void SkeletalMeshMerge(FSkeletalMesh& Base, FSkeletalMesh& AddedMesh);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableRuntime/Private/MuR/SparseIndexMap.h` (Private)


#### class `UE::Mutable::Private::SparseIndexMap`  
`class SparseIndexMap`  
_L20-101_
- desc: Very basic sparse index map where the i-th element contains the mapped index. Only indices in the range [ MinIndex, MaxIndex ] can be accessed.
- L23 _public member_ `static constexpr uint32 NotFoundValue = TNumericLimits<uint32>::Max();`
- L26 _private member_ `static constexpr uint32 Log2BlockSizeBytes = 12;`
- L27 _private member_ `static constexpr uint32 Log2IndexSizeBytes = 2;`
- L32 _private member_ `static constexpr uint32 Log2BlockElems = Log2BlockSizeBytes - Log2IndexSizeBytes;`
- L34 _private member_ `const uint32 MinIndex;`
- L35 _private member_ `const uint32 MaxIndex;`
- L37 _private typedef_ `using BlockType = TStaticArray<uint32, 1 << Log2BlockElems>;`
- L39 _private member_ `TArray< TUniquePtr<BlockType> > Blocks;`
- L43 _public function_ `SparseIndexMap( const uint32 InMinIndex, const uint32 InMaxIndex ) : MinIndex( InMinIndex ) , MaxIndex( InMaxIndex )`
- L57 _public function_ `bool Insert( const uint32 KeyIndex, const uint32 ValueIndex )`
- L79 _public function_ `uint32 Find( const uint32 KeyIndex ) const`

#### class `UE::Mutable::Private::SparseIndexMapSet`  
`class SparseIndexMapSet`  
_L104-166_
- L114 _private member_ `TArray<FRange> Ranges;`
- L125 _public function_ `SparseIndexMapSet(const TArray<FRangeDesc>& InRanges)`
- L134 _public function_ `bool Insert(const uint64 KeyIndex, const uint32 ValueIndex)`
- L150 _public function_ `uint32 Find(const uint64 KeyIndex) const`

#### struct `UE::Mutable::Private::SparseIndexMapSet::FRange`  
`struct FRange`  
_L108-112_
- L110 _public member_ `uint32 Prefix;`
- L111 _public member_ `SparseIndexMap Map;`

#### struct `UE::Mutable::Private::SparseIndexMapSet::FRangeDesc`  
`struct FRangeDesc`  
_L118-123_
- L120 _public member_ `uint32 Prefix;`
- L121 _public member_ `uint32 MinIndex;`
- L122 _public member_ `uint32 MaxIndex;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/FloatAdapter.h` (Public)


#### struct `UE::Mutable::FFloatAdapter`  
`struct FFloatAdapter`  
_L21-44_
- reflection: `USTRUCT()`
- L28 _public prototype_ `FFloatAdapter() = default;`
- L30 _public prototype_ `FFloatAdapter(const FFloatAdapter& Other);`
- L32 _public prototype_ `FFloatAdapter(FFloatAdapter&& Other) = delete;`
- L34 _public prototype_ `FFloatAdapter& operator=(const FFloatAdapter& Other);`
- L36 _public prototype_ `FFloatAdapter& operator=(FFloatAdapter&& Other) = delete;`
- L38 _public prototype_ `float GetValue() const;`
- L40 _public prototype_ `void SetValue(float Value);`
- L43 _private member_ `float Value = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/MaterialAdapter.h` (Public)


#### struct `UE::Mutable::FMaterialAdapter`  
`struct FMaterialAdapter`  
_L26-56_
- reflection: `USTRUCT()`
- L32 _public prototype_ `FMaterialAdapter();`
- L34 _public prototype_ `FMaterialAdapter(const FMaterialAdapter& Other);`
- L36 _public prototype_ `FMaterialAdapter(FMaterialAdapter&& Other) = delete;`
- L38 _public prototype_ `FMaterialAdapter& operator=(const FMaterialAdapter& Other);`
- L40 _public prototype_ `FMaterialAdapter& operator=(FMaterialAdapter&& Other) = delete;`
- L42 _public prototype_ `TOptional<TValueConst<FFloatAdapter>> GetFloat(const Private::FParameterKey& ParameterKey) const;`
- L44 _public prototype_ `bool SetFloat(const Private::FParameterKey& ParameterKey, const TValueConst<FFloatAdapter>* Value);`
- L46 _public prototype_ `TOptional<TValueConst<FVectorAdapter>> GetVector(const Private::FParameterKey& ParameterKey) const;`
- L48 _public prototype_ `bool SetVector(const Private::FParameterKey& ParameterKey, const TValueConst<FVectorAdapter>* Value);`
- L50 _public prototype_ `TOptional<TValueConst<FTextureAdapter>> GetTexture(const Private::FParameterKey& ParameterKey) const;`
- L52 _public prototype_ `bool SetTexture(const Private::FParameterKey& ParameterKey, const TValueConst<FTextureAdapter>* Value);`
- L55 _private member_ `Private::TManagedPtr<Private::FMaterial> Material;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/MeshAdapter.h` (Public)


#### struct `UE::Mutable::FMeshAdapter`  
`struct FMeshAdapter`  
_L19-50_
- reflection: `USTRUCT()`
- L25 _public prototype_ `FMeshAdapter();`
- L27 _public prototype_ `FMeshAdapter(const FMeshAdapter& Other);`
- L29 _public prototype_ `FMeshAdapter(FMeshAdapter&& Other) = delete;`
- L31 _public prototype_ `FMeshAdapter& operator=(const FMeshAdapter& Other);`
- L33 _public prototype_ `FMeshAdapter& operator=(FMeshAdapter&& Other) = delete;`
- L36 _public prototype_ `int32 GetNumVertices() const;` — Mesh interface
- L38 _public prototype_ `FVector3f GetVertex(int32 Index) const;`
- L40 _public prototype_ `void SetVertex(int32 Index, const FVector3f& Vertex);`
- L42 _public prototype_ `void RemoveVertices(const TBitArray<>& Vertices);`
- L45 _public prototype_ `Private::TManagedPtr<Private::FMesh> GetPrivate();` — Internal use only. Use at your own risk. Public API not maintained.
- L46 _public prototype_ `Private::TManagedPtr<const Private::FMesh> GetPrivate() const;`
- L49 _private member_ `Private::TManagedPtr<Private::FMesh> Mesh;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/Operation.h` (Public)


#### class `UE::Mutable::FContext`  
`class FContext`  
_L23-40_
- desc: Context of the External Operation.
- L31 _public prototype_ `FValueConst GetInput(const FText& Name);` — Returns and removes the input from the Context. Once called the owner is the requester. This allows CopyOrMove to move (see CopyOrMove for details).
- L34 _public prototype_ `void SetOutput(FValueConst&& Value);` — Return the pointer to store the ouput.
- L37 _private member_ `TMap<const FString, FValueConst> Inputs;`
- L39 _private member_ `FValueConst Output;`

#### struct `UE::Mutable::FExternalOperation`  
`struct FExternalOperation`  
_L53-70_
- reflection: `USTRUCT()`
- desc: External Operation Base class. All External Operations must inherit from this class. Due to Mutable being a Pure Functional VM, all operations must not store information (no members, globals, statics...). Furthermore, due to cache, given the same inputs an operation must always produce the same output (no randomness). An operation can have UProperty members but they are considered constants (they are copied when compiling and must not be modified at runtime). UProperties marked as Visible/EditAnywhere are automatically shown in the Node Details panel.
- L57 _public prototype_ `virtual ~FExternalOperation() = default;`
- L60 _public function_ `virtual uint32 GetVersion() const` — Version of the operation. If it differs from the compiled one, it will automatically trigger a compilation.
- L63 _public function_ `virtual TArray<TPair<FText, const UScriptStruct*>> GetInputs() const` — Static. It must always return the same inputs.
- L66 _public function_ `virtual TPair<FText, const UScriptStruct*> GetOutput() const` — Static. It must always return the same output.
- L69 _public function_ `virtual void Evaluate(FContext& Context) const` — This function must be pure functional (same inputs, same output).

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/TextureAdapter.h` (Public)


#### struct `UE::Mutable::FTextureAdapter`  
`struct FTextureAdapter`  
_L22-41_
- reflection: `USTRUCT()`
- L29 _public prototype_ `FTextureAdapter();`
- L31 _public prototype_ `FTextureAdapter(const FTextureAdapter& Other);`
- L33 _public prototype_ `FTextureAdapter(FTextureAdapter&& Other) = delete;`
- L35 _public prototype_ `FTextureAdapter& operator=(const FTextureAdapter& Other);`
- L37 _public prototype_ `FTextureAdapter& operator=(FTextureAdapter&& Other) = delete;`
- L40 _private member_ `Private::TManagedPtr<Private::FImage> Image;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/Value.h` (Public)


#### class `UE::Mutable::FValue`  
`class FValue`  
_L23-77_
- L31 _public function_ `template<typename T> static FValue New()`
- L40 _public prototype_ `FValue(const FValue& Other) = delete;`
- L42 _public prototype_ `FValue& operator=(const FValue& Other) = delete;`
- L44 _public function_ `FValue(FValue&& Other)`
- L49 _public function_ `FValue& operator=(FValue&& Other)`
- L55 _public function_ `FValue(const UScriptStruct* ScriptStruct)`
- L62 _public function_ `template <typename T> T& Get()`
- L68 _public function_ `template <typename T> T* GetPtr()`
- L74 _private prototype_ `FValue() = default;`
- L76 _private member_ `Private::TManagedPtr<FInstancedStruct> Ptr;`

#### class `UE::Mutable::FValueConst`  
`class FValueConst`  
_L80-130_
- L88 _public function_ `template<typename T> static FValueConst New()`
- L97 _public prototype_ `FValueConst(const FValueConst& Other) = delete;`
- L99 _public prototype_ `FValueConst& operator=(const FValueConst& Other) = delete;`
- L101 _public function_ `FValueConst(FValueConst&& Other)`
- L106 _public function_ `FValueConst& operator=(FValueConst&& Other)`
- L112 _public prototype_ `FValueConst(FValue&& Value);`
- L115 _public function_ `template <typename T> const T& Get() const`
- L121 _public function_ `template <typename T> const T* GetPtr() const`
- L127 _private prototype_ `FValueConst() = default;`
- L129 _private member_ `Private::TManagedPtr<const FInstancedStruct> Ptr;`

#### class `UE::Mutable::TValue`  
`template<typename T> class TValue`  
_L134-187_
- L143 _public function_ `static TValue New()`
- L152 _public prototype_ `TValue(const TValue& Other) = delete;`
- L154 _public prototype_ `TValue& operator=(const TValue& Other) = delete;`
- L156 _public function_ `TValue(TValue&& Other)`
- L161 _public function_ `TValue& operator=(TValue&& Other)`
- L167 _public function_ `TValue(const UScriptStruct* ScriptStruct)`
- L173 _public function_ `T& Get()`
- L178 _public function_ `T* GetPtr()`
- L184 _private prototype_ `TValue() = default;`
- L186 _private member_ `Private::TManagedPtr<FInstancedStruct> Ptr;` — TODO GMT Extension TVariant Lazy

#### class `UE::Mutable::TValueConst`  
`template<typename T> class TValueConst`  
_L191-242_
- L199 _public function_ `static TValueConst New()`
- L208 _public prototype_ `TValueConst(const FValueConst& Other) = delete;`
- L210 _public prototype_ `TValueConst& operator=(const FValueConst& Other) = delete;`
- L212 _public function_ `TValueConst(TValueConst&& Other)`
- L217 _public function_ `TValueConst& operator=(TValueConst&& Other)`
- L223 _public function_ `TValueConst(TValue<T>&& Value)`
- L228 _public function_ `const T& Get() const`
- L233 _public function_ `const T* GetPtr() const`
- L239 _private prototype_ `TValueConst() = default;`
- L241 _private member_ `Private::TManagedPtr<const FInstancedStruct> Ptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L250 _prototype_ `FValue CopyOrMove(FValueConst&& ValueConst);` (scope `UE::Mutable`) — Copy (or move) a value to remove it's const. Instead of copy, a value will be moved if it is uniquely referenced. A value may not be unique due to: - Being being used in more than one subsequent input. - User holding additional references to it. Use MoveTemp whenever possible.
- L253 _function_ `template<typename T> TValue<T> CopyOrMove(TValueConst<T>&& ValueConst)` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableRuntime/Public/MuR/External/VectorAdapter.h` (Public)


#### struct `UE::Mutable::FVectorAdapter`  
`struct FVectorAdapter`  
_L21-44_
- reflection: `USTRUCT()`
- L28 _public prototype_ `FVectorAdapter() = default;`
- L30 _public prototype_ `FVectorAdapter(const FVectorAdapter& Other);`
- L32 _public prototype_ `FVectorAdapter(FVectorAdapter&& Other) = delete;`
- L34 _public prototype_ `FVectorAdapter& operator=(const FVectorAdapter& Other);`
- L36 _public prototype_ `FVectorAdapter& operator=(FVectorAdapter&& Other) = delete;`
- L38 _public prototype_ `FVector4f GetValue() const;`
- L40 _public prototype_ `void SetValue(const FVector4f& Value);`
- L43 _private member_ `FVector4f Value = FVector4f::Zero();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
