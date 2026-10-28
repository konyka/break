# Developer / ShaderCompilerCommon

- module root: `Source/Developer/ShaderCompilerCommon`
- headers: 25; symbols: 3507
- symbol kinds: class=11, enum=52, enumerator=2311, function=311, macro=51, member=447, namespace=42, prototype=161, struct=76, typedef=11, union=4, variable=30
- PrivateDependencyModuleNames: Core, RenderCore, ShaderPreprocessor
- PublicDependencyModuleNames: FileUtilities, HlslParser
- PublicIncludePathModuleNames: TargetPlatform

### `Source/Developer/ShaderCompilerCommon/Internal/ShaderCompilerCommonInternal.h` (Internal)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ShaderCompilerCommon` (scope `UE`)
- L20 _prototype_ `extern bool RemoveUnusedOutputs( const FShaderCompilerInput& CompilerInput, FShaderCompilerOutput& CompilerOutput, FString& InOutSourceCode, FString& InOutEntryPoint, TConstArrayView<FStringView> InUsedOutputs, TConstArrayView<FStringView> InExceptions, TConstArrayView<UE::HlslParser::FScopedDeclarations> InScopedDeclarations );` (scope `UE::ShaderCompilerCommon`)
- L30 _prototype_ `extern bool RemoveUnusedInputs( const FShaderCompilerInput& CompilerInput, FShaderCompilerOutput& CompilerOutput, FStringView InSourceCode, FStringView InEntryPointName, TConstArrayView<FString> InUsedInputs, TConstArrayView<UE::HlslParser::FScopedDeclarations> InScopedDeclarations = {} );` (scope `UE::ShaderCompilerCommon`)
- L41 _prototype_ `extern IMalloc* GetDxcMalloc();` (scope `UE::ShaderCompilerCommon`) — Get an IMalloc to overload DXC's allocator with our own in Windows
- L44 _prototype_ `extern FSpecializationConstantData ProcessSpirvSpecializationConstants( const FShaderCompilerInput& Input, CrossCompiler::FShaderConductorContext& CompilerContext, spv_reflect::ShaderModule& Reflection, const FSpirvReflectBindings& UnspecializedBindings, FShaderCompilerOutput& Output);` (scope `UE::ShaderCompilerCommon`)

### `Source/Developer/ShaderCompilerCommon/Private/ISAParser/RDNA1_ISA.inl` (Private)


#### enum `RDNA1::ESOP1Ops`  
`enum class ESOP1Ops : uint16`  
_L14-81_
- L16 _public enumerator_ `s_mov_b32 = 3`
- L17 _public enumerator_ `s_mov_b64 = 4`
- L18 _public enumerator_ `s_cmov_b32 = 5`
- L19 _public enumerator_ `s_cmov_b64 = 6`
- L20 _public enumerator_ `s_not_b32 = 7`
- L21 _public enumerator_ `s_not_b64 = 8`
- L22 _public enumerator_ `s_wqm_b32 = 9`
- L23 _public enumerator_ `s_wqm_b64 = 10`
- L24 _public enumerator_ `s_brev_b32 = 11`
- L25 _public enumerator_ `s_brev_b64 = 12`
- L26 _public enumerator_ `s_bcnt0_i32_b32 = 13`
- L27 _public enumerator_ `s_bcnt0_i32_b64 = 14`
- L28 _public enumerator_ `s_bcnt1_i32_b32 = 15`
- L29 _public enumerator_ `s_bcnt1_i32_b64 = 16`
- L30 _public enumerator_ `s_ff0_i32_b32 = 17`
- L31 _public enumerator_ `s_ff0_i32_b64 = 18`
- L32 _public enumerator_ `s_ff1_i32_b32 = 19`
- L33 _public enumerator_ `s_ff1_i32_b64 = 20`
- L34 _public enumerator_ `s_flbit_i32_b32 = 21`
- L35 _public enumerator_ `s_flbit_i32_b64 = 22`
- L36 _public enumerator_ `s_flbit_i32 = 23`
- L37 _public enumerator_ `s_flbit_i32_i64 = 24`
- L38 _public enumerator_ `s_sext_i32_i8 = 25`
- L39 _public enumerator_ `s_sext_i32_i16 = 26`
- L40 _public enumerator_ `s_bitset0_b32 = 27`
- L41 _public enumerator_ `s_bitset0_b64 = 28`
- L42 _public enumerator_ `s_bitset1_b32 = 29`
- L43 _public enumerator_ `s_bitset1_b64 = 30`
- L44 _public enumerator_ `s_getpc_b64 = 31`
- L45 _public enumerator_ `s_setpc_b64 = 32`
- L46 _public enumerator_ `s_swappc_b64 = 33`
- L47 _public enumerator_ `s_rfe_b64 = 34`
- L48 _public enumerator_ `s_and_saveexec_b64 = 36`
- L49 _public enumerator_ `s_or_saveexec_b64 = 37`
- L50 _public enumerator_ `s_xor_saveexec_b64 = 38`
- L51 _public enumerator_ `s_andn2_saveexec_b64 = 39`
- L52 _public enumerator_ `s_orn2_saveexec_b64 = 40`
- L53 _public enumerator_ `s_nand_saveexec_b64 = 41`
- L54 _public enumerator_ `s_nor_saveexec_b64 = 42`
- L55 _public enumerator_ `s_xnor_saveexec_b64 = 43`
- L56 _public enumerator_ `s_quadmask_b32 = 44`
- L57 _public enumerator_ `s_quadmask_b64 = 45`
- L58 _public enumerator_ `s_movrels_b32 = 46`
- L59 _public enumerator_ `s_movrels_b64 = 47`
- L60 _public enumerator_ `s_movreld_b32 = 48`
- L61 _public enumerator_ `s_movreld_b64 = 49`
- L62 _public enumerator_ `s_abs_i32 = 52`
- L63 _public enumerator_ `s_andn1_saveexec_b64 = 55`
- L64 _public enumerator_ `s_orn1_saveexec_b64 = 56`
- L65 _public enumerator_ `s_andn1_wrexec_b64 = 57`
- L66 _public enumerator_ `s_andn2_wrexec_b64 = 58`
- L67 _public enumerator_ `s_bitreplicate_b64_b32 = 59`
- L68 _public enumerator_ `s_and_saveexec_b32 = 60`
- L69 _public enumerator_ `s_or_saveexec_b32 = 61`
- L70 _public enumerator_ `s_xor_saveexec_b32 = 62`
- L71 _public enumerator_ `s_andn2_saveexec_b32 = 63`
- L72 _public enumerator_ `s_orn2_saveexec_b32 = 64`
- L73 _public enumerator_ `s_nand_saveexec_b32 = 65`
- L74 _public enumerator_ `s_nor_saveexec_b32 = 66`
- L75 _public enumerator_ `s_xnor_saveexec_b32 = 67`
- L76 _public enumerator_ `s_andn1_saveexec_b32 = 68`
- L77 _public enumerator_ `s_orn1_saveexec_b32 = 69`
- L78 _public enumerator_ `s_and1_wrexec_b32 = 70`
- L79 _public enumerator_ `s_andn2_wrexec_b32 = 71`
- L80 _public enumerator_ `s_movrelsd_2_b32 = 73`

#### enum `RDNA1::ESOP2Ops`  
`enum class ESOP2Ops : uint16`  
_L161-214_
- L163 _public enumerator_ `s_add_u32 = 0`
- L164 _public enumerator_ `s_sub_u32 = 1`
- L165 _public enumerator_ `s_add_i32 = 2`
- L166 _public enumerator_ `s_sub_i32 = 3`
- L167 _public enumerator_ `s_addc_u32 = 4`
- L168 _public enumerator_ `s_subb_u32 = 5`
- L169 _public enumerator_ `s_min_i32 = 6`
- L170 _public enumerator_ `s_min_u32 = 7`
- L171 _public enumerator_ `s_max_i32 = 8`
- L172 _public enumerator_ `s_max_u32 = 9`
- L173 _public enumerator_ `s_cselect_b32 = 10`
- L174 _public enumerator_ `s_cselect_b64 = 11`
- L175 _public enumerator_ `s_and_b32 = 14`
- L176 _public enumerator_ `s_and_b64 = 15`
- L177 _public enumerator_ `s_or_b32 = 16`
- L178 _public enumerator_ `s_or_b64 = 17`
- L179 _public enumerator_ `s_xor_b32 = 18`
- L180 _public enumerator_ `s_xor_b64 = 19`
- L181 _public enumerator_ `s_andn2_b32 = 20`
- L182 _public enumerator_ `s_andn2_b64 = 21`
- L183 _public enumerator_ `s_orn2_b32 = 22`
- L184 _public enumerator_ `s_orn2_b64 = 23`
- L185 _public enumerator_ `s_nand_b32 = 24`
- L186 _public enumerator_ `s_nand_b64 = 25`
- L187 _public enumerator_ `s_nor_b32 = 26`
- L188 _public enumerator_ `s_nor_b64 = 27`
- L189 _public enumerator_ `s_xnor_b32 = 28`
- L190 _public enumerator_ `s_xnor_b64 = 29`
- L191 _public enumerator_ `s_lshl_b32 = 30`
- L192 _public enumerator_ `s_lshl_b64 = 31`
- L193 _public enumerator_ `s_lshr_b32 = 32`
- L194 _public enumerator_ `s_lshr_b64 = 33`
- L195 _public enumerator_ `s_ashr_i32 = 34`
- L196 _public enumerator_ `s_ashr_i64 = 35`
- L197 _public enumerator_ `s_bfm_b32 = 36`
- L198 _public enumerator_ `s_bfm_b64 = 37`
- L199 _public enumerator_ `s_mul_i32 = 38`
- L200 _public enumerator_ `s_bfe_u32 = 39`
- L201 _public enumerator_ `s_bfe_i32 = 40`
- L202 _public enumerator_ `s_bfe_u64 = 41`
- L203 _public enumerator_ `s_bfe_i64 = 42`
- L204 _public enumerator_ `s_absdiff_i32 = 44`
- L205 _public enumerator_ `s_lshl1_add_u32 = 46`
- L206 _public enumerator_ `s_lshl2_add_u32 = 47`
- L207 _public enumerator_ `s_lshl3_add_u32 = 48`
- L208 _public enumerator_ `s_lshl4_add_u32 = 49`
- L209 _public enumerator_ `s_pack_ll_b32_b16 = 50`
- L210 _public enumerator_ `s_pack_lh_b32_b16 = 51`
- L211 _public enumerator_ `s_pack_hh_b32_b16 = 52`
- L212 _public enumerator_ `s_mul_hi_u32 = 53`
- L213 _public enumerator_ `s_mul_hi_i32 = 54`

#### enum `RDNA1::ESOPKOps`  
`enum class ESOPKOps : uint16`  
_L280-309_
- L282 _public enumerator_ `s_movk_i32 = 0`
- L283 _public enumerator_ `s_version = 1`
- L284 _public enumerator_ `s_cmovk_i32 = 2`
- L285 _public enumerator_ `s_cmpk_eq_i32 = 3`
- L286 _public enumerator_ `s_cmpk_lg_i32 = 4`
- L287 _public enumerator_ `s_cmpk_gt_i32 = 5`
- L288 _public enumerator_ `s_cmpk_ge_i32 = 6`
- L289 _public enumerator_ `s_cmpk_lt_i32 = 7`
- L290 _public enumerator_ `s_cmpk_le_i32 = 8`
- L291 _public enumerator_ `s_cmpk_eq_u32 = 9`
- L292 _public enumerator_ `s_cmpk_lg_u32 = 10`
- L293 _public enumerator_ `s_cmpk_gt_u32 = 11`
- L294 _public enumerator_ `s_cmpk_ge_u32 = 12`
- L295 _public enumerator_ `s_cmpk_lt_u32 = 13`
- L296 _public enumerator_ `s_cmpk_le_u32 = 14`
- L297 _public enumerator_ `s_addk_i32 = 15`
- L298 _public enumerator_ `s_mulk_i32 = 16`
- L299 _public enumerator_ `s_getreg_b32 = 18`
- L300 _public enumerator_ `s_setreg_b32 = 19`
- L301 _public enumerator_ `s_setreg_imm32_b32 = 21`
- L302 _public enumerator_ `s_call_b64 = 22`
- L303 _public enumerator_ `s_waitcnt_vscnt = 23`
- L304 _public enumerator_ `s_waitcnt_vmcnt = 24`
- L305 _public enumerator_ `s_waitcnt_expcnt = 25`
- L306 _public enumerator_ `s_waitcnt_lgkmcnt = 26`
- L307 _public enumerator_ `s_subvector_loop_begin = 27`
- L308 _public enumerator_ `s_subvector_loop_end = 28`

#### enum `RDNA1::ESOPPOps`  
`enum class ESOPPOps : uint16`  
_L351-389_
- L353 _public enumerator_ `s_nop = 0`
- L354 _public enumerator_ `s_endpgm = 1`
- L355 _public enumerator_ `s_branch = 2`
- L356 _public enumerator_ `s_wakeup = 3`
- L357 _public enumerator_ `s_cbranch_scc0 = 4`
- L358 _public enumerator_ `s_cbranch_scc1 = 5`
- L359 _public enumerator_ `s_cbranch_vccz = 6`
- L360 _public enumerator_ `s_cbranch_vccnz = 7`
- L361 _public enumerator_ `s_cbranch_execz = 8`
- L362 _public enumerator_ `s_cbranch_execnz = 9`
- L363 _public enumerator_ `s_barrier = 10`
- L364 _public enumerator_ `s_setkill = 11`
- L365 _public enumerator_ `s_waitcnt = 12`
- L366 _public enumerator_ `s_sethalt = 13`
- L367 _public enumerator_ `s_sleep = 14`
- L368 _public enumerator_ `s_setprio = 15`
- L369 _public enumerator_ `s_sendmsg = 16`
- L370 _public enumerator_ `s_sendmsghalt = 17`
- L371 _public enumerator_ `s_trap = 18`
- L372 _public enumerator_ `s_icache_inv = 19`
- L373 _public enumerator_ `s_incperflevel = 20`
- L374 _public enumerator_ `s_decperflevel = 21`
- L375 _public enumerator_ `s_ttracedata = 22`
- L376 _public enumerator_ `s_cbranch_cdbgsys = 23`
- L377 _public enumerator_ `s_cbranch_cdbguser = 24`
- L378 _public enumerator_ `s_cbranch_cdbgsys_or_user = 25`
- L379 _public enumerator_ `s_cbranch_cdbgsys_and_user = 26`
- L380 _public enumerator_ `s_endpgm_saved = 27`
- L381 _public enumerator_ `s_endpgm_ordered_ps_done = 30`
- L382 _public enumerator_ `s_code_end = 31`
- L383 _public enumerator_ `s_inst_prefetch = 32`
- L384 _public enumerator_ `s_clause = 33`
- L385 _public enumerator_ `s_waitcnt_depctr = 35`
- L386 _public enumerator_ `s_round_mode = 36`
- L387 _public enumerator_ `s_denorm_mode = 37`
- L388 _public enumerator_ `s_ttracedata_imm = 40`

#### enum `RDNA1::ESMEMOps`  
`enum class ESMEMOps : uint16`  
_L440-458_
- L442 _public enumerator_ `s_load_dword = 0`
- L443 _public enumerator_ `s_load_dwordx2 = 1`
- L444 _public enumerator_ `s_load_dwordx4 = 2`
- L445 _public enumerator_ `s_load_dwordx8 = 3`
- L446 _public enumerator_ `s_load_dwordx16 = 4`
- L447 _public enumerator_ `s_buffer_load_dword = 8`
- L448 _public enumerator_ `s_buffer_load_dwordx2 = 9`
- L449 _public enumerator_ `s_buffer_load_dwordx4 = 10`
- L450 _public enumerator_ `s_buffer_load_dwordx8 = 11`
- L451 _public enumerator_ `s_buffer_load_dwordx16 = 12`
- L452 _public enumerator_ `s_gl1_inv = 31`
- L453 _public enumerator_ `s_dcache_inv = 32`
- L454 _public enumerator_ `s_memtime = 36`
- L455 _public enumerator_ `s_memrealtime = 37`
- L456 _public enumerator_ `s_atc_probe = 38`
- L457 _public enumerator_ `s_atc_probe_buffer = 39`

#### enum `RDNA1::ESOPCOps`  
`enum class ESOPCOps : uint16`  
_L489-509_
- L491 _public enumerator_ `s_cmp_eq_i32 = 0`
- L492 _public enumerator_ `s_cmp_lg_i32 = 1`
- L493 _public enumerator_ `s_cmp_gt_i32 = 2`
- L494 _public enumerator_ `s_cmp_ge_i32 = 3`
- L495 _public enumerator_ `s_cmp_lt_i32 = 4`
- L496 _public enumerator_ `s_cmp_le_i32 = 5`
- L497 _public enumerator_ `s_cmp_eq_u32 = 6`
- L498 _public enumerator_ `s_cmp_lg_u32 = 7`
- L499 _public enumerator_ `s_cmp_gt_u32 = 8`
- L500 _public enumerator_ `s_cmp_ge_u32 = 9`
- L501 _public enumerator_ `s_cmp_lt_u32 = 10`
- L502 _public enumerator_ `s_cmp_le_u32 = 11`
- L503 _public enumerator_ `s_bitcmp0_b32 = 12`
- L504 _public enumerator_ `s_bitcmp1_b32 = 13`
- L505 _public enumerator_ `s_bitcmp0_b64 = 14`
- L506 _public enumerator_ `s_bitcmp1_b64 = 15`
- L507 _public enumerator_ `s_cmp_eq_u64 = 18`
- L508 _public enumerator_ `s_cmp_lg_u64 = 19`

#### enum `RDNA1::EVOP1Ops`  
`enum class EVOP1Ops : uint16`  
_L542-625_
- L544 _public enumerator_ `v_nop = 0`
- L545 _public enumerator_ `v_mov_b32 = 1`
- L546 _public enumerator_ `v_readfirstlane_b32 = 2`
- L547 _public enumerator_ `v_cvt_i32_f64 = 3`
- L548 _public enumerator_ `v_cvt_f64_i32 = 4`
- L549 _public enumerator_ `v_cvt_f32_i32 = 5`
- L550 _public enumerator_ `v_cvt_f32_u32 = 6`
- L551 _public enumerator_ `v_cvt_u32_f32 = 7`
- L552 _public enumerator_ `v_cvt_i32_f32 = 8`
- L553 _public enumerator_ `v_cvt_f16_f32 = 10`
- L554 _public enumerator_ `v_cvt_f32_f16 = 11`
- L555 _public enumerator_ `v_cvt_rpi_i32_f32 = 12`
- L556 _public enumerator_ `v_cvt_flr_i32_f32 = 13`
- L557 _public enumerator_ `v_cvt_off_f32_i4 = 14`
- L558 _public enumerator_ `v_cvt_f32_f64 = 15`
- L559 _public enumerator_ `v_cvt_f64_f32 = 16`
- L560 _public enumerator_ `v_cvt_f32_ubyte0 = 17`
- L561 _public enumerator_ `v_cvt_f32_ubyte1 = 18`
- L562 _public enumerator_ `v_cvt_f32_ubyte2 = 19`
- L563 _public enumerator_ `v_cvt_f32_ubyte3 = 20`
- L564 _public enumerator_ `v_cvt_u32_f64 = 21`
- L565 _public enumerator_ `v_cvt_f64_u32 = 22`
- L566 _public enumerator_ `v_trunc_f64 = 23`
- L567 _public enumerator_ `v_ceil_f64 = 24`
- L568 _public enumerator_ `v_rndne_f64 = 25`
- L569 _public enumerator_ `v_floor_f64 = 26`
- L570 _public enumerator_ `v_pipeflush = 27`
- L571 _public enumerator_ `v_fract_f32 = 32`
- L572 _public enumerator_ `v_trunc_f32 = 33`
- L573 _public enumerator_ `v_ceil_f32 = 34`
- L574 _public enumerator_ `v_rndne_f32 = 35`
- L575 _public enumerator_ `v_floor_f32 = 36`
- L576 _public enumerator_ `v_exp_f32 = 37`
- L577 _public enumerator_ `v_log_f32 = 39`
- L578 _public enumerator_ `v_rcp_f32 = 42`
- L579 _public enumerator_ `v_rcp_iflag_f32 = 43`
- L580 _public enumerator_ `v_rsq_f32 = 46`
- L581 _public enumerator_ `v_rcp_f64 = 47`
- L582 _public enumerator_ `v_rsq_f64 = 49`
- L583 _public enumerator_ `v_sqrt_f32 = 51`
- L584 _public enumerator_ `v_sqrt_f64 = 52`
- L585 _public enumerator_ `v_sin_f32 = 53`
- L586 _public enumerator_ `v_cos_f32 = 54`
- L587 _public enumerator_ `v_not_b32 = 55`
- L588 _public enumerator_ `v_bfrev_b32 = 56`
- L589 _public enumerator_ `v_ffbh_u32 = 57`
- L590 _public enumerator_ `v_ffbl_b32 = 58`
- L591 _public enumerator_ `v_ffbh_i32 = 59`
- L592 _public enumerator_ `v_frexp_exp_i32_f64 = 60`
- L593 _public enumerator_ `v_frexp_mant_f64 = 61`
- L594 _public enumerator_ `v_fract_f64 = 62`
- L595 _public enumerator_ `v_frexp_exp_i32_f32 = 63`
- L596 _public enumerator_ `v_frexp_mant_f32 = 64`
- L597 _public enumerator_ `v_clrexcp = 65`
- L598 _public enumerator_ `v_movreld_b32 = 66`
- L599 _public enumerator_ `v_movrels_b32 = 67`
- L600 _public enumerator_ `v_movrelsd_b32 = 68`
- L601 _public enumerator_ `v_movrelsd_2_b32 = 72`
- L602 _public enumerator_ `v_cvt_f16_u16 = 80`
- L603 _public enumerator_ `v_cvt_f16_i16 = 81`
- L604 _public enumerator_ `v_cvt_u16_f16 = 82`
- L605 _public enumerator_ `v_cvt_i16_f16 = 83`
- L606 _public enumerator_ `v_rcp_f16 = 84`
- L607 _public enumerator_ `v_sqrt_f16 = 85`
- L608 _public enumerator_ `v_rsq_f16 = 86`
- L609 _public enumerator_ `v_log_f16 = 87`
- L610 _public enumerator_ `v_exp_f16 = 88`
- L611 _public enumerator_ `v_frexp_mant_f16 = 89`
- L612 _public enumerator_ `v_frexp_exp_i16_f16 = 90`
- L613 _public enumerator_ `v_floor_f16 = 91`
- L614 _public enumerator_ `v_ceil_f16 = 92`
- L615 _public enumerator_ `v_trunc_f16 = 93`
- L616 _public enumerator_ `v_rndne_f16 = 94`
- L617 _public enumerator_ `v_fract_f16 = 95`
- L618 _public enumerator_ `v_sin_f16 = 96`
- L619 _public enumerator_ `v_cos_f16 = 97`
- L620 _public enumerator_ `v_sat_pk_u8_i16 = 98`
- L621 _public enumerator_ `v_cvt_norm_i16_f16 = 99`
- L622 _public enumerator_ `v_cvt_norm_u16_f16 = 100`
- L623 _public enumerator_ `v_swap_b32 = 101`
- L624 _public enumerator_ `v_swapref_b32 = 104`

#### enum `RDNA1::EVOP3POps`  
`enum class EVOP3POps : uint16`  
_L721-745_
- L723 _public enumerator_ `v_pk_mad_i16 = 0`
- L724 _public enumerator_ `v_pk_mul_lo_u16 = 1`
- L725 _public enumerator_ `v_pk_add_i16 = 2`
- L726 _public enumerator_ `v_pk_sub_i16 = 3`
- L727 _public enumerator_ `v_pk_lshlrev_b16 = 4`
- L728 _public enumerator_ `v_pk_lshrrev_b16 = 5`
- L729 _public enumerator_ `v_pk_ashrrev_i16 = 6`
- L730 _public enumerator_ `v_pk_max_i16 = 7`
- L731 _public enumerator_ `v_pk_min_i16 = 8`
- L732 _public enumerator_ `v_pk_mad_u16 = 9`
- L733 _public enumerator_ `v_pk_add_u16 = 10`
- L734 _public enumerator_ `v_pk_sub_u16 = 11`
- L735 _public enumerator_ `v_pk_max_u16 = 12`
- L736 _public enumerator_ `v_pk_min_u16 = 13`
- L737 _public enumerator_ `v_pk_fma_f16 = 14`
- L738 _public enumerator_ `v_pk_add_f16 = 15`
- L739 _public enumerator_ `v_pk_mul_f16 = 16`
- L740 _public enumerator_ `v_pk_min_f16 = 17`
- L741 _public enumerator_ `v_pk_max_f16 = 18`
- L742 _public enumerator_ `v_fma_mix_f32 = 32`
- L743 _public enumerator_ `v_fma_mixlo_f16 = 33`
- L744 _public enumerator_ `v_fma_mixhi_f16 = 34`

#### enum `RDNA1::EVOP2Ops`  
`enum class EVOP2Ops : uint16`  
_L782-832_
- L784 _public enumerator_ `v_cndmask_b32 = 1`
- L785 _public enumerator_ `v_add_f32 = 3`
- L786 _public enumerator_ `v_sub_f32 = 4`
- L787 _public enumerator_ `v_subrev_f32 = 5`
- L788 _public enumerator_ `v_fmac_legacy_f32 = 6`
- L789 _public enumerator_ `v_mul_legacy_f32 = 7`
- L790 _public enumerator_ `v_mul_f32 = 8`
- L791 _public enumerator_ `v_mul_i32_i24 = 9`
- L792 _public enumerator_ `v_mul_hi_i32_i24 = 10`
- L793 _public enumerator_ `v_mul_u32_u24 = 11`
- L794 _public enumerator_ `v_mul_hi_u32_u24 = 12`
- L795 _public enumerator_ `v_min_f32 = 15`
- L796 _public enumerator_ `v_max_f32 = 16`
- L797 _public enumerator_ `v_min_i32 = 17`
- L798 _public enumerator_ `v_max_i32 = 18`
- L799 _public enumerator_ `v_min_u32 = 19`
- L800 _public enumerator_ `v_max_u32 = 20`
- L801 _public enumerator_ `v_lshrrev_b32 = 22`
- L802 _public enumerator_ `v_ashrrev_i32 = 24`
- L803 _public enumerator_ `v_lshlrev_b32 = 26`
- L804 _public enumerator_ `v_and_b32 = 27`
- L805 _public enumerator_ `v_or_b32 = 28`
- L806 _public enumerator_ `v_xor_b32 = 29`
- L807 _public enumerator_ `v_xnor_b32 = 30`
- L808 _public enumerator_ `v_mac_f32 = 31`
- L809 _public enumerator_ `v_madmk_f32 = 32`
- L810 _public enumerator_ `v_madak_f32 = 33`
- L811 _public enumerator_ `v_add_nc_u32 = 37`
- L812 _public enumerator_ `v_sub_nc_u32 = 38`
- L813 _public enumerator_ `v_subrev_nc_u32 = 39`
- L814 _public enumerator_ `v_add_co_ci_u32 = 40`
- L815 _public enumerator_ `v_sub_co_ci_u32 = 41`
- L816 _public enumerator_ `v_subrev_co_ci_u32 = 42`
- L817 _public enumerator_ `v_fmac_f32 = 43`
- L818 _public enumerator_ `v_fmamk_f32 = 44`
- L819 _public enumerator_ `v_fmaak_f32 = 45`
- L820 _public enumerator_ `v_cvt_pkrtz_f16_f32 = 47`
- L821 _public enumerator_ `v_add_f16 = 50`
- L822 _public enumerator_ `v_sub_f16 = 51`
- L823 _public enumerator_ `v_subrev_f16 = 52`
- L824 _public enumerator_ `v_mul_f16 = 53`
- L825 _public enumerator_ `v_fmac_f16 = 54`
- L826 _public enumerator_ `v_fmamk_f16 = 55`
- L827 _public enumerator_ `v_fmaak_f16 = 56`
- L828 _public enumerator_ `v_max_f16 = 57`
- L829 _public enumerator_ `v_min_f16 = 58`
- L830 _public enumerator_ `v_ldexp_f16 = 59`
- L831 _public enumerator_ `v_pk_fmac_f16 = 60`

#### enum `RDNA1::EVOPCOps`  
`enum class EVOPCOps : uint16`  
_L895-1087_
- L897 _public enumerator_ `v_cmp_f_f32 = 0`
- L898 _public enumerator_ `v_cmp_lt_f32 = 1`
- L899 _public enumerator_ `v_cmp_eq_f32 = 2`
- L900 _public enumerator_ `v_cmp_le_f32 = 3`
- L901 _public enumerator_ `v_cmp_gt_f32 = 4`
- L902 _public enumerator_ `v_cmp_lg_f32 = 5`
- L903 _public enumerator_ `v_cmp_ge_f32 = 6`
- L904 _public enumerator_ `v_cmp_o_f32 = 7`
- L905 _public enumerator_ `v_cmp_u_f32 = 8`
- L906 _public enumerator_ `v_cmp_nge_f32 = 9`
- L907 _public enumerator_ `v_cmp_nlg_f32 = 10`
- L908 _public enumerator_ `v_cmp_ngt_f32 = 11`
- L909 _public enumerator_ `v_cmp_nle_f32 = 12`
- L910 _public enumerator_ `v_cmp_neq_f32 = 13`
- L911 _public enumerator_ `v_cmp_nlt_f32 = 14`
- L912 _public enumerator_ `v_cmp_tru_f32 = 15`
- L913 _public enumerator_ `v_cmpx_f_f32 = 16`
- L914 _public enumerator_ `v_cmpx_lt_f32 = 17`
- L915 _public enumerator_ `v_cmpx_eq_f32 = 18`
- L916 _public enumerator_ `v_cmpx_le_f32 = 19`
- L917 _public enumerator_ `v_cmpx_gt_f32 = 20`
- L918 _public enumerator_ `v_cmpx_lg_f32 = 21`
- L919 _public enumerator_ `v_cmpx_ge_f32 = 22`
- L920 _public enumerator_ `v_cmpx_o_f32 = 23`
- L921 _public enumerator_ `v_cmpx_u_f32 = 24`
- L922 _public enumerator_ `v_cmpx_nge_f32 = 25`
- L923 _public enumerator_ `v_cmpx_nlg_f32 = 26`
- L924 _public enumerator_ `v_cmpx_ngt_f32 = 27`
- L925 _public enumerator_ `v_cmpx_nle_f32 = 28`
- L926 _public enumerator_ `v_cmpx_neq_f32 = 29`
- L927 _public enumerator_ `v_cmpx_nlt_f32 = 30`
- L928 _public enumerator_ `v_cmpx_tru_f32 = 31`
- L929 _public enumerator_ `v_cmp_f_f64 = 32`
- L930 _public enumerator_ `v_cmp_lt_f64 = 33`
- L931 _public enumerator_ `v_cmp_eq_f64 = 34`
- L932 _public enumerator_ `v_cmp_le_f64 = 35`
- L933 _public enumerator_ `v_cmp_gt_f64 = 36`
- L934 _public enumerator_ `v_cmp_lg_f64 = 37`
- L935 _public enumerator_ `v_cmp_ge_f64 = 38`
- L936 _public enumerator_ `v_cmp_o_f64 = 39`
- L937 _public enumerator_ `v_cmp_u_f64 = 40`
- L938 _public enumerator_ `v_cmp_nge_f64 = 41`
- L939 _public enumerator_ `v_cmp_nlg_f64 = 42`
- L940 _public enumerator_ `v_cmp_ngt_f64 = 43`
- L941 _public enumerator_ `v_cmp_nle_f64 = 44`
- L942 _public enumerator_ `v_cmp_neq_f64 = 45`
- L943 _public enumerator_ `v_cmp_nlt_f64 = 46`
- L944 _public enumerator_ `v_cmp_tru_f64 = 47`
- L945 _public enumerator_ `v_cmpx_f_f64 = 48`
- L946 _public enumerator_ `v_cmpx_lt_f64 = 49`
- L947 _public enumerator_ `v_cmpx_eq_f64 = 50`
- L948 _public enumerator_ `v_cmpx_le_f64 = 51`
- L949 _public enumerator_ `v_cmpx_gt_f64 = 52`
- L950 _public enumerator_ `v_cmpx_lg_f64 = 53`
- L951 _public enumerator_ `v_cmpx_ge_f64 = 54`
- L952 _public enumerator_ `v_cmpx_o_f64 = 55`
- L953 _public enumerator_ `v_cmpx_u_f64 = 56`
- L954 _public enumerator_ `v_cmpx_nge_f64 = 57`
- L955 _public enumerator_ `v_cmpx_nlg_f64 = 58`
- L956 _public enumerator_ `v_cmpx_ngt_f64 = 59`
- L957 _public enumerator_ `v_cmpx_nle_f64 = 60`
- L958 _public enumerator_ `v_cmpx_neq_f64 = 61`
- L959 _public enumerator_ `v_cmpx_nlt_f64 = 62`
- L960 _public enumerator_ `v_cmpx_tru_f64 = 63`
- L961 _public enumerator_ `v_cmp_f_i32 = 128`
- L962 _public enumerator_ `v_cmp_lt_i32 = 129`
- L963 _public enumerator_ `v_cmp_eq_i32 = 130`
- L964 _public enumerator_ `v_cmp_le_i32 = 131`
- L965 _public enumerator_ `v_cmp_gt_i32 = 132`
- L966 _public enumerator_ `v_cmp_ne_i32 = 133`
- L967 _public enumerator_ `v_cmp_ge_i32 = 134`
- L968 _public enumerator_ `v_cmp_t_i32 = 135`
- L969 _public enumerator_ `v_cmp_class_f32 = 136`
- L970 _public enumerator_ `v_cmp_lt_i16 = 137`
- L971 _public enumerator_ `v_cmp_eq_i16 = 138`
- L972 _public enumerator_ `v_cmp_le_i16 = 139`
- L973 _public enumerator_ `v_cmp_gt_i16 = 140`
- L974 _public enumerator_ `v_cmp_ne_i16 = 141`
- L975 _public enumerator_ `v_cmp_ge_i16 = 142`
- L976 _public enumerator_ `v_cmp_class_f16 = 143`
- L977 _public enumerator_ `v_cmpx_f_i32 = 144`
- L978 _public enumerator_ `v_cmpx_lt_i32 = 145`
- L979 _public enumerator_ `v_cmpx_eq_i32 = 146`
- L980 _public enumerator_ `v_cmpx_le_i32 = 147`
- L981 _public enumerator_ `v_cmpx_gt_i32 = 148`
- L982 _public enumerator_ `v_cmpx_ne_i32 = 149`
- L983 _public enumerator_ `v_cmpx_ge_i32 = 150`
- L984 _public enumerator_ `v_cmpx_t_i32 = 151`
- L985 _public enumerator_ `v_cmpx_class_f32 = 152`
- L986 _public enumerator_ `v_cmpx_lt_i16 = 153`
- L987 _public enumerator_ `v_cmpx_eq_i16 = 154`
- L988 _public enumerator_ `v_cmpx_le_i16 = 155`
- L989 _public enumerator_ `v_cmpx_gt_i16 = 156`
- L990 _public enumerator_ `v_cmpx_ne_i16 = 157`
- L991 _public enumerator_ `v_cmpx_ge_i16 = 158`
- L992 _public enumerator_ `v_cmpx_class_f16 = 159`
- L993 _public enumerator_ `v_cmp_f_i64 = 160`
- L994 _public enumerator_ `v_cmp_lt_i64 = 161`
- L995 _public enumerator_ `v_cmp_eq_i64 = 162`
- L996 _public enumerator_ `v_cmp_le_i64 = 163`
- L997 _public enumerator_ `v_cmp_gt_i64 = 164`
- L998 _public enumerator_ `v_cmp_ne_i64 = 165`
- L999 _public enumerator_ `v_cmp_ge_i64 = 166`
- L1000 _public enumerator_ `v_cmp_t_i64 = 167`
- L1001 _public enumerator_ `v_cmp_class_f64 = 168`
- L1002 _public enumerator_ `v_cmp_lt_u16 = 169`
- L1003 _public enumerator_ `v_cmp_eq_u16 = 170`
- L1004 _public enumerator_ `v_cmp_le_u16 = 171`
- L1005 _public enumerator_ `v_cmp_gt_u16 = 172`
- L1006 _public enumerator_ `v_cmp_ne_u16 = 173`
- L1007 _public enumerator_ `v_cmp_ge_u16 = 174`
- L1008 _public enumerator_ `v_cmpx_f_i64 = 176`
- L1009 _public enumerator_ `v_cmpx_lt_i64 = 177`
- L1010 _public enumerator_ `v_cmpx_eq_i64 = 178`
- L1011 _public enumerator_ `v_cmpx_le_i64 = 179`
- L1012 _public enumerator_ `v_cmpx_gt_i64 = 180`
- L1013 _public enumerator_ `v_cmpx_ne_i64 = 181`
- L1014 _public enumerator_ `v_cmpx_ge_i64 = 182`
- L1015 _public enumerator_ `v_cmpx_t_i64 = 183`
- L1016 _public enumerator_ `v_cmpx_class_f64 = 184`
- L1017 _public enumerator_ `v_cmpx_lt_u16 = 185`
- L1018 _public enumerator_ `v_cmpx_eq_u16 = 186`
- L1019 _public enumerator_ `v_cmpx_le_u16 = 187`
- L1020 _public enumerator_ `v_cmpx_gt_u16 = 188`
- L1021 _public enumerator_ `v_cmpx_ne_u16 = 189`
- L1022 _public enumerator_ `v_cmpx_ge_u16 = 190`
- L1023 _public enumerator_ `v_cmp_f_u32 = 192`
- L1024 _public enumerator_ `v_cmp_lt_u32 = 193`
- L1025 _public enumerator_ `v_cmp_eq_u32 = 194`
- L1026 _public enumerator_ `v_cmp_le_u32 = 195`
- L1027 _public enumerator_ `v_cmp_gt_u32 = 196`
- L1028 _public enumerator_ `v_cmp_ne_u32 = 197`
- L1029 _public enumerator_ `v_cmp_ge_u32 = 198`
- L1030 _public enumerator_ `v_cmp_t_u32 = 199`
- L1031 _public enumerator_ `v_cmp_f_f16 = 200`
- L1032 _public enumerator_ `v_cmp_lt_f16 = 201`
- L1033 _public enumerator_ `v_cmp_eq_f16 = 202`
- L1034 _public enumerator_ `v_cmp_le_f16 = 203`
- L1035 _public enumerator_ `v_cmp_gt_f16 = 204`
- L1036 _public enumerator_ `v_cmp_lg_f16 = 205`
- L1037 _public enumerator_ `v_cmp_ge_f16 = 206`
- L1038 _public enumerator_ `v_cmp_o_f16 = 207`
- L1039 _public enumerator_ `v_cmpx_f_u32 = 208`
- L1040 _public enumerator_ `v_cmpx_lt_u32 = 209`
- L1041 _public enumerator_ `v_cmpx_eq_u32 = 210`
- L1042 _public enumerator_ `v_cmpx_le_u32 = 211`
- L1043 _public enumerator_ `v_cmpx_gt_u32 = 212`
- L1044 _public enumerator_ `v_cmpx_ne_u32 = 213`
- L1045 _public enumerator_ `v_cmpx_ge_u32 = 214`
- L1046 _public enumerator_ `v_cmpx_t_u32 = 215`
- L1047 _public enumerator_ `v_cmpx_f_f16 = 216`
- L1048 _public enumerator_ `v_cmpx_lt_f16 = 217`
- L1049 _public enumerator_ `v_cmpx_eq_f16 = 218`
- L1050 _public enumerator_ `v_cmpx_le_f16 = 219`
- L1051 _public enumerator_ `v_cmpx_gt_f16 = 220`
- L1052 _public enumerator_ `v_cmpx_lg_f16 = 221`
- L1053 _public enumerator_ `v_cmpx_ge_f16 = 222`
- L1054 _public enumerator_ `v_cmpx_o_f16 = 223`
- L1055 _public enumerator_ `v_cmp_f_u64 = 224`
- L1056 _public enumerator_ `v_cmp_lt_u64 = 225`
- L1057 _public enumerator_ `v_cmp_eq_u64 = 226`
- L1058 _public enumerator_ `v_cmp_le_u64 = 227`
- L1059 _public enumerator_ `v_cmp_gt_u64 = 228`
- L1060 _public enumerator_ `v_cmp_ne_u64 = 229`
- L1061 _public enumerator_ `v_cmp_ge_u64 = 230`
- L1062 _public enumerator_ `v_cmp_t_u64 = 231`
- L1063 _public enumerator_ `v_cmp_u_f16 = 232`
- L1064 _public enumerator_ `v_cmp_nge_f16 = 233`
- L1065 _public enumerator_ `v_cmp_nlg_f16 = 234`
- L1066 _public enumerator_ `v_cmp_ngt_f16 = 235`
- L1067 _public enumerator_ `v_cmp_nle_f16 = 236`
- L1068 _public enumerator_ `v_cmp_neq_f16 = 237`
- L1069 _public enumerator_ `v_cmp_nlt_f16 = 238`
- L1070 _public enumerator_ `v_cmp_tru_f16 = 239`
- L1071 _public enumerator_ `v_cmpx_f_u64 = 240`
- L1072 _public enumerator_ `v_cmpx_lt_u64 = 241`
- L1073 _public enumerator_ `v_cmpx_eq_u64 = 242`
- L1074 _public enumerator_ `v_cmpx_le_u64 = 243`
- L1075 _public enumerator_ `v_cmpx_gt_u64 = 244`
- L1076 _public enumerator_ `v_cmpx_ne_u64 = 245`
- L1077 _public enumerator_ `v_cmpx_ge_u64 = 246`
- L1078 _public enumerator_ `v_cmpx_t_u64 = 247`
- L1079 _public enumerator_ `v_cmpx_u_f16 = 248`
- L1080 _public enumerator_ `v_cmpx_nge_f16 = 249`
- L1081 _public enumerator_ `v_cmpx_nlg_f16 = 250`
- L1082 _public enumerator_ `v_cmpx_ngt_f16 = 251`
- L1083 _public enumerator_ `v_cmpx_nle_f16 = 252`
- L1084 _public enumerator_ `v_cmpx_neq_f16 = 253`
- L1085 _public enumerator_ `v_cmpx_nlt_f16 = 254`
- L1086 _public enumerator_ `v_cmpx_tru_f16 = 255`

#### enum `RDNA1::EVOP3ABOps`  
`enum class EVOP3ABOps : uint16`  
_L1292-1409_
- L1294 _public enumerator_ `v_fma_legacy_f32 = 320`
- L1295 _public enumerator_ `v_mad_f32 = 321`
- L1296 _public enumerator_ `v_mad_i32_i24 = 322`
- L1297 _public enumerator_ `v_mad_u32_u24 = 323`
- L1298 _public enumerator_ `v_cubeid_f32 = 324`
- L1299 _public enumerator_ `v_cubesc_f32 = 325`
- L1300 _public enumerator_ `v_cubetc_f32 = 326`
- L1301 _public enumerator_ `v_cubema_f32 = 327`
- L1302 _public enumerator_ `v_bfe_u32 = 328`
- L1303 _public enumerator_ `v_bfe_i32 = 329`
- L1304 _public enumerator_ `v_bfi_b32 = 330`
- L1305 _public enumerator_ `v_fma_f32 = 331`
- L1306 _public enumerator_ `v_fma_f64 = 332`
- L1307 _public enumerator_ `v_lerp_u8 = 333`
- L1308 _public enumerator_ `v_alignbit_b32 = 334`
- L1309 _public enumerator_ `v_alignbyte_b32 = 335`
- L1310 _public enumerator_ `v_mullit_f32 = 336`
- L1311 _public enumerator_ `v_min3_f32 = 337`
- L1312 _public enumerator_ `v_min3_i32 = 338`
- L1313 _public enumerator_ `v_min3_u32 = 339`
- L1314 _public enumerator_ `v_max3_f32 = 340`
- L1315 _public enumerator_ `v_max3_i32 = 341`
- L1316 _public enumerator_ `v_max3_u32 = 342`
- L1317 _public enumerator_ `v_med3_f32 = 343`
- L1318 _public enumerator_ `v_med3_i32 = 344`
- L1319 _public enumerator_ `v_med3_u32 = 345`
- L1320 _public enumerator_ `v_sad_u8 = 346`
- L1321 _public enumerator_ `v_sad_hi_u8 = 347`
- L1322 _public enumerator_ `v_sad_u16 = 348`
- L1323 _public enumerator_ `v_sad_u32 = 349`
- L1324 _public enumerator_ `v_cvt_pk_u8_f32 = 350`
- L1325 _public enumerator_ `v_div_fixup_f32 = 351`
- L1326 _public enumerator_ `v_div_fixup_f64 = 352`
- L1327 _public enumerator_ `v_add_f64 = 356`
- L1328 _public enumerator_ `v_mul_f64 = 357`
- L1329 _public enumerator_ `v_min_f64 = 358`
- L1330 _public enumerator_ `v_max_f64 = 359`
- L1331 _public enumerator_ `v_ldexp_f64 = 360`
- L1332 _public enumerator_ `v_mul_lo_u32 = 361`
- L1333 _public enumerator_ `v_mul_hi_u32 = 362`
- L1334 _public enumerator_ `v_mul_hi_i32 = 364`
- L1335 _public enumerator_ `v_div_scale_f32 = 365`
- L1336 _public enumerator_ `v_div_scale_f64 = 366`
- L1337 _public enumerator_ `v_div_fmas_f32 = 367`
- L1338 _public enumerator_ `v_div_fmas_f64 = 368`
- L1339 _public enumerator_ `v_msad_u8 = 369`
- L1340 _public enumerator_ `v_qsad_pk_u16_u8 = 370`
- L1341 _public enumerator_ `v_mqsad_pk_u16_u8 = 371`
- L1342 _public enumerator_ `v_trig_preop_f64 = 372`
- L1343 _public enumerator_ `v_mqsad_u32_u8 = 373`
- L1344 _public enumerator_ `v_mad_u64_u32 = 374`
- L1345 _public enumerator_ `v_mad_i64_i32 = 375`
- L1346 _public enumerator_ `v_xor3_b32 = 376`
- L1347 _public enumerator_ `v_lshlrev_b64 = 767`
- L1348 _public enumerator_ `v_lshrrev_b64 = 768`
- L1349 _public enumerator_ `v_ashrrev_i64 = 769`
- L1350 _public enumerator_ `v_add_nc_u16 = 771`
- L1351 _public enumerator_ `v_sub_nc_u16 = 772`
- L1352 _public enumerator_ `v_mul_lo_u16 = 773`
- L1353 _public enumerator_ `v_lshrrev_b16 = 775`
- L1354 _public enumerator_ `v_ashrrev_i16 = 776`
- L1355 _public enumerator_ `v_max_u16 = 777`
- L1356 _public enumerator_ `v_max_i16 = 778`
- L1357 _public enumerator_ `v_min_u16 = 779`
- L1358 _public enumerator_ `v_min_i16 = 780`
- L1359 _public enumerator_ `v_add_nc_i16 = 781`
- L1360 _public enumerator_ `v_sub_nc_i16 = 782`
- L1361 _public enumerator_ `v_add_co_u32 = 783`
- L1362 _public enumerator_ `v_sub_co_u32 = 784`
- L1363 _public enumerator_ `v_pack_b32_f16 = 785`
- L1364 _public enumerator_ `v_cvt_pknorm_i16_f16 = 786`
- L1365 _public enumerator_ `v_cvt_pknorm_u16_f16 = 787`
- L1366 _public enumerator_ `v_lshlrev_b16 = 788`
- L1367 _public enumerator_ `v_subrev_co_u32 = 793`
- L1368 _public enumerator_ `v_mad_u16 = 832`
- L1369 _public enumerator_ `v_interp_p1ll_f16 = 834`
- L1370 _public enumerator_ `v_interp_p1lv_f16 = 835`
- L1371 _public enumerator_ `v_perm_b32 = 836`
- L1372 _public enumerator_ `v_xad_u32 = 837`
- L1373 _public enumerator_ `v_lshl_add_u32 = 838`
- L1374 _public enumerator_ `v_add_lshl_u32 = 839`
- L1375 _public enumerator_ `v_fma_f16 = 843`
- L1376 _public enumerator_ `v_min3_f16 = 849`
- L1377 _public enumerator_ `v_min3_i16 = 850`
- L1378 _public enumerator_ `v_min3_u16 = 851`
- L1379 _public enumerator_ `v_max3_f16 = 852`
- L1380 _public enumerator_ `v_max3_i16 = 853`
- L1381 _public enumerator_ `v_max3_u16 = 854`
- L1382 _public enumerator_ `v_med3_f16 = 855`
- L1383 _public enumerator_ `v_med3_i16 = 856`
- L1384 _public enumerator_ `v_med3_u16 = 857`
- L1385 _public enumerator_ `v_interp_p2_f16 = 858`
- L1386 _public enumerator_ `v_mad_i16 = 862`
- L1387 _public enumerator_ `v_div_fixup_f16 = 863`
- L1388 _public enumerator_ `v_readlane_b32 = 864`
- L1389 _public enumerator_ `v_writelane_b32 = 865`
- L1390 _public enumerator_ `v_ldexp_f32 = 866`
- L1391 _public enumerator_ `v_bfm_b32 = 867`
- L1392 _public enumerator_ `v_bcnt_u32_b32 = 868`
- L1393 _public enumerator_ `v_mbcnt_lo_u32_b32 = 869`
- L1394 _public enumerator_ `v_mbcnt_hi_u32_b32 = 870`
- L1395 _public enumerator_ `v_cvt_pknorm_i16_f32 = 872`
- L1396 _public enumerator_ `v_cvt_pknorm_u16_f32 = 873`
- L1397 _public enumerator_ `v_cvt_pk_u16_u32 = 874`
- L1398 _public enumerator_ `v_cvt_pk_i16_i32 = 875`
- L1399 _public enumerator_ `v_add3_u32 = 877`
- L1400 _public enumerator_ `v_lshl_or_b32 = 879`
- L1401 _public enumerator_ `v_and_or_b32 = 881`
- L1402 _public enumerator_ `v_or3_b32 = 882`
- L1403 _public enumerator_ `v_mad_u32_u16 = 883`
- L1404 _public enumerator_ `v_mad_i32_i16 = 885`
- L1405 _public enumerator_ `v_sub_nc_i32 = 886`
- L1406 _public enumerator_ `v_permlane16_b32 = 887`
- L1407 _public enumerator_ `v_permlanex16_b32 = 888`
- L1408 _public enumerator_ `v_add_nc_i32 = 895`

#### enum `RDNA1::EVINTERPOps`  
`enum class EVINTERPOps : uint16`  
_L1559-1564_
- L1561 _public enumerator_ `v_interp_p1_f32 = 0`
- L1562 _public enumerator_ `v_interp_p2_f32 = 1`
- L1563 _public enumerator_ `v_interp_mov_f32 = 2`

#### enum `RDNA1::EMIMGOps`  
`enum class EMIMGOps : uint16`  
_L1582-1677_
- L1584 _public enumerator_ `image_load = 0`
- L1585 _public enumerator_ `image_load_mip = 1`
- L1586 _public enumerator_ `image_load_pck = 2`
- L1587 _public enumerator_ `image_load_pck_sgn = 3`
- L1588 _public enumerator_ `image_load_mip_pck = 4`
- L1589 _public enumerator_ `image_load_mip_pck_sgn = 5`
- L1590 _public enumerator_ `image_store = 8`
- L1591 _public enumerator_ `image_store_mip = 9`
- L1592 _public enumerator_ `image_store_pck = 10`
- L1593 _public enumerator_ `image_store_mip_pck = 11`
- L1594 _public enumerator_ `image_get_resinfo = 14`
- L1595 _public enumerator_ `image_atomic_swap = 15`
- L1596 _public enumerator_ `image_atomic_cmpswap = 16`
- L1597 _public enumerator_ `image_atomic_add = 17`
- L1598 _public enumerator_ `image_atomic_sub = 18`
- L1599 _public enumerator_ `image_atomic_smin = 20`
- L1600 _public enumerator_ `image_atomic_umin = 21`
- L1601 _public enumerator_ `image_atomic_smax = 22`
- L1602 _public enumerator_ `image_atomic_umax = 23`
- L1603 _public enumerator_ `image_atomic_and = 24`
- L1604 _public enumerator_ `image_atomic_or = 25`
- L1605 _public enumerator_ `image_atomic_xor = 26`
- L1606 _public enumerator_ `image_atomic_inc = 27`
- L1607 _public enumerator_ `image_atomic_dec = 28`
- L1608 _public enumerator_ `image_atomic_fcmpswap = 29`
- L1609 _public enumerator_ `image_atomic_fmin = 30`
- L1610 _public enumerator_ `image_atomic_fmax = 31`
- L1611 _public enumerator_ `image_sample = 32`
- L1612 _public enumerator_ `image_sample_cl = 33`
- L1613 _public enumerator_ `image_sample_d = 34`
- L1614 _public enumerator_ `image_sample_d_cl = 35`
- L1615 _public enumerator_ `image_sample_l = 36`
- L1616 _public enumerator_ `image_sample_b = 37`
- L1617 _public enumerator_ `image_sample_b_cl = 38`
- L1618 _public enumerator_ `image_sample_lz = 39`
- L1619 _public enumerator_ `image_sample_c = 40`
- L1620 _public enumerator_ `image_sample_c_cl = 41`
- L1621 _public enumerator_ `image_sample_c_d = 42`
- L1622 _public enumerator_ `image_sample_c_d_cl = 43`
- L1623 _public enumerator_ `image_sample_c_l = 44`
- L1624 _public enumerator_ `image_sample_c_b = 45`
- L1625 _public enumerator_ `image_sample_c_b_cl = 46`
- L1626 _public enumerator_ `image_sample_c_lz = 47`
- L1627 _public enumerator_ `image_sample_o = 48`
- L1628 _public enumerator_ `image_sample_cl_o = 49`
- L1629 _public enumerator_ `image_sample_d_o = 50`
- L1630 _public enumerator_ `image_sample_d_cl_o = 51`
- L1631 _public enumerator_ `image_sample_l_o = 52`
- L1632 _public enumerator_ `image_sample_b_o = 53`
- L1633 _public enumerator_ `image_sample_b_cl_o = 54`
- L1634 _public enumerator_ `image_sample_lz_o = 55`
- L1635 _public enumerator_ `image_sample_c_o = 56`
- L1636 _public enumerator_ `image_sample_c_cl_o = 57`
- L1637 _public enumerator_ `image_sample_c_do_o = 58`
- L1638 _public enumerator_ `image_sample_c_d_cl_o = 59`
- L1639 _public enumerator_ `image_sample_c_l_o = 60`
- L1640 _public enumerator_ `image_sample_c_b_o = 61`
- L1641 _public enumerator_ `image_sample_c_b_cl_o = 62`
- L1642 _public enumerator_ `image_sample_c_lz_o = 63`
- L1643 _public enumerator_ `image_gather4 = 64`
- L1644 _public enumerator_ `image_gather4_cl = 65`
- L1645 _public enumerator_ `image_gather4_l = 68`
- L1646 _public enumerator_ `image_gather4_b = 69`
- L1647 _public enumerator_ `image_gather4_b_cl = 70`
- L1648 _public enumerator_ `image_gather4_lz = 71`
- L1649 _public enumerator_ `image_gather4_c = 72`
- L1650 _public enumerator_ `image_gather4_c_cl = 73`
- L1651 _public enumerator_ `image_gather4_c_l = 76`
- L1652 _public enumerator_ `image_gather4_c_b = 77`
- L1653 _public enumerator_ `image_gather4_c_b_cl = 78`
- L1654 _public enumerator_ `image_gather4_c_lz = 79`
- L1655 _public enumerator_ `image_gather4_o = 80`
- L1656 _public enumerator_ `image_gather4_cl_o = 81`
- L1657 _public enumerator_ `image_gather4_l_o = 84`
- L1658 _public enumerator_ `image_gather4_b_o = 85`
- L1659 _public enumerator_ `image_gather4_b_cl_o = 86`
- L1660 _public enumerator_ `image_gather4_lz_o = 87`
- L1661 _public enumerator_ `image_gather4_c_o = 88`
- L1662 _public enumerator_ `image_gather4_c_cl_o = 89`
- L1663 _public enumerator_ `image_gather4_c_l_o = 92`
- L1664 _public enumerator_ `image_gather4_c_b_o = 93`
- L1665 _public enumerator_ `image_gather4_c_b_cl_o = 94`
- L1666 _public enumerator_ `image_gather4_c_lz_o = 95`
- L1667 _public enumerator_ `image_get_lod = 96`
- L1668 _public enumerator_ `image_gather4h = 97`
- L1669 _public enumerator_ `image_sample_d_g16 = 162`
- L1670 _public enumerator_ `image_sample_d_cl_g16 = 163`
- L1671 _public enumerator_ `image_sample_c_d_g16 = 170`
- L1672 _public enumerator_ `image_sample_c_d_cl_g16 = 171`
- L1673 _public enumerator_ `image_sample_d_o_g16 = 178`
- L1674 _public enumerator_ `image_sample_d_cl_o_g16 = 179`
- L1675 _public enumerator_ `image_sample_c_d_o_g16 = 186`
- L1676 _public enumerator_ `image_sample_c_d_cl_o_g16 = 187`

#### enum `RDNA1::EMUBUFOps`  
`enum class EMUBUFOps : uint16`  
_L1785-1862_
- L1787 _public enumerator_ `buffer_load_format_x = 0`
- L1788 _public enumerator_ `buffer_load_format_xy = 1`
- L1789 _public enumerator_ `buffer_load_format_xyz = 2`
- L1790 _public enumerator_ `buffer_load_format_xyzw = 3`
- L1791 _public enumerator_ `buffer_store_format_x = 4`
- L1792 _public enumerator_ `buffer_store_format_xy = 5`
- L1793 _public enumerator_ `buffer_store_format_xyz = 6`
- L1794 _public enumerator_ `buffer_store_format_xyzw = 7`
- L1795 _public enumerator_ `buffer_load_ubyte = 8`
- L1796 _public enumerator_ `buffer_load_sbyte = 9`
- L1797 _public enumerator_ `buffer_load_ushort = 10`
- L1798 _public enumerator_ `buffer_load_sshort = 11`
- L1799 _public enumerator_ `buffer_load_dword = 12`
- L1800 _public enumerator_ `buffer_load_dwordx2 = 13`
- L1801 _public enumerator_ `buffer_load_dwordx4 = 14`
- L1802 _public enumerator_ `buffer_load_dwordx3 = 15`
- L1803 _public enumerator_ `buffer_store_byte = 24`
- L1804 _public enumerator_ `buffer_store_byte_d16_hi = 25`
- L1805 _public enumerator_ `buffer_store_short = 26`
- L1806 _public enumerator_ `buffer_store_short_d16_hi = 27`
- L1807 _public enumerator_ `buffer_store_dword = 28`
- L1808 _public enumerator_ `buffer_store_dwordx2 = 29`
- L1809 _public enumerator_ `buffer_store_dwordx4 = 30`
- L1810 _public enumerator_ `buffer_store_dwordx3 = 31`
- L1811 _public enumerator_ `buffer_load_ubyte_d16 = 32`
- L1812 _public enumerator_ `buffer_load_ubyte_d16_hi = 33`
- L1813 _public enumerator_ `buffer_load_sbyte_d16 = 34`
- L1814 _public enumerator_ `buffer_load_sbyte_d16_hi = 35`
- L1815 _public enumerator_ `buffer_load_short_d16 = 36`
- L1816 _public enumerator_ `buffer_load_short_d16_hi = 37`
- L1817 _public enumerator_ `buffer_load_format_d16_hi_x = 38`
- L1818 _public enumerator_ `buffer_store_format_d16_hi_x = 39`
- L1819 _public enumerator_ `buffer_atomic_swap = 48`
- L1820 _public enumerator_ `buffer_atomic_cmpswap = 49`
- L1821 _public enumerator_ `buffer_atomic_add = 50`
- L1822 _public enumerator_ `buffer_atomic_sub = 51`
- L1823 _public enumerator_ `buffer_atomic_csub = 52`
- L1824 _public enumerator_ `buffer_atomic_smin = 53`
- L1825 _public enumerator_ `buffer_atomic_umin = 54`
- L1826 _public enumerator_ `buffer_atomic_smax = 55`
- L1827 _public enumerator_ `buffer_atomic_umax = 56`
- L1828 _public enumerator_ `buffer_atomic_and = 57`
- L1829 _public enumerator_ `buffer_atomic_or = 58`
- L1830 _public enumerator_ `buffer_atomic_xor = 59`
- L1831 _public enumerator_ `buffer_atomic_inc = 60`
- L1832 _public enumerator_ `buffer_atomic_dec = 61`
- L1833 _public enumerator_ `buffer_atomic_fcmpswap = 62`
- L1834 _public enumerator_ `buffer_atomic_fmin = 63`
- L1835 _public enumerator_ `buffer_atomic_fmax = 64`
- L1836 _public enumerator_ `buffer_atomic_swap_x2 = 80`
- L1837 _public enumerator_ `buffer_atomic_cmpswap_x2 = 81`
- L1838 _public enumerator_ `buffer_atomic_add_x2 = 82`
- L1839 _public enumerator_ `buffer_atomic_sub_x2 = 83`
- L1840 _public enumerator_ `buffer_atomic_smin_x2 = 85`
- L1841 _public enumerator_ `buffer_atomic_umin_x2 = 86`
- L1842 _public enumerator_ `buffer_atomic_smax_x2 = 87`
- L1843 _public enumerator_ `buffer_atomic_umax_x2 = 88`
- L1844 _public enumerator_ `buffer_atomic_and_x2 = 89`
- L1845 _public enumerator_ `buffer_atomic_or_x2 = 90`
- L1846 _public enumerator_ `buffer_atomic_xor_x2 = 91`
- L1847 _public enumerator_ `buffer_atomic_inc_x2 = 92`
- L1848 _public enumerator_ `buffer_atomic_dec_x2 = 93`
- L1849 _public enumerator_ `buffer_atomic_fcmpswap_x2 = 94`
- L1850 _public enumerator_ `buffer_atomic_fmin_x2 = 95`
- L1851 _public enumerator_ `buffer_atomic_fmax_x2 = 96`
- L1852 _public enumerator_ `buffer_gl0_inv = 113`
- L1853 _public enumerator_ `buffer_gl1_inv = 114`
- L1854 _public enumerator_ `buffer_load_format_d16_x = 128`
- L1855 _public enumerator_ `buffer_load_format_d16_xy = 129`
- L1856 _public enumerator_ `buffer_load_format_d16_xyz = 130`
- L1857 _public enumerator_ `buffer_load_format_d16_xyzw = 131`
- L1858 _public enumerator_ `buffer_store_format_d16_x = 132`
- L1859 _public enumerator_ `buffer_store_format_d16_xy = 133`
- L1860 _public enumerator_ `buffer_store_format_d16_xyz = 134`
- L1861 _public enumerator_ `buffer_store_format_d16_xyzw = 135`

#### enum `RDNA1::EMTBUFOps`  
`enum class EMTBUFOps : uint16`  
_L1952-1970_
- L1954 _public enumerator_ `tbuffer_load_format_x = 0`
- L1955 _public enumerator_ `tbuffer_load_format_xy = 1`
- L1956 _public enumerator_ `tbuffer_load_format_xyz = 2`
- L1957 _public enumerator_ `tbuffer_load_format_xyzw = 3`
- L1958 _public enumerator_ `tbuffer_store_format_x = 4`
- L1959 _public enumerator_ `tbuffer_store_format_xy = 5`
- L1960 _public enumerator_ `tbuffer_store_format_xyz = 6`
- L1961 _public enumerator_ `tbuffer_store_format_xyzw = 7`
- L1962 _public enumerator_ `tbuffer_load_format_d16_x = 8`
- L1963 _public enumerator_ `tbuffer_load_format_d16_xy = 9`
- L1964 _public enumerator_ `tbuffer_load_format_d16_xyz = 10`
- L1965 _public enumerator_ `tbuffer_load_format_d16_xyzw = 11`
- L1966 _public enumerator_ `tbuffer_store_format_d16_x = 12`
- L1967 _public enumerator_ `tbuffer_store_format_d16_xy = 13`
- L1968 _public enumerator_ `tbuffer_store_format_d16_xyz = 14`
- L1969 _public enumerator_ `tbuffer_store_format_d16_xyzw = 15`

#### enum `RDNA1::EFLATOps`  
`enum class EFLATOps : uint16`  
_L2001-2057_
- L2003 _public enumerator_ `flat_load_ubyte = 8`
- L2004 _public enumerator_ `flat_load_sbyte = 9`
- L2005 _public enumerator_ `flat_load_ushort = 10`
- L2006 _public enumerator_ `flat_load_sshort = 11`
- L2007 _public enumerator_ `flat_load_dword = 12`
- L2008 _public enumerator_ `flat_load_dwordx2 = 13`
- L2009 _public enumerator_ `flat_load_dwordx4 = 14`
- L2010 _public enumerator_ `flat_load_dwordx3 = 15`
- L2011 _public enumerator_ `flat_store_byte = 24`
- L2012 _public enumerator_ `flat_store_byte_d16_hi = 25`
- L2013 _public enumerator_ `flat_store_short = 26`
- L2014 _public enumerator_ `flat_store_short_d16_hi = 27`
- L2015 _public enumerator_ `flat_store_dword = 28`
- L2016 _public enumerator_ `flat_store_dwordx2 = 29`
- L2017 _public enumerator_ `flat_store_dwordx4 = 30`
- L2018 _public enumerator_ `flat_store_dwordx3 = 31`
- L2019 _public enumerator_ `flat_load_ubyte_d16 = 32`
- L2020 _public enumerator_ `flat_load_ubyte_d16_hi = 33`
- L2021 _public enumerator_ `flat_load_sbyte_d16 = 34`
- L2022 _public enumerator_ `flat_load_sbyte_d16_hi = 35`
- L2023 _public enumerator_ `flat_load_short_d16 = 36`
- L2024 _public enumerator_ `flat_load_short_d16_hi = 37`
- L2025 _public enumerator_ `flat_atomic_swap = 48`
- L2026 _public enumerator_ `flat_atomic_cmpswap = 49`
- L2027 _public enumerator_ `flat_atomic_add = 50`
- L2028 _public enumerator_ `flat_atomic_sub = 51`
- L2029 _public enumerator_ `flat_atomic_smin = 53`
- L2030 _public enumerator_ `flat_atomic_umin = 54`
- L2031 _public enumerator_ `flat_atomic_smax = 55`
- L2032 _public enumerator_ `flat_atomic_umax = 56`
- L2033 _public enumerator_ `flat_atomic_and = 57`
- L2034 _public enumerator_ `flat_atomic_or = 58`
- L2035 _public enumerator_ `flat_atomic_xor = 59`
- L2036 _public enumerator_ `flat_atomic_inc = 60`
- L2037 _public enumerator_ `flat_atomic_dec = 61`
- L2038 _public enumerator_ `flat_atomic_fcmpswap = 62`
- L2039 _public enumerator_ `flat_atomic_fmin = 63`
- L2040 _public enumerator_ `flat_atomic_fmax = 64`
- L2041 _public enumerator_ `flat_atomic_swap_x2 = 80`
- L2042 _public enumerator_ `flat_atomic_cmpswap_x2 = 81`
- L2043 _public enumerator_ `flat_atomic_add_x2 = 82`
- L2044 _public enumerator_ `flat_atomic_sub_x2 = 83`
- L2045 _public enumerator_ `flat_atomic_smin_x2 = 85`
- L2046 _public enumerator_ `flat_atomic_umin_x2 = 86`
- L2047 _public enumerator_ `flat_atomic_smax_x2 = 87`
- L2048 _public enumerator_ `flat_atomic_umax_x2 = 88`
- L2049 _public enumerator_ `flat_atomic_and_x2 = 89`
- L2050 _public enumerator_ `flat_atomic_or_x2 = 90`
- L2051 _public enumerator_ `flat_atomic_xor_x2 = 91`
- L2052 _public enumerator_ `flat_atomic_inc_x2 = 92`
- L2053 _public enumerator_ `flat_atomic_dec_x2 = 93`
- L2054 _public enumerator_ `flat_atomic_fcmpswap_x2 = 94`
- L2055 _public enumerator_ `flat_atomic_fmin_x2 = 95`
- L2056 _public enumerator_ `flat_atomic_fmax_x2 = 96`

#### enum `RDNA1::ESCRATCHOps`  
`enum class ESCRATCHOps : uint16`  
_L2126-2150_
- L2128 _public enumerator_ `scratch_load_ubyte = 8`
- L2129 _public enumerator_ `scratch_load_sbyte = 9`
- L2130 _public enumerator_ `scratch_load_ushort = 10`
- L2131 _public enumerator_ `scratch_load_sshort = 11`
- L2132 _public enumerator_ `scratch_load_dword = 12`
- L2133 _public enumerator_ `scratch_load_dwordx2 = 13`
- L2134 _public enumerator_ `scratch_load_dwordx4 = 14`
- L2135 _public enumerator_ `scratch_load_dwordx3 = 15`
- L2136 _public enumerator_ `scratch_store_byte = 24`
- L2137 _public enumerator_ `scratch_store_byte_d16_hi = 25`
- L2138 _public enumerator_ `scratch_store_short = 26`
- L2139 _public enumerator_ `scratch_store_short_d16_hi = 27`
- L2140 _public enumerator_ `scratch_store_dword = 28`
- L2141 _public enumerator_ `scratch_store_dwordx2 = 29`
- L2142 _public enumerator_ `scratch_store_dwordx4 = 30`
- L2143 _public enumerator_ `scratch_store_dwordx3 = 31`
- L2144 _public enumerator_ `scratch_load_ubyte_d16 = 32`
- L2145 _public enumerator_ `scratch_load_ubyte_d16_hi = 33`
- L2146 _public enumerator_ `scratch_load_sbyte_d16 = 34`
- L2147 _public enumerator_ `scratch_load_sbyte_d16_hi = 35`
- L2148 _public enumerator_ `scratch_load_short_d16 = 36`
- L2149 _public enumerator_ `scratch_load_short_d16_hi = 37`

#### enum `RDNA1::ELDSGDSOps`  
`enum class ELDSGDSOps : uint16`  
_L2187-2312_
- L2189 _public enumerator_ `ds_add_u32 = 0`
- L2190 _public enumerator_ `ds_sub_u32 = 1`
- L2191 _public enumerator_ `ds_rsub_u32 = 2`
- L2192 _public enumerator_ `ds_inc_u32 = 3`
- L2193 _public enumerator_ `ds_dec_u32 = 4`
- L2194 _public enumerator_ `ds_min_i32 = 5`
- L2195 _public enumerator_ `ds_max_i32 = 6`
- L2196 _public enumerator_ `ds_min_u32 = 7`
- L2197 _public enumerator_ `ds_max_u32 = 8`
- L2198 _public enumerator_ `ds_and_b32 = 9`
- L2199 _public enumerator_ `ds_or_b32 = 10`
- L2200 _public enumerator_ `ds_xor_b32 = 11`
- L2201 _public enumerator_ `ds_mskor_b32 = 12`
- L2202 _public enumerator_ `ds_write_b32 = 13`
- L2203 _public enumerator_ `ds_write2_b32 = 14`
- L2204 _public enumerator_ `ds_write2st64_b32 = 15`
- L2205 _public enumerator_ `ds_cmpst_b32 = 16`
- L2206 _public enumerator_ `ds_cmpst_f32 = 17`
- L2207 _public enumerator_ `ds_min_f32 = 18`
- L2208 _public enumerator_ `ds_max_f32 = 19`
- L2209 _public enumerator_ `ds_nop = 20`
- L2210 _public enumerator_ `ds_add_f32 = 21`
- L2211 _public enumerator_ `ds_gws_sema_release_all = 24`
- L2212 _public enumerator_ `ds_gws_init = 25`
- L2213 _public enumerator_ `ds_gws_sema_v = 26`
- L2214 _public enumerator_ `ds_gws_sema_br = 27`
- L2215 _public enumerator_ `ds_gws_sema_p = 28`
- L2216 _public enumerator_ `ds_gws_barrier = 29`
- L2217 _public enumerator_ `ds_write_b8 = 30`
- L2218 _public enumerator_ `ds_write_b16 = 31`
- L2219 _public enumerator_ `ds_add_rtn_u32 = 32`
- L2220 _public enumerator_ `ds_sub_rtn_u32 = 33`
- L2221 _public enumerator_ `ds_rsub_rtn_u32 = 34`
- L2222 _public enumerator_ `ds_inc_rtn_u32 = 35`
- L2223 _public enumerator_ `ds_dec_rtn_u32 = 36`
- L2224 _public enumerator_ `ds_min_rtn_i32 = 37`
- L2225 _public enumerator_ `ds_max_rtn_i32 = 38`
- L2226 _public enumerator_ `ds_min_rtn_u32 = 39`
- L2227 _public enumerator_ `ds_max_rtn_u32 = 40`
- L2228 _public enumerator_ `ds_and_rtn_b32 = 41`
- L2229 _public enumerator_ `ds_or_rtn_b32 = 42`
- L2230 _public enumerator_ `ds_xor_rtn_b32 = 43`
- L2231 _public enumerator_ `ds_mskor_rtn_b32 = 44`
- L2232 _public enumerator_ `ds_wrxchg_rtn_b32 = 45`
- L2233 _public enumerator_ `ds_wrxchg2_rtn_b32 = 46`
- L2234 _public enumerator_ `ds_wrxchg2st64_rtn_b32 = 47`
- L2235 _public enumerator_ `ds_cmpst_rtn_b32 = 48`
- L2236 _public enumerator_ `ds_cmpst_rtn_f32 = 49`
- L2237 _public enumerator_ `ds_min_rtn_f32 = 50`
- L2238 _public enumerator_ `ds_max_rtn_f32 = 51`
- L2239 _public enumerator_ `ds_wrap_rtn_b32 = 52`
- L2240 _public enumerator_ `ds_swizzle_b32 = 53`
- L2241 _public enumerator_ `ds_read_b32 = 54`
- L2242 _public enumerator_ `ds_read2_b32 = 55`
- L2243 _public enumerator_ `ds_read2st64_b32 = 56`
- L2244 _public enumerator_ `ds_read_i8 = 57`
- L2245 _public enumerator_ `ds_read_u8 = 58`
- L2246 _public enumerator_ `ds_read_i16 = 59`
- L2247 _public enumerator_ `ds_read_u16 = 60`
- L2248 _public enumerator_ `ds_consume = 61`
- L2249 _public enumerator_ `ds_append = 62`
- L2250 _public enumerator_ `ds_ordered_count = 63`
- L2251 _public enumerator_ `ds_add_u64 = 64`
- L2252 _public enumerator_ `ds_sub_u64 = 65`
- L2253 _public enumerator_ `ds_rsub_u64 = 66`
- L2254 _public enumerator_ `ds_inc_u64 = 67`
- L2255 _public enumerator_ `ds_dec_u64 = 68`
- L2256 _public enumerator_ `ds_min_i64 = 69`
- L2257 _public enumerator_ `ds_max_i64 = 70`
- L2258 _public enumerator_ `ds_min_u64 = 71`
- L2259 _public enumerator_ `ds_max_u64 = 72`
- L2260 _public enumerator_ `ds_and_b64 = 73`
- L2261 _public enumerator_ `ds_or_b64 = 74`
- L2262 _public enumerator_ `ds_xor_b64 = 75`
- L2263 _public enumerator_ `ds_mskor_b64 = 76`
- L2264 _public enumerator_ `ds_write_b64 = 77`
- L2265 _public enumerator_ `ds_write2_b64 = 78`
- L2266 _public enumerator_ `ds_write2st64_b64 = 79`
- L2267 _public enumerator_ `ds_cmpst_b64 = 80`
- L2268 _public enumerator_ `ds_cmpst_f64 = 81`
- L2269 _public enumerator_ `ds_min_f64 = 82`
- L2270 _public enumerator_ `ds_max_f64 = 83`
- L2271 _public enumerator_ `ds_add_rtn_f32 = 85`
- L2272 _public enumerator_ `ds_add_rtn_u64 = 96`
- L2273 _public enumerator_ `ds_sub_rtn_u64 = 97`
- L2274 _public enumerator_ `ds_rsub_rtn_u64 = 98`
- L2275 _public enumerator_ `ds_inc_rtn_u64 = 99`
- L2276 _public enumerator_ `ds_dec_rtn_u64 = 100`
- L2277 _public enumerator_ `ds_min_rtn_i64 = 101`
- L2278 _public enumerator_ `ds_max_rtn_i64 = 102`
- L2279 _public enumerator_ `ds_min_rtn_u64 = 103`
- L2280 _public enumerator_ `ds_max_rtn_u64 = 104`
- L2281 _public enumerator_ `ds_and_rtn_b64 = 105`
- L2282 _public enumerator_ `ds_or_rtn_b64 = 106`
- L2283 _public enumerator_ `ds_xor_rtn_b64 = 107`
- L2284 _public enumerator_ `ds_mskor_rtn_b64 = 108`
- L2285 _public enumerator_ `ds_wrxchg_rtn_b64 = 109`
- L2286 _public enumerator_ `ds_wrxchg2_rtn_b64 = 110`
- L2287 _public enumerator_ `ds_wrxchg2st64_rtn_b64 = 111`
- L2288 _public enumerator_ `ds_cmpst_rtn_b64 = 112`
- L2289 _public enumerator_ `ds_cmpst_rtn_f64 = 113`
- L2290 _public enumerator_ `ds_min_rtn_f64 = 114`
- L2291 _public enumerator_ `ds_max_rtn_f64 = 115`
- L2292 _public enumerator_ `ds_read_b64 = 118`
- L2293 _public enumerator_ `ds_read2_b64 = 119`
- L2294 _public enumerator_ `ds_read2st64_b64 = 120`
- L2295 _public enumerator_ `ds_condxchg32_rtn_b64 = 126`
- L2296 _public enumerator_ `ds_write_b8_d16_hi = 160`
- L2297 _public enumerator_ `ds_write_b16_d16_hi = 161`
- L2298 _public enumerator_ `ds_read_u8_d16 = 162`
- L2299 _public enumerator_ `ds_read_u8_d16_hi = 163`
- L2300 _public enumerator_ `ds_read_i8_d16 = 164`
- L2301 _public enumerator_ `ds_read_i8_d16_hi = 165`
- L2302 _public enumerator_ `ds_read_u16_d16 = 166`
- L2303 _public enumerator_ `ds_read_u16_d16_hi = 167`
- L2304 _public enumerator_ `ds_write_addtid_b32 = 176`
- L2305 _public enumerator_ `ds_read_addtid_b32 = 177`
- L2306 _public enumerator_ `ds_permute_b32 = 178`
- L2307 _public enumerator_ `ds_bpermute_b32 = 179`
- L2308 _public enumerator_ `ds_write_b96 = 222`
- L2309 _public enumerator_ `ds_write_b128 = 223`
- L2310 _public enumerator_ `ds_read_b96 = 254`
- L2311 _public enumerator_ `ds_read_b128 = 255`

#### enum `RDNA1::EGLOBALOps`  
`enum class EGLOBALOps : uint16`  
_L2450-2509_
- L2452 _public enumerator_ `global_load_ubyte = 8`
- L2453 _public enumerator_ `global_load_sbyte = 9`
- L2454 _public enumerator_ `global_load_ushort = 10`
- L2455 _public enumerator_ `global_load_sshort = 11`
- L2456 _public enumerator_ `global_load_dword = 12`
- L2457 _public enumerator_ `global_load_dwordx2 = 13`
- L2458 _public enumerator_ `global_load_dwordx4 = 14`
- L2459 _public enumerator_ `global_load_dwordx3 = 15`
- L2460 _public enumerator_ `global_load_dword_addtid = 22`
- L2461 _public enumerator_ `global_store_dword_addtid = 23`
- L2462 _public enumerator_ `global_store_byte = 24`
- L2463 _public enumerator_ `global_store_byte_d16_hi = 25`
- L2464 _public enumerator_ `global_store_short = 26`
- L2465 _public enumerator_ `global_store_short_d16_hi = 27`
- L2466 _public enumerator_ `global_store_dword = 28`
- L2467 _public enumerator_ `global_store_dwordx2 = 29`
- L2468 _public enumerator_ `global_store_dwordx4 = 30`
- L2469 _public enumerator_ `global_store_dwordx3 = 31`
- L2470 _public enumerator_ `global_load_ubyte_d16 = 32`
- L2471 _public enumerator_ `global_load_ubyte_d16_hi = 33`
- L2472 _public enumerator_ `global_load_sbyte_d16 = 34`
- L2473 _public enumerator_ `global_load_sbyte_d16_hi = 35`
- L2474 _public enumerator_ `global_load_short_d16 = 36`
- L2475 _public enumerator_ `global_load_short_d16_hi = 37`
- L2476 _public enumerator_ `global_atomic_swap = 48`
- L2477 _public enumerator_ `global_atomic_cmpswap = 49`
- L2478 _public enumerator_ `global_atomic_add = 50`
- L2479 _public enumerator_ `global_atomic_sub = 51`
- L2480 _public enumerator_ `global_atomic_csub = 52`
- L2481 _public enumerator_ `global_atomic_smin = 53`
- L2482 _public enumerator_ `global_atomic_umin = 54`
- L2483 _public enumerator_ `global_atomic_smax = 55`
- L2484 _public enumerator_ `global_atomic_umax = 56`
- L2485 _public enumerator_ `global_atomic_and = 57`
- L2486 _public enumerator_ `global_atomic_or = 58`
- L2487 _public enumerator_ `global_atomic_xor = 59`
- L2488 _public enumerator_ `global_atomic_inc = 60`
- L2489 _public enumerator_ `global_atomic_dec = 61`
- L2490 _public enumerator_ `global_atomic_fcmpswap = 62`
- L2491 _public enumerator_ `global_atomic_fmin = 63`
- L2492 _public enumerator_ `global_atomic_fmax = 64`
- L2493 _public enumerator_ `global_atomic_swap_x2 = 80`
- L2494 _public enumerator_ `global_atomic_cmpswap_x2 = 81`
- L2495 _public enumerator_ `global_atomic_add_x2 = 82`
- L2496 _public enumerator_ `global_atomic_sub_x2 = 83`
- L2497 _public enumerator_ `global_atomic_smin_x2 = 85`
- L2498 _public enumerator_ `global_atomic_umin_x2 = 86`
- L2499 _public enumerator_ `global_atomic_smax_x2 = 87`
- L2500 _public enumerator_ `global_atomic_umax_x2 = 88`
- L2501 _public enumerator_ `global_atomic_and_x2 = 89`
- L2502 _public enumerator_ `global_atomic_or_x2 = 90`
- L2503 _public enumerator_ `global_atomic_xor_x2 = 91`
- L2504 _public enumerator_ `global_atomic_inc_x2 = 92`
- L2505 _public enumerator_ `global_atomic_dec_x2 = 93`
- L2506 _public enumerator_ `global_atomic_fcmpswap_x2 = 94`
- L2507 _public enumerator_ `global_atomic_fmin_x2 = 95`
- L2508 _public enumerator_ `global_atomic_fmax_x2 = 96`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RDNA1`
- L83 _function_ `const char* ToString(ESOP1Ops Op)` (scope `RDNA1`)
- L85 _macro_ `#define OP_TO_STRING_CASE(x) case ESOP1Ops::x: return #x`
- L216 _function_ `const char* ToString(ESOP2Ops Op)` (scope `RDNA1`)
- L218 _macro_ `#define OP_TO_STRING_CASE(x) case ESOP2Ops::x: return #x`
- L311 _function_ `const char* ToString(ESOPKOps Op)` (scope `RDNA1`)
- L313 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPKOps::x: return #x`
- L391 _function_ `const char* ToString(ESOPPOps Op)` (scope `RDNA1`)
- L393 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPPOps::x: return #x`
- L460 _function_ `const char* ToString(ESMEMOps Op)` (scope `RDNA1`)
- L462 _macro_ `#define OP_TO_STRING_CASE(x) case ESMEMOps::x: return #x`
- L511 _function_ `const char* ToString(ESOPCOps Op)` (scope `RDNA1`)
- L513 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPCOps::x: return #x`
- L627 _function_ `const char* ToString(EVOP1Ops Op)` (scope `RDNA1`)
- L629 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP1Ops::x: return #x`
- L747 _function_ `const char* ToString(EVOP3POps Op)` (scope `RDNA1`)
- L749 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP3POps::x: return #x`
- L834 _function_ `const char* ToString(EVOP2Ops Op)` (scope `RDNA1`)
- L836 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP2Ops::x: return #x`
- L1089 _function_ `const char* ToString(EVOPCOps Op)` (scope `RDNA1`)
- L1091 _macro_ `#define OP_TO_STRING_CASE(x) case EVOPCOps::x: return #x`
- L1411 _function_ `inline bool IsVOP3BEncoding(EVOP3ABOps Op)` (scope `RDNA1`)
- L1431 _function_ `const char* ToString(EVOP3ABOps Op)` (scope `RDNA1`)
- L1433 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP3ABOps::x: return #x`
- L1566 _function_ `const char* ToString(EVINTERPOps Op)` (scope `RDNA1`)
- L1568 _macro_ `#define OP_TO_STRING_CASE(x) case EVINTERPOps::x: return #x`
- L1679 _function_ `const char* ToString(EMIMGOps Op)` (scope `RDNA1`)
- L1681 _macro_ `#define OP_TO_STRING_CASE(x) case EMIMGOps::x: return #x`
- L1864 _function_ `const char* ToString(EMUBUFOps Op)` (scope `RDNA1`)
- L1866 _macro_ `#define OP_TO_STRING_CASE(x) case EMUBUFOps::x: return #x`
- L1972 _function_ `const char* ToString(EMTBUFOps Op)` (scope `RDNA1`)
- L1974 _macro_ `#define OP_TO_STRING_CASE(x) case EMTBUFOps::x: return #x`
- L2059 _function_ `const char* ToString(EFLATOps Op)` (scope `RDNA1`)
- L2061 _macro_ `#define OP_TO_STRING_CASE(x) case EFLATOps::x: return #x`
- L2152 _function_ `const char* ToString(ESCRATCHOps Op)` (scope `RDNA1`)
- L2154 _macro_ `#define OP_TO_STRING_CASE(x) case ESCRATCHOps::x: return #x`
- L2314 _function_ `const char* ToString(ELDSGDSOps Op)` (scope `RDNA1`)
- L2316 _macro_ `#define OP_TO_STRING_CASE(x) case ELDSGDSOps::x: return #x`
- L2511 _function_ `const char* ToString(EGLOBALOps Op)` (scope `RDNA1`)
- L2513 _macro_ `#define OP_TO_STRING_CASE(x) case EGLOBALOps::x: return #x`
- L2581 _function_ `inline bool HasTrailingLiteral(RDNA1::EVOP2Ops Op)` (scope `RDNA1`)
- L2598 _function_ `void PrintSMEM(const FInstSMEM& Inst)` (scope `RDNA1`)
- L2604 _function_ `void PrintSOP1(const FInstSOP1& Inst)` (scope `RDNA1`)
- L2610 _function_ `void PrintSOP2(const FInstSOP2& Inst)` (scope `RDNA1`)
- L2616 _function_ `void PrintSOPP(const FInstSOPP& Inst)` (scope `RDNA1`)
- L2622 _function_ `void PrintSOPC(const FInstSOPC& Inst)` (scope `RDNA1`)
- L2628 _function_ `void PrintSOPK(const FInstSOPK& Inst)` (scope `RDNA1`)
- L2634 _function_ `void PrintMIMG(const FInstMIMG& Inst)` (scope `RDNA1`)
- L2640 _function_ `void PrintVINTERP(const FInstVINTERP& Inst)` (scope `RDNA1`)
- L2646 _function_ `void PrintVOP1(const FInstVOP1& Inst)` (scope `RDNA1`)
- L2652 _function_ `void PrintVOP2(const FInstVOP2& Inst)` (scope `RDNA1`)
- L2658 _function_ `void PrintVOP3A(const FInstVOP3A& Inst)` (scope `RDNA1`)
- L2688 _function_ `void PrintVOP3B(const FInstVOP3B& Inst)` (scope `RDNA1`)
- L2694 _function_ `void PrintVOP3P(const FInstVOP3P& Inst)` (scope `RDNA1`)
- L2700 _function_ `void PrintVOPC(const FInstVOPC& Inst)` (scope `RDNA1`)
- L2706 _function_ `void PrintLDSGDS(const FInstLDSGDS& Inst)` (scope `RDNA1`)
- L2712 _function_ `void PrintMUBUF(const FInstMUBUF& Inst)` (scope `RDNA1`)
- L2718 _function_ `void PrintMTBUF(const FInstMTBUF& Inst)` (scope `RDNA1`)
- L2724 _function_ `void PrintEXPORT(const FInstEXPORT& Inst)` (scope `RDNA1`)
- L2729 _function_ `void PrintFLAT(const FInstFSG& Inst)` (scope `RDNA1`)
- L2735 _function_ `void PrintSCRATCH(const FInstFSG& Inst)` (scope `RDNA1`)
- L2741 _function_ `void PrintGLOBAL(const FInstFSG& Inst)` (scope `RDNA1`)
- L2747 _function_ `void PrintFSG(const FInstFSG& Inst)` (scope `RDNA1`)

### `Source/Developer/ShaderCompilerCommon/Private/ISAParser/RDNA2_ISA.inl` (Private)


#### enum `RDNA2::ESOP1Ops`  
`enum class ESOP1Ops : uint16`  
_L14-81_
- L16 _public enumerator_ `s_mov_b32 = 3`
- L17 _public enumerator_ `s_mov_b64 = 4`
- L18 _public enumerator_ `s_cmov_b32 = 5`
- L19 _public enumerator_ `s_cmov_b64 = 6`
- L20 _public enumerator_ `s_not_b32 = 7`
- L21 _public enumerator_ `s_not_b64 = 8`
- L22 _public enumerator_ `s_wqm_b32 = 9`
- L23 _public enumerator_ `s_wqm_b64 = 10`
- L24 _public enumerator_ `s_brev_b32 = 11`
- L25 _public enumerator_ `s_brev_b64 = 12`
- L26 _public enumerator_ `s_bcnt0_i32_b32 = 13`
- L27 _public enumerator_ `s_bcnt0_i32_b64 = 14`
- L28 _public enumerator_ `s_bcnt1_i32_b32 = 15`
- L29 _public enumerator_ `s_bcnt1_i32_b64 = 16`
- L30 _public enumerator_ `s_ff0_i32_b32 = 17`
- L31 _public enumerator_ `s_ff0_i32_b64 = 18`
- L32 _public enumerator_ `s_ff1_i32_b32 = 19`
- L33 _public enumerator_ `s_ff1_i32_b64 = 20`
- L34 _public enumerator_ `s_flbit_i32_b32 = 21`
- L35 _public enumerator_ `s_flbit_i32_b64 = 22`
- L36 _public enumerator_ `s_flbit_i32 = 23`
- L37 _public enumerator_ `s_flbit_i32_i64 = 24`
- L38 _public enumerator_ `s_sext_i32_i8 = 25`
- L39 _public enumerator_ `s_sext_i32_i16 = 26`
- L40 _public enumerator_ `s_bitset0_b32 = 27`
- L41 _public enumerator_ `s_bitset0_b64 = 28`
- L42 _public enumerator_ `s_bitset1_b32 = 29`
- L43 _public enumerator_ `s_bitset1_b64 = 30`
- L44 _public enumerator_ `s_getpc_b64 = 31`
- L45 _public enumerator_ `s_setpc_b64 = 32`
- L46 _public enumerator_ `s_swappc_b64 = 33`
- L47 _public enumerator_ `s_rfe_b64 = 34`
- L48 _public enumerator_ `s_and_saveexec_b64 = 36`
- L49 _public enumerator_ `s_or_saveexec_b64 = 37`
- L50 _public enumerator_ `s_xor_saveexec_b64 = 38`
- L51 _public enumerator_ `s_andn2_saveexec_b64 = 39`
- L52 _public enumerator_ `s_orn2_saveexec_b64 = 40`
- L53 _public enumerator_ `s_nand_saveexec_b64 = 41`
- L54 _public enumerator_ `s_nor_saveexec_b64 = 42`
- L55 _public enumerator_ `s_xnor_saveexec_b64 = 43`
- L56 _public enumerator_ `s_quadmask_b32 = 44`
- L57 _public enumerator_ `s_quadmask_b64 = 45`
- L58 _public enumerator_ `s_movrels_b32 = 46`
- L59 _public enumerator_ `s_movrels_b64 = 47`
- L60 _public enumerator_ `s_movreld_b32 = 48`
- L61 _public enumerator_ `s_movreld_b64 = 49`
- L62 _public enumerator_ `s_abs_i32 = 52`
- L63 _public enumerator_ `s_andn1_saveexec_b64 = 55`
- L64 _public enumerator_ `s_orn1_saveexec_b64 = 56`
- L65 _public enumerator_ `s_andn1_wrexec_b64 = 57`
- L66 _public enumerator_ `s_andn2_wrexec_b64 = 58`
- L67 _public enumerator_ `s_bitreplicate_b64_b32 = 59`
- L68 _public enumerator_ `s_and_saveexec_b32 = 60`
- L69 _public enumerator_ `s_or_saveexec_b32 = 61`
- L70 _public enumerator_ `s_xor_saveexec_b32 = 62`
- L71 _public enumerator_ `s_andn2_saveexec_b32 = 63`
- L72 _public enumerator_ `s_orn2_saveexec_b32 = 64`
- L73 _public enumerator_ `s_nand_saveexec_b32 = 65`
- L74 _public enumerator_ `s_nor_saveexec_b32 = 66`
- L75 _public enumerator_ `s_xnor_saveexec_b32 = 67`
- L76 _public enumerator_ `s_andn1_saveexec_b32 = 68`
- L77 _public enumerator_ `s_orn1_saveexec_b32 = 69`
- L78 _public enumerator_ `s_and1_wrexec_b32 = 70`
- L79 _public enumerator_ `s_andn2_wrexec_b32 = 71`
- L80 _public enumerator_ `s_movrelsd_2_b32 = 73`

#### enum `RDNA2::ESOP2Ops`  
`enum class ESOP2Ops : uint16`  
_L161-214_
- L163 _public enumerator_ `s_add_u32 = 0`
- L164 _public enumerator_ `s_sub_u32 = 1`
- L165 _public enumerator_ `s_add_i32 = 2`
- L166 _public enumerator_ `s_sub_i32 = 3`
- L167 _public enumerator_ `s_addc_u32 = 4`
- L168 _public enumerator_ `s_subb_u32 = 5`
- L169 _public enumerator_ `s_min_i32 = 6`
- L170 _public enumerator_ `s_min_u32 = 7`
- L171 _public enumerator_ `s_max_i32 = 8`
- L172 _public enumerator_ `s_max_u32 = 9`
- L173 _public enumerator_ `s_cselect_b32 = 10`
- L174 _public enumerator_ `s_cselect_b64 = 11`
- L175 _public enumerator_ `s_and_b32 = 14`
- L176 _public enumerator_ `s_and_b64 = 15`
- L177 _public enumerator_ `s_or_b32 = 16`
- L178 _public enumerator_ `s_or_b64 = 17`
- L179 _public enumerator_ `s_xor_b32 = 18`
- L180 _public enumerator_ `s_xor_b64 = 19`
- L181 _public enumerator_ `s_andn2_b32 = 20`
- L182 _public enumerator_ `s_andn2_b64 = 21`
- L183 _public enumerator_ `s_orn2_b32 = 22`
- L184 _public enumerator_ `s_orn2_b64 = 23`
- L185 _public enumerator_ `s_nand_b32 = 24`
- L186 _public enumerator_ `s_nand_b64 = 25`
- L187 _public enumerator_ `s_nor_b32 = 26`
- L188 _public enumerator_ `s_nor_b64 = 27`
- L189 _public enumerator_ `s_xnor_b32 = 28`
- L190 _public enumerator_ `s_xnor_b64 = 29`
- L191 _public enumerator_ `s_lshl_b32 = 30`
- L192 _public enumerator_ `s_lshl_b64 = 31`
- L193 _public enumerator_ `s_lshr_b32 = 32`
- L194 _public enumerator_ `s_lshr_b64 = 33`
- L195 _public enumerator_ `s_ashr_i32 = 34`
- L196 _public enumerator_ `s_ashr_i64 = 35`
- L197 _public enumerator_ `s_bfm_b32 = 36`
- L198 _public enumerator_ `s_bfm_b64 = 37`
- L199 _public enumerator_ `s_mul_i32 = 38`
- L200 _public enumerator_ `s_bfe_u32 = 39`
- L201 _public enumerator_ `s_bfe_i32 = 40`
- L202 _public enumerator_ `s_bfe_u64 = 41`
- L203 _public enumerator_ `s_bfe_i64 = 42`
- L204 _public enumerator_ `s_absdiff_i32 = 44`
- L205 _public enumerator_ `s_lshl1_add_u32 = 46`
- L206 _public enumerator_ `s_lshl2_add_u32 = 47`
- L207 _public enumerator_ `s_lshl3_add_u32 = 48`
- L208 _public enumerator_ `s_lshl4_add_u32 = 49`
- L209 _public enumerator_ `s_pack_ll_b32_b16 = 50`
- L210 _public enumerator_ `s_pack_lh_b32_b16 = 51`
- L211 _public enumerator_ `s_pack_hh_b32_b16 = 52`
- L212 _public enumerator_ `s_mul_hi_u32 = 53`
- L213 _public enumerator_ `s_mul_hi_i32 = 54`

#### enum `RDNA2::ESOPKOps`  
`enum class ESOPKOps : uint16`  
_L280-309_
- L282 _public enumerator_ `s_movk_i32 = 0`
- L283 _public enumerator_ `s_version = 1`
- L284 _public enumerator_ `s_cmovk_i32 = 2`
- L285 _public enumerator_ `s_cmpk_eq_i32 = 3`
- L286 _public enumerator_ `s_cmpk_lg_i32 = 4`
- L287 _public enumerator_ `s_cmpk_gt_i32 = 5`
- L288 _public enumerator_ `s_cmpk_ge_i32 = 6`
- L289 _public enumerator_ `s_cmpk_lt_i32 = 7`
- L290 _public enumerator_ `s_cmpk_le_i32 = 8`
- L291 _public enumerator_ `s_cmpk_eq_u32 = 9`
- L292 _public enumerator_ `s_cmpk_lg_u32 = 10`
- L293 _public enumerator_ `s_cmpk_gt_u32 = 11`
- L294 _public enumerator_ `s_cmpk_ge_u32 = 12`
- L295 _public enumerator_ `s_cmpk_lt_u32 = 13`
- L296 _public enumerator_ `s_cmpk_le_u32 = 14`
- L297 _public enumerator_ `s_addk_i32 = 15`
- L298 _public enumerator_ `s_mulk_i32 = 16`
- L299 _public enumerator_ `s_getreg_b32 = 18`
- L300 _public enumerator_ `s_setreg_b32 = 19`
- L301 _public enumerator_ `s_setreg_imm32_b32 = 21`
- L302 _public enumerator_ `s_call_b64 = 22`
- L303 _public enumerator_ `s_waitcnt_vscnt = 23`
- L304 _public enumerator_ `s_waitcnt_vmcnt = 24`
- L305 _public enumerator_ `s_waitcnt_expcnt = 25`
- L306 _public enumerator_ `s_waitcnt_lgkmcnt = 26`
- L307 _public enumerator_ `s_subvector_loop_begin = 27`
- L308 _public enumerator_ `s_subvector_loop_end = 28`

#### enum `RDNA2::ESOPPOps`  
`enum class ESOPPOps : uint16`  
_L351-389_
- L353 _public enumerator_ `s_nop = 0`
- L354 _public enumerator_ `s_endpgm = 1`
- L355 _public enumerator_ `s_branch = 2`
- L356 _public enumerator_ `s_wakeup = 3`
- L357 _public enumerator_ `s_cbranch_scc0 = 4`
- L358 _public enumerator_ `s_cbranch_scc1 = 5`
- L359 _public enumerator_ `s_cbranch_vccz = 6`
- L360 _public enumerator_ `s_cbranch_vccnz = 7`
- L361 _public enumerator_ `s_cbranch_execz = 8`
- L362 _public enumerator_ `s_cbranch_execnz = 9`
- L363 _public enumerator_ `s_barrier = 10`
- L364 _public enumerator_ `s_setkill = 11`
- L365 _public enumerator_ `s_waitcnt = 12`
- L366 _public enumerator_ `s_sethalt = 13`
- L367 _public enumerator_ `s_sleep = 14`
- L368 _public enumerator_ `s_setprio = 15`
- L369 _public enumerator_ `s_sendmsg = 16`
- L370 _public enumerator_ `s_sendmsghalt = 17`
- L371 _public enumerator_ `s_trap = 18`
- L372 _public enumerator_ `s_icache_inv = 19`
- L373 _public enumerator_ `s_incperflevel = 20`
- L374 _public enumerator_ `s_decperflevel = 21`
- L375 _public enumerator_ `s_ttracedata = 22`
- L376 _public enumerator_ `s_cbranch_cdbgsys = 23`
- L377 _public enumerator_ `s_cbranch_cdbguser = 24`
- L378 _public enumerator_ `s_cbranch_cdbgsys_or_user = 25`
- L379 _public enumerator_ `s_cbranch_cdbgsys_and_user = 26`
- L380 _public enumerator_ `s_endpgm_saved = 27`
- L381 _public enumerator_ `s_endpgm_ordered_ps_done = 30`
- L382 _public enumerator_ `s_code_end = 31`
- L383 _public enumerator_ `s_inst_prefetch = 32`
- L384 _public enumerator_ `s_clause = 33`
- L385 _public enumerator_ `s_waitcnt_depctr = 35`
- L386 _public enumerator_ `s_round_mode = 36`
- L387 _public enumerator_ `s_denorm_mode = 37`
- L388 _public enumerator_ `s_ttracedata_imm = 40`

#### enum `RDNA2::ESMEMOps`  
`enum class ESMEMOps : uint16`  
_L440-458_
- L442 _public enumerator_ `s_load_dword = 0`
- L443 _public enumerator_ `s_load_dwordx2 = 1`
- L444 _public enumerator_ `s_load_dwordx4 = 2`
- L445 _public enumerator_ `s_load_dwordx8 = 3`
- L446 _public enumerator_ `s_load_dwordx16 = 4`
- L447 _public enumerator_ `s_buffer_load_dword = 8`
- L448 _public enumerator_ `s_buffer_load_dwordx2 = 9`
- L449 _public enumerator_ `s_buffer_load_dwordx4 = 10`
- L450 _public enumerator_ `s_buffer_load_dwordx8 = 11`
- L451 _public enumerator_ `s_buffer_load_dwordx16 = 12`
- L452 _public enumerator_ `s_gl1_inv = 31`
- L453 _public enumerator_ `s_dcache_inv = 32`
- L454 _public enumerator_ `s_memtime = 36`
- L455 _public enumerator_ `s_memrealtime = 37`
- L456 _public enumerator_ `s_atc_probe = 38`
- L457 _public enumerator_ `s_atc_probe_buffer = 39`

#### enum `RDNA2::ESOPCOps`  
`enum class ESOPCOps : uint16`  
_L489-509_
- L491 _public enumerator_ `s_cmp_eq_i32 = 0`
- L492 _public enumerator_ `s_cmp_lg_i32 = 1`
- L493 _public enumerator_ `s_cmp_gt_i32 = 2`
- L494 _public enumerator_ `s_cmp_ge_i32 = 3`
- L495 _public enumerator_ `s_cmp_lt_i32 = 4`
- L496 _public enumerator_ `s_cmp_le_i32 = 5`
- L497 _public enumerator_ `s_cmp_eq_u32 = 6`
- L498 _public enumerator_ `s_cmp_lg_u32 = 7`
- L499 _public enumerator_ `s_cmp_gt_u32 = 8`
- L500 _public enumerator_ `s_cmp_ge_u32 = 9`
- L501 _public enumerator_ `s_cmp_lt_u32 = 10`
- L502 _public enumerator_ `s_cmp_le_u32 = 11`
- L503 _public enumerator_ `s_bitcmp0_b32 = 12`
- L504 _public enumerator_ `s_bitcmp1_b32 = 13`
- L505 _public enumerator_ `s_bitcmp0_b64 = 14`
- L506 _public enumerator_ `s_bitcmp1_b64 = 15`
- L507 _public enumerator_ `s_cmp_eq_u64 = 18`
- L508 _public enumerator_ `s_cmp_lg_u64 = 19`

#### enum `RDNA2::EVOP1Ops`  
`enum class EVOP1Ops : uint16`  
_L542-625_
- L544 _public enumerator_ `v_nop = 0`
- L545 _public enumerator_ `v_mov_b32 = 1`
- L546 _public enumerator_ `v_readfirstlane_b32 = 2`
- L547 _public enumerator_ `v_cvt_i32_f64 = 3`
- L548 _public enumerator_ `v_cvt_f64_i32 = 4`
- L549 _public enumerator_ `v_cvt_f32_i32 = 5`
- L550 _public enumerator_ `v_cvt_f32_u32 = 6`
- L551 _public enumerator_ `v_cvt_u32_f32 = 7`
- L552 _public enumerator_ `v_cvt_i32_f32 = 8`
- L553 _public enumerator_ `v_cvt_f16_f32 = 10`
- L554 _public enumerator_ `v_cvt_f32_f16 = 11`
- L555 _public enumerator_ `v_cvt_rpi_i32_f32 = 12`
- L556 _public enumerator_ `v_cvt_flr_i32_f32 = 13`
- L557 _public enumerator_ `v_cvt_off_f32_i4 = 14`
- L558 _public enumerator_ `v_cvt_f32_f64 = 15`
- L559 _public enumerator_ `v_cvt_f64_f32 = 16`
- L560 _public enumerator_ `v_cvt_f32_ubyte0 = 17`
- L561 _public enumerator_ `v_cvt_f32_ubyte1 = 18`
- L562 _public enumerator_ `v_cvt_f32_ubyte2 = 19`
- L563 _public enumerator_ `v_cvt_f32_ubyte3 = 20`
- L564 _public enumerator_ `v_cvt_u32_f64 = 21`
- L565 _public enumerator_ `v_cvt_f64_u32 = 22`
- L566 _public enumerator_ `v_trunc_f64 = 23`
- L567 _public enumerator_ `v_ceil_f64 = 24`
- L568 _public enumerator_ `v_rndne_f64 = 25`
- L569 _public enumerator_ `v_floor_f64 = 26`
- L570 _public enumerator_ `v_pipeflush = 27`
- L571 _public enumerator_ `v_fract_f32 = 32`
- L572 _public enumerator_ `v_trunc_f32 = 33`
- L573 _public enumerator_ `v_ceil_f32 = 34`
- L574 _public enumerator_ `v_rndne_f32 = 35`
- L575 _public enumerator_ `v_floor_f32 = 36`
- L576 _public enumerator_ `v_exp_f32 = 37`
- L577 _public enumerator_ `v_log_f32 = 39`
- L578 _public enumerator_ `v_rcp_f32 = 42`
- L579 _public enumerator_ `v_rcp_iflag_f32 = 43`
- L580 _public enumerator_ `v_rsq_f32 = 46`
- L581 _public enumerator_ `v_rcp_f64 = 47`
- L582 _public enumerator_ `v_rsq_f64 = 49`
- L583 _public enumerator_ `v_sqrt_f32 = 51`
- L584 _public enumerator_ `v_sqrt_f64 = 52`
- L585 _public enumerator_ `v_sin_f32 = 53`
- L586 _public enumerator_ `v_cos_f32 = 54`
- L587 _public enumerator_ `v_not_b32 = 55`
- L588 _public enumerator_ `v_bfrev_b32 = 56`
- L589 _public enumerator_ `v_ffbh_u32 = 57`
- L590 _public enumerator_ `v_ffbl_b32 = 58`
- L591 _public enumerator_ `v_ffbh_i32 = 59`
- L592 _public enumerator_ `v_frexp_exp_i32_f64 = 60`
- L593 _public enumerator_ `v_frexp_mant_f64 = 61`
- L594 _public enumerator_ `v_fract_f64 = 62`
- L595 _public enumerator_ `v_frexp_exp_i32_f32 = 63`
- L596 _public enumerator_ `v_frexp_mant_f32 = 64`
- L597 _public enumerator_ `v_clrexcp = 65`
- L598 _public enumerator_ `v_movreld_b32 = 66`
- L599 _public enumerator_ `v_movrels_b32 = 67`
- L600 _public enumerator_ `v_movrelsd_b32 = 68`
- L601 _public enumerator_ `v_movrelsd_2_b32 = 72`
- L602 _public enumerator_ `v_cvt_f16_u16 = 80`
- L603 _public enumerator_ `v_cvt_f16_i16 = 81`
- L604 _public enumerator_ `v_cvt_u16_f16 = 82`
- L605 _public enumerator_ `v_cvt_i16_f16 = 83`
- L606 _public enumerator_ `v_rcp_f16 = 84`
- L607 _public enumerator_ `v_sqrt_f16 = 85`
- L608 _public enumerator_ `v_rsq_f16 = 86`
- L609 _public enumerator_ `v_log_f16 = 87`
- L610 _public enumerator_ `v_exp_f16 = 88`
- L611 _public enumerator_ `v_frexp_mant_f16 = 89`
- L612 _public enumerator_ `v_frexp_exp_i16_f16 = 90`
- L613 _public enumerator_ `v_floor_f16 = 91`
- L614 _public enumerator_ `v_ceil_f16 = 92`
- L615 _public enumerator_ `v_trunc_f16 = 93`
- L616 _public enumerator_ `v_rndne_f16 = 94`
- L617 _public enumerator_ `v_fract_f16 = 95`
- L618 _public enumerator_ `v_sin_f16 = 96`
- L619 _public enumerator_ `v_cos_f16 = 97`
- L620 _public enumerator_ `v_sat_pk_u8_i16 = 98`
- L621 _public enumerator_ `v_cvt_norm_i16_f16 = 99`
- L622 _public enumerator_ `v_cvt_norm_u16_f16 = 100`
- L623 _public enumerator_ `v_swap_b32 = 101`
- L624 _public enumerator_ `v_swapref_b32 = 104`

#### enum `RDNA2::EVOP3POps`  
`enum class EVOP3POps : uint16`  
_L721-745_
- L723 _public enumerator_ `v_pk_mad_i16 = 0`
- L724 _public enumerator_ `v_pk_mul_lo_u16 = 1`
- L725 _public enumerator_ `v_pk_add_i16 = 2`
- L726 _public enumerator_ `v_pk_sub_i16 = 3`
- L727 _public enumerator_ `v_pk_lshlrev_b16 = 4`
- L728 _public enumerator_ `v_pk_lshrrev_b16 = 5`
- L729 _public enumerator_ `v_pk_ashrrev_i16 = 6`
- L730 _public enumerator_ `v_pk_max_i16 = 7`
- L731 _public enumerator_ `v_pk_min_i16 = 8`
- L732 _public enumerator_ `v_pk_mad_u16 = 9`
- L733 _public enumerator_ `v_pk_add_u16 = 10`
- L734 _public enumerator_ `v_pk_sub_u16 = 11`
- L735 _public enumerator_ `v_pk_max_u16 = 12`
- L736 _public enumerator_ `v_pk_min_u16 = 13`
- L737 _public enumerator_ `v_pk_fma_f16 = 14`
- L738 _public enumerator_ `v_pk_add_f16 = 15`
- L739 _public enumerator_ `v_pk_mul_f16 = 16`
- L740 _public enumerator_ `v_pk_min_f16 = 17`
- L741 _public enumerator_ `v_pk_max_f16 = 18`
- L742 _public enumerator_ `v_fma_mix_f32 = 32`
- L743 _public enumerator_ `v_fma_mixlo_f16 = 33`
- L744 _public enumerator_ `v_fma_mixhi_f16 = 34`

#### enum `RDNA2::EVOP2Ops`  
`enum class EVOP2Ops : uint16`  
_L782-834_
- L784 _public enumerator_ `v_cndmask_b32 = 1`
- L785 _public enumerator_ `v_dot2c_f32_f16 = 2`
- L786 _public enumerator_ `v_add_f32 = 3`
- L787 _public enumerator_ `v_sub_f32 = 4`
- L788 _public enumerator_ `v_subrev_f32 = 5`
- L789 _public enumerator_ `v_fmac_legacy_f32 = 6`
- L790 _public enumerator_ `v_mul_legacy_f32 = 7`
- L791 _public enumerator_ `v_mul_f32 = 8`
- L792 _public enumerator_ `v_mul_i32_i24 = 9`
- L793 _public enumerator_ `v_mul_hi_i32_i24 = 10`
- L794 _public enumerator_ `v_mul_u32_u24 = 11`
- L795 _public enumerator_ `v_mul_hi_u32_u24 = 12`
- L796 _public enumerator_ `v_dot4c_i32_i8 = 13`
- L797 _public enumerator_ `v_min_f32 = 15`
- L798 _public enumerator_ `v_max_f32 = 16`
- L799 _public enumerator_ `v_min_i32 = 17`
- L800 _public enumerator_ `v_max_i32 = 18`
- L801 _public enumerator_ `v_min_u32 = 19`
- L802 _public enumerator_ `v_max_u32 = 20`
- L803 _public enumerator_ `v_lshrrev_b32 = 22`
- L804 _public enumerator_ `v_ashrrev_i32 = 24`
- L805 _public enumerator_ `v_lshlrev_b32 = 26`
- L806 _public enumerator_ `v_and_b32 = 27`
- L807 _public enumerator_ `v_or_b32 = 28`
- L808 _public enumerator_ `v_xor_b32 = 29`
- L809 _public enumerator_ `v_xnor_b32 = 30`
- L810 _public enumerator_ `v_mac_f32 = 31`
- L811 _public enumerator_ `v_madmk_f32 = 32`
- L812 _public enumerator_ `v_madak_f32 = 33`
- L813 _public enumerator_ `v_add_nc_u32 = 37`
- L814 _public enumerator_ `v_sub_nc_u32 = 38`
- L815 _public enumerator_ `v_subrev_nc_u32 = 39`
- L816 _public enumerator_ `v_add_co_ci_u32 = 40`
- L817 _public enumerator_ `v_sub_co_ci_u32 = 41`
- L818 _public enumerator_ `v_subrev_co_ci_u32 = 42`
- L819 _public enumerator_ `v_fmac_f32 = 43`
- L820 _public enumerator_ `v_fmamk_f32 = 44`
- L821 _public enumerator_ `v_fmaak_f32 = 45`
- L822 _public enumerator_ `v_cvt_pkrtz_f16_f32 = 47`
- L823 _public enumerator_ `v_add_f16 = 50`
- L824 _public enumerator_ `v_sub_f16 = 51`
- L825 _public enumerator_ `v_subrev_f16 = 52`
- L826 _public enumerator_ `v_mul_f16 = 53`
- L827 _public enumerator_ `v_fmac_f16 = 54`
- L828 _public enumerator_ `v_fmamk_f16 = 55`
- L829 _public enumerator_ `v_fmaak_f16 = 56`
- L830 _public enumerator_ `v_max_f16 = 57`
- L831 _public enumerator_ `v_min_f16 = 58`
- L832 _public enumerator_ `v_ldexp_f16 = 59`
- L833 _public enumerator_ `v_pk_fmac_f16 = 60`

#### enum `RDNA2::EVOPCOps`  
`enum class EVOPCOps : uint16`  
_L899-1091_
- L901 _public enumerator_ `v_cmp_f_f32 = 0`
- L902 _public enumerator_ `v_cmp_lt_f32 = 1`
- L903 _public enumerator_ `v_cmp_eq_f32 = 2`
- L904 _public enumerator_ `v_cmp_le_f32 = 3`
- L905 _public enumerator_ `v_cmp_gt_f32 = 4`
- L906 _public enumerator_ `v_cmp_lg_f32 = 5`
- L907 _public enumerator_ `v_cmp_ge_f32 = 6`
- L908 _public enumerator_ `v_cmp_o_f32 = 7`
- L909 _public enumerator_ `v_cmp_u_f32 = 8`
- L910 _public enumerator_ `v_cmp_nge_f32 = 9`
- L911 _public enumerator_ `v_cmp_nlg_f32 = 10`
- L912 _public enumerator_ `v_cmp_ngt_f32 = 11`
- L913 _public enumerator_ `v_cmp_nle_f32 = 12`
- L914 _public enumerator_ `v_cmp_neq_f32 = 13`
- L915 _public enumerator_ `v_cmp_nlt_f32 = 14`
- L916 _public enumerator_ `v_cmp_tru_f32 = 15`
- L917 _public enumerator_ `v_cmpx_f_f32 = 16`
- L918 _public enumerator_ `v_cmpx_lt_f32 = 17`
- L919 _public enumerator_ `v_cmpx_eq_f32 = 18`
- L920 _public enumerator_ `v_cmpx_le_f32 = 19`
- L921 _public enumerator_ `v_cmpx_gt_f32 = 20`
- L922 _public enumerator_ `v_cmpx_lg_f32 = 21`
- L923 _public enumerator_ `v_cmpx_ge_f32 = 22`
- L924 _public enumerator_ `v_cmpx_o_f32 = 23`
- L925 _public enumerator_ `v_cmpx_u_f32 = 24`
- L926 _public enumerator_ `v_cmpx_nge_f32 = 25`
- L927 _public enumerator_ `v_cmpx_nlg_f32 = 26`
- L928 _public enumerator_ `v_cmpx_ngt_f32 = 27`
- L929 _public enumerator_ `v_cmpx_nle_f32 = 28`
- L930 _public enumerator_ `v_cmpx_neq_f32 = 29`
- L931 _public enumerator_ `v_cmpx_nlt_f32 = 30`
- L932 _public enumerator_ `v_cmpx_tru_f32 = 31`
- L933 _public enumerator_ `v_cmp_f_f64 = 32`
- L934 _public enumerator_ `v_cmp_lt_f64 = 33`
- L935 _public enumerator_ `v_cmp_eq_f64 = 34`
- L936 _public enumerator_ `v_cmp_le_f64 = 35`
- L937 _public enumerator_ `v_cmp_gt_f64 = 36`
- L938 _public enumerator_ `v_cmp_lg_f64 = 37`
- L939 _public enumerator_ `v_cmp_ge_f64 = 38`
- L940 _public enumerator_ `v_cmp_o_f64 = 39`
- L941 _public enumerator_ `v_cmp_u_f64 = 40`
- L942 _public enumerator_ `v_cmp_nge_f64 = 41`
- L943 _public enumerator_ `v_cmp_nlg_f64 = 42`
- L944 _public enumerator_ `v_cmp_ngt_f64 = 43`
- L945 _public enumerator_ `v_cmp_nle_f64 = 44`
- L946 _public enumerator_ `v_cmp_neq_f64 = 45`
- L947 _public enumerator_ `v_cmp_nlt_f64 = 46`
- L948 _public enumerator_ `v_cmp_tru_f64 = 47`
- L949 _public enumerator_ `v_cmpx_f_f64 = 48`
- L950 _public enumerator_ `v_cmpx_lt_f64 = 49`
- L951 _public enumerator_ `v_cmpx_eq_f64 = 50`
- L952 _public enumerator_ `v_cmpx_le_f64 = 51`
- L953 _public enumerator_ `v_cmpx_gt_f64 = 52`
- L954 _public enumerator_ `v_cmpx_lg_f64 = 53`
- L955 _public enumerator_ `v_cmpx_ge_f64 = 54`
- L956 _public enumerator_ `v_cmpx_o_f64 = 55`
- L957 _public enumerator_ `v_cmpx_u_f64 = 56`
- L958 _public enumerator_ `v_cmpx_nge_f64 = 57`
- L959 _public enumerator_ `v_cmpx_nlg_f64 = 58`
- L960 _public enumerator_ `v_cmpx_ngt_f64 = 59`
- L961 _public enumerator_ `v_cmpx_nle_f64 = 60`
- L962 _public enumerator_ `v_cmpx_neq_f64 = 61`
- L963 _public enumerator_ `v_cmpx_nlt_f64 = 62`
- L964 _public enumerator_ `v_cmpx_tru_f64 = 63`
- L965 _public enumerator_ `v_cmp_f_i32 = 128`
- L966 _public enumerator_ `v_cmp_lt_i32 = 129`
- L967 _public enumerator_ `v_cmp_eq_i32 = 130`
- L968 _public enumerator_ `v_cmp_le_i32 = 131`
- L969 _public enumerator_ `v_cmp_gt_i32 = 132`
- L970 _public enumerator_ `v_cmp_ne_i32 = 133`
- L971 _public enumerator_ `v_cmp_ge_i32 = 134`
- L972 _public enumerator_ `v_cmp_t_i32 = 135`
- L973 _public enumerator_ `v_cmp_class_f32 = 136`
- L974 _public enumerator_ `v_cmp_lt_i16 = 137`
- L975 _public enumerator_ `v_cmp_eq_i16 = 138`
- L976 _public enumerator_ `v_cmp_le_i16 = 139`
- L977 _public enumerator_ `v_cmp_gt_i16 = 140`
- L978 _public enumerator_ `v_cmp_ne_i16 = 141`
- L979 _public enumerator_ `v_cmp_ge_i16 = 142`
- L980 _public enumerator_ `v_cmp_class_f16 = 143`
- L981 _public enumerator_ `v_cmpx_f_i32 = 144`
- L982 _public enumerator_ `v_cmpx_lt_i32 = 145`
- L983 _public enumerator_ `v_cmpx_eq_i32 = 146`
- L984 _public enumerator_ `v_cmpx_le_i32 = 147`
- L985 _public enumerator_ `v_cmpx_gt_i32 = 148`
- L986 _public enumerator_ `v_cmpx_ne_i32 = 149`
- L987 _public enumerator_ `v_cmpx_ge_i32 = 150`
- L988 _public enumerator_ `v_cmpx_t_i32 = 151`
- L989 _public enumerator_ `v_cmpx_class_f32 = 152`
- L990 _public enumerator_ `v_cmpx_lt_i16 = 153`
- L991 _public enumerator_ `v_cmpx_eq_i16 = 154`
- L992 _public enumerator_ `v_cmpx_le_i16 = 155`
- L993 _public enumerator_ `v_cmpx_gt_i16 = 156`
- L994 _public enumerator_ `v_cmpx_ne_i16 = 157`
- L995 _public enumerator_ `v_cmpx_ge_i16 = 158`
- L996 _public enumerator_ `v_cmpx_class_f16 = 159`
- L997 _public enumerator_ `v_cmp_f_i64 = 160`
- L998 _public enumerator_ `v_cmp_lt_i64 = 161`
- L999 _public enumerator_ `v_cmp_eq_i64 = 162`
- L1000 _public enumerator_ `v_cmp_le_i64 = 163`
- L1001 _public enumerator_ `v_cmp_gt_i64 = 164`
- L1002 _public enumerator_ `v_cmp_ne_i64 = 165`
- L1003 _public enumerator_ `v_cmp_ge_i64 = 166`
- L1004 _public enumerator_ `v_cmp_t_i64 = 167`
- L1005 _public enumerator_ `v_cmp_class_f64 = 168`
- L1006 _public enumerator_ `v_cmp_lt_u16 = 169`
- L1007 _public enumerator_ `v_cmp_eq_u16 = 170`
- L1008 _public enumerator_ `v_cmp_le_u16 = 171`
- L1009 _public enumerator_ `v_cmp_gt_u16 = 172`
- L1010 _public enumerator_ `v_cmp_ne_u16 = 173`
- L1011 _public enumerator_ `v_cmp_ge_u16 = 174`
- L1012 _public enumerator_ `v_cmpx_f_i64 = 176`
- L1013 _public enumerator_ `v_cmpx_lt_i64 = 177`
- L1014 _public enumerator_ `v_cmpx_eq_i64 = 178`
- L1015 _public enumerator_ `v_cmpx_le_i64 = 179`
- L1016 _public enumerator_ `v_cmpx_gt_i64 = 180`
- L1017 _public enumerator_ `v_cmpx_ne_i64 = 181`
- L1018 _public enumerator_ `v_cmpx_ge_i64 = 182`
- L1019 _public enumerator_ `v_cmpx_t_i64 = 183`
- L1020 _public enumerator_ `v_cmpx_class_f64 = 184`
- L1021 _public enumerator_ `v_cmpx_lt_u16 = 185`
- L1022 _public enumerator_ `v_cmpx_eq_u16 = 186`
- L1023 _public enumerator_ `v_cmpx_le_u16 = 187`
- L1024 _public enumerator_ `v_cmpx_gt_u16 = 188`
- L1025 _public enumerator_ `v_cmpx_ne_u16 = 189`
- L1026 _public enumerator_ `v_cmpx_ge_u16 = 190`
- L1027 _public enumerator_ `v_cmp_f_u32 = 192`
- L1028 _public enumerator_ `v_cmp_lt_u32 = 193`
- L1029 _public enumerator_ `v_cmp_eq_u32 = 194`
- L1030 _public enumerator_ `v_cmp_le_u32 = 195`
- L1031 _public enumerator_ `v_cmp_gt_u32 = 196`
- L1032 _public enumerator_ `v_cmp_ne_u32 = 197`
- L1033 _public enumerator_ `v_cmp_ge_u32 = 198`
- L1034 _public enumerator_ `v_cmp_t_u32 = 199`
- L1035 _public enumerator_ `v_cmp_f_f16 = 200`
- L1036 _public enumerator_ `v_cmp_lt_f16 = 201`
- L1037 _public enumerator_ `v_cmp_eq_f16 = 202`
- L1038 _public enumerator_ `v_cmp_le_f16 = 203`
- L1039 _public enumerator_ `v_cmp_gt_f16 = 204`
- L1040 _public enumerator_ `v_cmp_lg_f16 = 205`
- L1041 _public enumerator_ `v_cmp_ge_f16 = 206`
- L1042 _public enumerator_ `v_cmp_o_f16 = 207`
- L1043 _public enumerator_ `v_cmpx_f_u32 = 208`
- L1044 _public enumerator_ `v_cmpx_lt_u32 = 209`
- L1045 _public enumerator_ `v_cmpx_eq_u32 = 210`
- L1046 _public enumerator_ `v_cmpx_le_u32 = 211`
- L1047 _public enumerator_ `v_cmpx_gt_u32 = 212`
- L1048 _public enumerator_ `v_cmpx_ne_u32 = 213`
- L1049 _public enumerator_ `v_cmpx_ge_u32 = 214`
- L1050 _public enumerator_ `v_cmpx_t_u32 = 215`
- L1051 _public enumerator_ `v_cmpx_f_f16 = 216`
- L1052 _public enumerator_ `v_cmpx_lt_f16 = 217`
- L1053 _public enumerator_ `v_cmpx_eq_f16 = 218`
- L1054 _public enumerator_ `v_cmpx_le_f16 = 219`
- L1055 _public enumerator_ `v_cmpx_gt_f16 = 220`
- L1056 _public enumerator_ `v_cmpx_lg_f16 = 221`
- L1057 _public enumerator_ `v_cmpx_ge_f16 = 222`
- L1058 _public enumerator_ `v_cmpx_o_f16 = 223`
- L1059 _public enumerator_ `v_cmp_f_u64 = 224`
- L1060 _public enumerator_ `v_cmp_lt_u64 = 225`
- L1061 _public enumerator_ `v_cmp_eq_u64 = 226`
- L1062 _public enumerator_ `v_cmp_le_u64 = 227`
- L1063 _public enumerator_ `v_cmp_gt_u64 = 228`
- L1064 _public enumerator_ `v_cmp_ne_u64 = 229`
- L1065 _public enumerator_ `v_cmp_ge_u64 = 230`
- L1066 _public enumerator_ `v_cmp_t_u64 = 231`
- L1067 _public enumerator_ `v_cmp_u_f16 = 232`
- L1068 _public enumerator_ `v_cmp_nge_f16 = 233`
- L1069 _public enumerator_ `v_cmp_nlg_f16 = 234`
- L1070 _public enumerator_ `v_cmp_ngt_f16 = 235`
- L1071 _public enumerator_ `v_cmp_nle_f16 = 236`
- L1072 _public enumerator_ `v_cmp_neq_f16 = 237`
- L1073 _public enumerator_ `v_cmp_nlt_f16 = 238`
- L1074 _public enumerator_ `v_cmp_tru_f16 = 239`
- L1075 _public enumerator_ `v_cmpx_f_u64 = 240`
- L1076 _public enumerator_ `v_cmpx_lt_u64 = 241`
- L1077 _public enumerator_ `v_cmpx_eq_u64 = 242`
- L1078 _public enumerator_ `v_cmpx_le_u64 = 243`
- L1079 _public enumerator_ `v_cmpx_gt_u64 = 244`
- L1080 _public enumerator_ `v_cmpx_ne_u64 = 245`
- L1081 _public enumerator_ `v_cmpx_ge_u64 = 246`
- L1082 _public enumerator_ `v_cmpx_t_u64 = 247`
- L1083 _public enumerator_ `v_cmpx_u_f16 = 248`
- L1084 _public enumerator_ `v_cmpx_nge_f16 = 249`
- L1085 _public enumerator_ `v_cmpx_nlg_f16 = 250`
- L1086 _public enumerator_ `v_cmpx_ngt_f16 = 251`
- L1087 _public enumerator_ `v_cmpx_nle_f16 = 252`
- L1088 _public enumerator_ `v_cmpx_neq_f16 = 253`
- L1089 _public enumerator_ `v_cmpx_nlt_f16 = 254`
- L1090 _public enumerator_ `v_cmpx_tru_f16 = 255`

#### enum `RDNA2::EVOP3ABOps`  
`enum class EVOP3ABOps : uint16`  
_L1296-1413_
- L1298 _public enumerator_ `v_fma_legacy_f32 = 320`
- L1299 _public enumerator_ `v_mad_f32 = 321`
- L1300 _public enumerator_ `v_mad_i32_i24 = 322`
- L1301 _public enumerator_ `v_mad_u32_u24 = 323`
- L1302 _public enumerator_ `v_cubeid_f32 = 324`
- L1303 _public enumerator_ `v_cubesc_f32 = 325`
- L1304 _public enumerator_ `v_cubetc_f32 = 326`
- L1305 _public enumerator_ `v_cubema_f32 = 327`
- L1306 _public enumerator_ `v_bfe_u32 = 328`
- L1307 _public enumerator_ `v_bfe_i32 = 329`
- L1308 _public enumerator_ `v_bfi_b32 = 330`
- L1309 _public enumerator_ `v_fma_f32 = 331`
- L1310 _public enumerator_ `v_fma_f64 = 332`
- L1311 _public enumerator_ `v_lerp_u8 = 333`
- L1312 _public enumerator_ `v_alignbit_b32 = 334`
- L1313 _public enumerator_ `v_alignbyte_b32 = 335`
- L1314 _public enumerator_ `v_mullit_f32 = 336`
- L1315 _public enumerator_ `v_min3_f32 = 337`
- L1316 _public enumerator_ `v_min3_i32 = 338`
- L1317 _public enumerator_ `v_min3_u32 = 339`
- L1318 _public enumerator_ `v_max3_f32 = 340`
- L1319 _public enumerator_ `v_max3_i32 = 341`
- L1320 _public enumerator_ `v_max3_u32 = 342`
- L1321 _public enumerator_ `v_med3_f32 = 343`
- L1322 _public enumerator_ `v_med3_i32 = 344`
- L1323 _public enumerator_ `v_med3_u32 = 345`
- L1324 _public enumerator_ `v_sad_u8 = 346`
- L1325 _public enumerator_ `v_sad_hi_u8 = 347`
- L1326 _public enumerator_ `v_sad_u16 = 348`
- L1327 _public enumerator_ `v_sad_u32 = 349`
- L1328 _public enumerator_ `v_cvt_pk_u8_f32 = 350`
- L1329 _public enumerator_ `v_div_fixup_f32 = 351`
- L1330 _public enumerator_ `v_div_fixup_f64 = 352`
- L1331 _public enumerator_ `v_add_f64 = 356`
- L1332 _public enumerator_ `v_mul_f64 = 357`
- L1333 _public enumerator_ `v_min_f64 = 358`
- L1334 _public enumerator_ `v_max_f64 = 359`
- L1335 _public enumerator_ `v_ldexp_f64 = 360`
- L1336 _public enumerator_ `v_mul_lo_u32 = 361`
- L1337 _public enumerator_ `v_mul_hi_u32 = 362`
- L1338 _public enumerator_ `v_mul_hi_i32 = 364`
- L1339 _public enumerator_ `v_div_scale_f32 = 365`
- L1340 _public enumerator_ `v_div_scale_f64 = 366`
- L1341 _public enumerator_ `v_div_fmas_f32 = 367`
- L1342 _public enumerator_ `v_div_fmas_f64 = 368`
- L1343 _public enumerator_ `v_msad_u8 = 369`
- L1344 _public enumerator_ `v_qsad_pk_u16_u8 = 370`
- L1345 _public enumerator_ `v_mqsad_pk_u16_u8 = 371`
- L1346 _public enumerator_ `v_trig_preop_f64 = 372`
- L1347 _public enumerator_ `v_mqsad_u32_u8 = 373`
- L1348 _public enumerator_ `v_mad_u64_u32 = 374`
- L1349 _public enumerator_ `v_mad_i64_i32 = 375`
- L1350 _public enumerator_ `v_xor3_b32 = 376`
- L1351 _public enumerator_ `v_lshlrev_b64 = 767`
- L1352 _public enumerator_ `v_lshrrev_b64 = 768`
- L1353 _public enumerator_ `v_ashrrev_i64 = 769`
- L1354 _public enumerator_ `v_add_nc_u16 = 771`
- L1355 _public enumerator_ `v_sub_nc_u16 = 772`
- L1356 _public enumerator_ `v_mul_lo_u16 = 773`
- L1357 _public enumerator_ `v_lshrrev_b16 = 775`
- L1358 _public enumerator_ `v_ashrrev_i16 = 776`
- L1359 _public enumerator_ `v_max_u16 = 777`
- L1360 _public enumerator_ `v_max_i16 = 778`
- L1361 _public enumerator_ `v_min_u16 = 779`
- L1362 _public enumerator_ `v_min_i16 = 780`
- L1363 _public enumerator_ `v_add_nc_i16 = 781`
- L1364 _public enumerator_ `v_sub_nc_i16 = 782`
- L1365 _public enumerator_ `v_add_co_u32 = 783`
- L1366 _public enumerator_ `v_sub_co_u32 = 784`
- L1367 _public enumerator_ `v_pack_b32_f16 = 785`
- L1368 _public enumerator_ `v_cvt_pknorm_i16_f16 = 786`
- L1369 _public enumerator_ `v_cvt_pknorm_u16_f16 = 787`
- L1370 _public enumerator_ `v_lshlrev_b16 = 788`
- L1371 _public enumerator_ `v_subrev_co_u32 = 793`
- L1372 _public enumerator_ `v_mad_u16 = 832`
- L1373 _public enumerator_ `v_interp_p1ll_f16 = 834`
- L1374 _public enumerator_ `v_interp_p1lv_f16 = 835`
- L1375 _public enumerator_ `v_perm_b32 = 836`
- L1376 _public enumerator_ `v_xad_u32 = 837`
- L1377 _public enumerator_ `v_lshl_add_u32 = 838`
- L1378 _public enumerator_ `v_add_lshl_u32 = 839`
- L1379 _public enumerator_ `v_fma_f16 = 843`
- L1380 _public enumerator_ `v_min3_f16 = 849`
- L1381 _public enumerator_ `v_min3_i16 = 850`
- L1382 _public enumerator_ `v_min3_u16 = 851`
- L1383 _public enumerator_ `v_max3_f16 = 852`
- L1384 _public enumerator_ `v_max3_i16 = 853`
- L1385 _public enumerator_ `v_max3_u16 = 854`
- L1386 _public enumerator_ `v_med3_f16 = 855`
- L1387 _public enumerator_ `v_med3_i16 = 856`
- L1388 _public enumerator_ `v_med3_u16 = 857`
- L1389 _public enumerator_ `v_interp_p2_f16 = 858`
- L1390 _public enumerator_ `v_mad_i16 = 862`
- L1391 _public enumerator_ `v_div_fixup_f16 = 863`
- L1392 _public enumerator_ `v_readlane_b32 = 864`
- L1393 _public enumerator_ `v_writelane_b32 = 865`
- L1394 _public enumerator_ `v_ldexp_f32 = 866`
- L1395 _public enumerator_ `v_bfm_b32 = 867`
- L1396 _public enumerator_ `v_bcnt_u32_b32 = 868`
- L1397 _public enumerator_ `v_mbcnt_lo_u32_b32 = 869`
- L1398 _public enumerator_ `v_mbcnt_hi_u32_b32 = 870`
- L1399 _public enumerator_ `v_cvt_pknorm_i16_f32 = 872`
- L1400 _public enumerator_ `v_cvt_pknorm_u16_f32 = 873`
- L1401 _public enumerator_ `v_cvt_pk_u16_u32 = 874`
- L1402 _public enumerator_ `v_cvt_pk_i16_i32 = 875`
- L1403 _public enumerator_ `v_add3_u32 = 877`
- L1404 _public enumerator_ `v_lshl_or_b32 = 879`
- L1405 _public enumerator_ `v_and_or_b32 = 881`
- L1406 _public enumerator_ `v_or3_b32 = 882`
- L1407 _public enumerator_ `v_mad_u32_u16 = 883`
- L1408 _public enumerator_ `v_mad_i32_i16 = 885`
- L1409 _public enumerator_ `v_sub_nc_i32 = 886`
- L1410 _public enumerator_ `v_permlane16_b32 = 887`
- L1411 _public enumerator_ `v_permlanex16_b32 = 888`
- L1412 _public enumerator_ `v_add_nc_i32 = 895`

#### enum `RDNA2::EVINTERPOps`  
`enum class EVINTERPOps : uint16`  
_L1563-1568_
- L1565 _public enumerator_ `v_interp_p1_f32 = 0`
- L1566 _public enumerator_ `v_interp_p2_f32 = 1`
- L1567 _public enumerator_ `v_interp_mov_f32 = 2`

#### enum `RDNA2::EMIMGOps`  
`enum class EMIMGOps : uint16`  
_L1586-1683_
- L1588 _public enumerator_ `image_load = 0`
- L1589 _public enumerator_ `image_load_mip = 1`
- L1590 _public enumerator_ `image_load_pck = 2`
- L1591 _public enumerator_ `image_load_pck_sgn = 3`
- L1592 _public enumerator_ `image_load_mip_pck = 4`
- L1593 _public enumerator_ `image_load_mip_pck_sgn = 5`
- L1594 _public enumerator_ `image_store = 8`
- L1595 _public enumerator_ `image_store_mip = 9`
- L1596 _public enumerator_ `image_store_pck = 10`
- L1597 _public enumerator_ `image_store_mip_pck = 11`
- L1598 _public enumerator_ `image_get_resinfo = 14`
- L1599 _public enumerator_ `image_atomic_swap = 15`
- L1600 _public enumerator_ `image_atomic_cmpswap = 16`
- L1601 _public enumerator_ `image_atomic_add = 17`
- L1602 _public enumerator_ `image_atomic_sub = 18`
- L1603 _public enumerator_ `image_atomic_smin = 20`
- L1604 _public enumerator_ `image_atomic_umin = 21`
- L1605 _public enumerator_ `image_atomic_smax = 22`
- L1606 _public enumerator_ `image_atomic_umax = 23`
- L1607 _public enumerator_ `image_atomic_and = 24`
- L1608 _public enumerator_ `image_atomic_or = 25`
- L1609 _public enumerator_ `image_atomic_xor = 26`
- L1610 _public enumerator_ `image_atomic_inc = 27`
- L1611 _public enumerator_ `image_atomic_dec = 28`
- L1612 _public enumerator_ `image_atomic_fcmpswap = 29`
- L1613 _public enumerator_ `image_atomic_fmin = 30`
- L1614 _public enumerator_ `image_atomic_fmax = 31`
- L1615 _public enumerator_ `image_sample = 32`
- L1616 _public enumerator_ `image_sample_cl = 33`
- L1617 _public enumerator_ `image_sample_d = 34`
- L1618 _public enumerator_ `image_sample_d_cl = 35`
- L1619 _public enumerator_ `image_sample_l = 36`
- L1620 _public enumerator_ `image_sample_b = 37`
- L1621 _public enumerator_ `image_sample_b_cl = 38`
- L1622 _public enumerator_ `image_sample_lz = 39`
- L1623 _public enumerator_ `image_sample_c = 40`
- L1624 _public enumerator_ `image_sample_c_cl = 41`
- L1625 _public enumerator_ `image_sample_c_d = 42`
- L1626 _public enumerator_ `image_sample_c_d_cl = 43`
- L1627 _public enumerator_ `image_sample_c_l = 44`
- L1628 _public enumerator_ `image_sample_c_b = 45`
- L1629 _public enumerator_ `image_sample_c_b_cl = 46`
- L1630 _public enumerator_ `image_sample_c_lz = 47`
- L1631 _public enumerator_ `image_sample_o = 48`
- L1632 _public enumerator_ `image_sample_cl_o = 49`
- L1633 _public enumerator_ `image_sample_d_o = 50`
- L1634 _public enumerator_ `image_sample_d_cl_o = 51`
- L1635 _public enumerator_ `image_sample_l_o = 52`
- L1636 _public enumerator_ `image_sample_b_o = 53`
- L1637 _public enumerator_ `image_sample_b_cl_o = 54`
- L1638 _public enumerator_ `image_sample_lz_o = 55`
- L1639 _public enumerator_ `image_sample_c_o = 56`
- L1640 _public enumerator_ `image_sample_c_cl_o = 57`
- L1641 _public enumerator_ `image_sample_c_do_o = 58`
- L1642 _public enumerator_ `image_sample_c_d_cl_o = 59`
- L1643 _public enumerator_ `image_sample_c_l_o = 60`
- L1644 _public enumerator_ `image_sample_c_b_o = 61`
- L1645 _public enumerator_ `image_sample_c_b_cl_o = 62`
- L1646 _public enumerator_ `image_sample_c_lz_o = 63`
- L1647 _public enumerator_ `image_gather4 = 64`
- L1648 _public enumerator_ `image_gather4_cl = 65`
- L1649 _public enumerator_ `image_gather4_l = 68`
- L1650 _public enumerator_ `image_gather4_b = 69`
- L1651 _public enumerator_ `image_gather4_b_cl = 70`
- L1652 _public enumerator_ `image_gather4_lz = 71`
- L1653 _public enumerator_ `image_gather4_c = 72`
- L1654 _public enumerator_ `image_gather4_c_cl = 73`
- L1655 _public enumerator_ `image_gather4_c_l = 76`
- L1656 _public enumerator_ `image_gather4_c_b = 77`
- L1657 _public enumerator_ `image_gather4_c_b_cl = 78`
- L1658 _public enumerator_ `image_gather4_c_lz = 79`
- L1659 _public enumerator_ `image_gather4_o = 80`
- L1660 _public enumerator_ `image_gather4_cl_o = 81`
- L1661 _public enumerator_ `image_gather4_l_o = 84`
- L1662 _public enumerator_ `image_gather4_b_o = 85`
- L1663 _public enumerator_ `image_gather4_b_cl_o = 86`
- L1664 _public enumerator_ `image_gather4_lz_o = 87`
- L1665 _public enumerator_ `image_gather4_c_o = 88`
- L1666 _public enumerator_ `image_gather4_c_cl_o = 89`
- L1667 _public enumerator_ `image_gather4_c_l_o = 92`
- L1668 _public enumerator_ `image_gather4_c_b_o = 93`
- L1669 _public enumerator_ `image_gather4_c_b_cl_o = 94`
- L1670 _public enumerator_ `image_gather4_c_lz_o = 95`
- L1671 _public enumerator_ `image_get_lod = 96`
- L1672 _public enumerator_ `image_gather4h = 97`
- L1673 _public enumerator_ `image_gather4h_pck = 98`
- L1674 _public enumerator_ `image_gather8h_pck = 99`
- L1675 _public enumerator_ `image_sample_d_g16 = 162`
- L1676 _public enumerator_ `image_sample_d_cl_g16 = 163`
- L1677 _public enumerator_ `image_sample_c_d_g16 = 170`
- L1678 _public enumerator_ `image_sample_c_d_cl_g16 = 171`
- L1679 _public enumerator_ `image_sample_d_o_g16 = 178`
- L1680 _public enumerator_ `image_sample_d_cl_o_g16 = 179`
- L1681 _public enumerator_ `image_sample_c_d_o_g16 = 186`
- L1682 _public enumerator_ `image_sample_c_d_cl_o_g16 = 187`

#### enum `RDNA2::EMUBUFOps`  
`enum class EMUBUFOps : uint16`  
_L1793-1870_
- L1795 _public enumerator_ `buffer_load_format_x = 0`
- L1796 _public enumerator_ `buffer_load_format_xy = 1`
- L1797 _public enumerator_ `buffer_load_format_xyz = 2`
- L1798 _public enumerator_ `buffer_load_format_xyzw = 3`
- L1799 _public enumerator_ `buffer_store_format_x = 4`
- L1800 _public enumerator_ `buffer_store_format_xy = 5`
- L1801 _public enumerator_ `buffer_store_format_xyz = 6`
- L1802 _public enumerator_ `buffer_store_format_xyzw = 7`
- L1803 _public enumerator_ `buffer_load_ubyte = 8`
- L1804 _public enumerator_ `buffer_load_sbyte = 9`
- L1805 _public enumerator_ `buffer_load_ushort = 10`
- L1806 _public enumerator_ `buffer_load_sshort = 11`
- L1807 _public enumerator_ `buffer_load_dword = 12`
- L1808 _public enumerator_ `buffer_load_dwordx2 = 13`
- L1809 _public enumerator_ `buffer_load_dwordx4 = 14`
- L1810 _public enumerator_ `buffer_load_dwordx3 = 15`
- L1811 _public enumerator_ `buffer_store_byte = 24`
- L1812 _public enumerator_ `buffer_store_byte_d16_hi = 25`
- L1813 _public enumerator_ `buffer_store_short = 26`
- L1814 _public enumerator_ `buffer_store_short_d16_hi = 27`
- L1815 _public enumerator_ `buffer_store_dword = 28`
- L1816 _public enumerator_ `buffer_store_dwordx2 = 29`
- L1817 _public enumerator_ `buffer_store_dwordx4 = 30`
- L1818 _public enumerator_ `buffer_store_dwordx3 = 31`
- L1819 _public enumerator_ `buffer_load_ubyte_d16 = 32`
- L1820 _public enumerator_ `buffer_load_ubyte_d16_hi = 33`
- L1821 _public enumerator_ `buffer_load_sbyte_d16 = 34`
- L1822 _public enumerator_ `buffer_load_sbyte_d16_hi = 35`
- L1823 _public enumerator_ `buffer_load_short_d16 = 36`
- L1824 _public enumerator_ `buffer_load_short_d16_hi = 37`
- L1825 _public enumerator_ `buffer_load_format_d16_hi_x = 38`
- L1826 _public enumerator_ `buffer_store_format_d16_hi_x = 39`
- L1827 _public enumerator_ `buffer_atomic_swap = 48`
- L1828 _public enumerator_ `buffer_atomic_cmpswap = 49`
- L1829 _public enumerator_ `buffer_atomic_add = 50`
- L1830 _public enumerator_ `buffer_atomic_sub = 51`
- L1831 _public enumerator_ `buffer_atomic_csub = 52`
- L1832 _public enumerator_ `buffer_atomic_smin = 53`
- L1833 _public enumerator_ `buffer_atomic_umin = 54`
- L1834 _public enumerator_ `buffer_atomic_smax = 55`
- L1835 _public enumerator_ `buffer_atomic_umax = 56`
- L1836 _public enumerator_ `buffer_atomic_and = 57`
- L1837 _public enumerator_ `buffer_atomic_or = 58`
- L1838 _public enumerator_ `buffer_atomic_xor = 59`
- L1839 _public enumerator_ `buffer_atomic_inc = 60`
- L1840 _public enumerator_ `buffer_atomic_dec = 61`
- L1841 _public enumerator_ `buffer_atomic_fcmpswap = 62`
- L1842 _public enumerator_ `buffer_atomic_fmin = 63`
- L1843 _public enumerator_ `buffer_atomic_fmax = 64`
- L1844 _public enumerator_ `buffer_atomic_swap_x2 = 80`
- L1845 _public enumerator_ `buffer_atomic_cmpswap_x2 = 81`
- L1846 _public enumerator_ `buffer_atomic_add_x2 = 82`
- L1847 _public enumerator_ `buffer_atomic_sub_x2 = 83`
- L1848 _public enumerator_ `buffer_atomic_smin_x2 = 85`
- L1849 _public enumerator_ `buffer_atomic_umin_x2 = 86`
- L1850 _public enumerator_ `buffer_atomic_smax_x2 = 87`
- L1851 _public enumerator_ `buffer_atomic_umax_x2 = 88`
- L1852 _public enumerator_ `buffer_atomic_and_x2 = 89`
- L1853 _public enumerator_ `buffer_atomic_or_x2 = 90`
- L1854 _public enumerator_ `buffer_atomic_xor_x2 = 91`
- L1855 _public enumerator_ `buffer_atomic_inc_x2 = 92`
- L1856 _public enumerator_ `buffer_atomic_dec_x2 = 93`
- L1857 _public enumerator_ `buffer_atomic_fcmpswap_x2 = 94`
- L1858 _public enumerator_ `buffer_atomic_fmin_x2 = 95`
- L1859 _public enumerator_ `buffer_atomic_fmax_x2 = 96`
- L1860 _public enumerator_ `buffer_gl0_inv = 113`
- L1861 _public enumerator_ `buffer_gl1_inv = 114`
- L1862 _public enumerator_ `buffer_load_format_d16_x = 128`
- L1863 _public enumerator_ `buffer_load_format_d16_xy = 129`
- L1864 _public enumerator_ `buffer_load_format_d16_xyz = 130`
- L1865 _public enumerator_ `buffer_load_format_d16_xyzw = 131`
- L1866 _public enumerator_ `buffer_store_format_d16_x = 132`
- L1867 _public enumerator_ `buffer_store_format_d16_xy = 133`
- L1868 _public enumerator_ `buffer_store_format_d16_xyz = 134`
- L1869 _public enumerator_ `buffer_store_format_d16_xyzw = 135`

#### enum `RDNA2::EMTBUFOps`  
`enum class EMTBUFOps : uint16`  
_L1960-1978_
- L1962 _public enumerator_ `tbuffer_load_format_x = 0`
- L1963 _public enumerator_ `tbuffer_load_format_xy = 1`
- L1964 _public enumerator_ `tbuffer_load_format_xyz = 2`
- L1965 _public enumerator_ `tbuffer_load_format_xyzw = 3`
- L1966 _public enumerator_ `tbuffer_store_format_x = 4`
- L1967 _public enumerator_ `tbuffer_store_format_xy = 5`
- L1968 _public enumerator_ `tbuffer_store_format_xyz = 6`
- L1969 _public enumerator_ `tbuffer_store_format_xyzw = 7`
- L1970 _public enumerator_ `tbuffer_load_format_d16_x = 8`
- L1971 _public enumerator_ `tbuffer_load_format_d16_xy = 9`
- L1972 _public enumerator_ `tbuffer_load_format_d16_xyz = 10`
- L1973 _public enumerator_ `tbuffer_load_format_d16_xyzw = 11`
- L1974 _public enumerator_ `tbuffer_store_format_d16_x = 12`
- L1975 _public enumerator_ `tbuffer_store_format_d16_xy = 13`
- L1976 _public enumerator_ `tbuffer_store_format_d16_xyz = 14`
- L1977 _public enumerator_ `tbuffer_store_format_d16_xyzw = 15`

#### enum `RDNA2::EFLATOps`  
`enum class EFLATOps : uint16`  
_L2009-2065_
- L2011 _public enumerator_ `flat_load_ubyte = 8`
- L2012 _public enumerator_ `flat_load_sbyte = 9`
- L2013 _public enumerator_ `flat_load_ushort = 10`
- L2014 _public enumerator_ `flat_load_sshort = 11`
- L2015 _public enumerator_ `flat_load_dword = 12`
- L2016 _public enumerator_ `flat_load_dwordx2 = 13`
- L2017 _public enumerator_ `flat_load_dwordx4 = 14`
- L2018 _public enumerator_ `flat_load_dwordx3 = 15`
- L2019 _public enumerator_ `flat_store_byte = 24`
- L2020 _public enumerator_ `flat_store_byte_d16_hi = 25`
- L2021 _public enumerator_ `flat_store_short = 26`
- L2022 _public enumerator_ `flat_store_short_d16_hi = 27`
- L2023 _public enumerator_ `flat_store_dword = 28`
- L2024 _public enumerator_ `flat_store_dwordx2 = 29`
- L2025 _public enumerator_ `flat_store_dwordx4 = 30`
- L2026 _public enumerator_ `flat_store_dwordx3 = 31`
- L2027 _public enumerator_ `flat_load_ubyte_d16 = 32`
- L2028 _public enumerator_ `flat_load_ubyte_d16_hi = 33`
- L2029 _public enumerator_ `flat_load_sbyte_d16 = 34`
- L2030 _public enumerator_ `flat_load_sbyte_d16_hi = 35`
- L2031 _public enumerator_ `flat_load_short_d16 = 36`
- L2032 _public enumerator_ `flat_load_short_d16_hi = 37`
- L2033 _public enumerator_ `flat_atomic_swap = 48`
- L2034 _public enumerator_ `flat_atomic_cmpswap = 49`
- L2035 _public enumerator_ `flat_atomic_add = 50`
- L2036 _public enumerator_ `flat_atomic_sub = 51`
- L2037 _public enumerator_ `flat_atomic_smin = 53`
- L2038 _public enumerator_ `flat_atomic_umin = 54`
- L2039 _public enumerator_ `flat_atomic_smax = 55`
- L2040 _public enumerator_ `flat_atomic_umax = 56`
- L2041 _public enumerator_ `flat_atomic_and = 57`
- L2042 _public enumerator_ `flat_atomic_or = 58`
- L2043 _public enumerator_ `flat_atomic_xor = 59`
- L2044 _public enumerator_ `flat_atomic_inc = 60`
- L2045 _public enumerator_ `flat_atomic_dec = 61`
- L2046 _public enumerator_ `flat_atomic_fcmpswap = 62`
- L2047 _public enumerator_ `flat_atomic_fmin = 63`
- L2048 _public enumerator_ `flat_atomic_fmax = 64`
- L2049 _public enumerator_ `flat_atomic_swap_x2 = 80`
- L2050 _public enumerator_ `flat_atomic_cmpswap_x2 = 81`
- L2051 _public enumerator_ `flat_atomic_add_x2 = 82`
- L2052 _public enumerator_ `flat_atomic_sub_x2 = 83`
- L2053 _public enumerator_ `flat_atomic_smin_x2 = 85`
- L2054 _public enumerator_ `flat_atomic_umin_x2 = 86`
- L2055 _public enumerator_ `flat_atomic_smax_x2 = 87`
- L2056 _public enumerator_ `flat_atomic_umax_x2 = 88`
- L2057 _public enumerator_ `flat_atomic_and_x2 = 89`
- L2058 _public enumerator_ `flat_atomic_or_x2 = 90`
- L2059 _public enumerator_ `flat_atomic_xor_x2 = 91`
- L2060 _public enumerator_ `flat_atomic_inc_x2 = 92`
- L2061 _public enumerator_ `flat_atomic_dec_x2 = 93`
- L2062 _public enumerator_ `flat_atomic_fcmpswap_x2 = 94`
- L2063 _public enumerator_ `flat_atomic_fmin_x2 = 95`
- L2064 _public enumerator_ `flat_atomic_fmax_x2 = 96`

#### enum `RDNA2::ESCRATCHOps`  
`enum class ESCRATCHOps : uint16`  
_L2134-2158_
- L2136 _public enumerator_ `scratch_load_ubyte = 8`
- L2137 _public enumerator_ `scratch_load_sbyte = 9`
- L2138 _public enumerator_ `scratch_load_ushort = 10`
- L2139 _public enumerator_ `scratch_load_sshort = 11`
- L2140 _public enumerator_ `scratch_load_dword = 12`
- L2141 _public enumerator_ `scratch_load_dwordx2 = 13`
- L2142 _public enumerator_ `scratch_load_dwordx4 = 14`
- L2143 _public enumerator_ `scratch_load_dwordx3 = 15`
- L2144 _public enumerator_ `scratch_store_byte = 24`
- L2145 _public enumerator_ `scratch_store_byte_d16_hi = 25`
- L2146 _public enumerator_ `scratch_store_short = 26`
- L2147 _public enumerator_ `scratch_store_short_d16_hi = 27`
- L2148 _public enumerator_ `scratch_store_dword = 28`
- L2149 _public enumerator_ `scratch_store_dwordx2 = 29`
- L2150 _public enumerator_ `scratch_store_dwordx4 = 30`
- L2151 _public enumerator_ `scratch_store_dwordx3 = 31`
- L2152 _public enumerator_ `scratch_load_ubyte_d16 = 32`
- L2153 _public enumerator_ `scratch_load_ubyte_d16_hi = 33`
- L2154 _public enumerator_ `scratch_load_sbyte_d16 = 34`
- L2155 _public enumerator_ `scratch_load_sbyte_d16_hi = 35`
- L2156 _public enumerator_ `scratch_load_short_d16 = 36`
- L2157 _public enumerator_ `scratch_load_short_d16_hi = 37`

#### enum `RDNA2::ELDSGDSOps`  
`enum class ELDSGDSOps : uint16`  
_L2195-2320_
- L2197 _public enumerator_ `ds_add_u32 = 0`
- L2198 _public enumerator_ `ds_sub_u32 = 1`
- L2199 _public enumerator_ `ds_rsub_u32 = 2`
- L2200 _public enumerator_ `ds_inc_u32 = 3`
- L2201 _public enumerator_ `ds_dec_u32 = 4`
- L2202 _public enumerator_ `ds_min_i32 = 5`
- L2203 _public enumerator_ `ds_max_i32 = 6`
- L2204 _public enumerator_ `ds_min_u32 = 7`
- L2205 _public enumerator_ `ds_max_u32 = 8`
- L2206 _public enumerator_ `ds_and_b32 = 9`
- L2207 _public enumerator_ `ds_or_b32 = 10`
- L2208 _public enumerator_ `ds_xor_b32 = 11`
- L2209 _public enumerator_ `ds_mskor_b32 = 12`
- L2210 _public enumerator_ `ds_write_b32 = 13`
- L2211 _public enumerator_ `ds_write2_b32 = 14`
- L2212 _public enumerator_ `ds_write2st64_b32 = 15`
- L2213 _public enumerator_ `ds_cmpst_b32 = 16`
- L2214 _public enumerator_ `ds_cmpst_f32 = 17`
- L2215 _public enumerator_ `ds_min_f32 = 18`
- L2216 _public enumerator_ `ds_max_f32 = 19`
- L2217 _public enumerator_ `ds_nop = 20`
- L2218 _public enumerator_ `ds_add_f32 = 21`
- L2219 _public enumerator_ `ds_gws_sema_release_all = 24`
- L2220 _public enumerator_ `ds_gws_init = 25`
- L2221 _public enumerator_ `ds_gws_sema_v = 26`
- L2222 _public enumerator_ `ds_gws_sema_br = 27`
- L2223 _public enumerator_ `ds_gws_sema_p = 28`
- L2224 _public enumerator_ `ds_gws_barrier = 29`
- L2225 _public enumerator_ `ds_write_b8 = 30`
- L2226 _public enumerator_ `ds_write_b16 = 31`
- L2227 _public enumerator_ `ds_add_rtn_u32 = 32`
- L2228 _public enumerator_ `ds_sub_rtn_u32 = 33`
- L2229 _public enumerator_ `ds_rsub_rtn_u32 = 34`
- L2230 _public enumerator_ `ds_inc_rtn_u32 = 35`
- L2231 _public enumerator_ `ds_dec_rtn_u32 = 36`
- L2232 _public enumerator_ `ds_min_rtn_i32 = 37`
- L2233 _public enumerator_ `ds_max_rtn_i32 = 38`
- L2234 _public enumerator_ `ds_min_rtn_u32 = 39`
- L2235 _public enumerator_ `ds_max_rtn_u32 = 40`
- L2236 _public enumerator_ `ds_and_rtn_b32 = 41`
- L2237 _public enumerator_ `ds_or_rtn_b32 = 42`
- L2238 _public enumerator_ `ds_xor_rtn_b32 = 43`
- L2239 _public enumerator_ `ds_mskor_rtn_b32 = 44`
- L2240 _public enumerator_ `ds_wrxchg_rtn_b32 = 45`
- L2241 _public enumerator_ `ds_wrxchg2_rtn_b32 = 46`
- L2242 _public enumerator_ `ds_wrxchg2st64_rtn_b32 = 47`
- L2243 _public enumerator_ `ds_cmpst_rtn_b32 = 48`
- L2244 _public enumerator_ `ds_cmpst_rtn_f32 = 49`
- L2245 _public enumerator_ `ds_min_rtn_f32 = 50`
- L2246 _public enumerator_ `ds_max_rtn_f32 = 51`
- L2247 _public enumerator_ `ds_wrap_rtn_b32 = 52`
- L2248 _public enumerator_ `ds_swizzle_b32 = 53`
- L2249 _public enumerator_ `ds_read_b32 = 54`
- L2250 _public enumerator_ `ds_read2_b32 = 55`
- L2251 _public enumerator_ `ds_read2st64_b32 = 56`
- L2252 _public enumerator_ `ds_read_i8 = 57`
- L2253 _public enumerator_ `ds_read_u8 = 58`
- L2254 _public enumerator_ `ds_read_i16 = 59`
- L2255 _public enumerator_ `ds_read_u16 = 60`
- L2256 _public enumerator_ `ds_consume = 61`
- L2257 _public enumerator_ `ds_append = 62`
- L2258 _public enumerator_ `ds_ordered_count = 63`
- L2259 _public enumerator_ `ds_add_u64 = 64`
- L2260 _public enumerator_ `ds_sub_u64 = 65`
- L2261 _public enumerator_ `ds_rsub_u64 = 66`
- L2262 _public enumerator_ `ds_inc_u64 = 67`
- L2263 _public enumerator_ `ds_dec_u64 = 68`
- L2264 _public enumerator_ `ds_min_i64 = 69`
- L2265 _public enumerator_ `ds_max_i64 = 70`
- L2266 _public enumerator_ `ds_min_u64 = 71`
- L2267 _public enumerator_ `ds_max_u64 = 72`
- L2268 _public enumerator_ `ds_and_b64 = 73`
- L2269 _public enumerator_ `ds_or_b64 = 74`
- L2270 _public enumerator_ `ds_xor_b64 = 75`
- L2271 _public enumerator_ `ds_mskor_b64 = 76`
- L2272 _public enumerator_ `ds_write_b64 = 77`
- L2273 _public enumerator_ `ds_write2_b64 = 78`
- L2274 _public enumerator_ `ds_write2st64_b64 = 79`
- L2275 _public enumerator_ `ds_cmpst_b64 = 80`
- L2276 _public enumerator_ `ds_cmpst_f64 = 81`
- L2277 _public enumerator_ `ds_min_f64 = 82`
- L2278 _public enumerator_ `ds_max_f64 = 83`
- L2279 _public enumerator_ `ds_add_rtn_f32 = 85`
- L2280 _public enumerator_ `ds_add_rtn_u64 = 96`
- L2281 _public enumerator_ `ds_sub_rtn_u64 = 97`
- L2282 _public enumerator_ `ds_rsub_rtn_u64 = 98`
- L2283 _public enumerator_ `ds_inc_rtn_u64 = 99`
- L2284 _public enumerator_ `ds_dec_rtn_u64 = 100`
- L2285 _public enumerator_ `ds_min_rtn_i64 = 101`
- L2286 _public enumerator_ `ds_max_rtn_i64 = 102`
- L2287 _public enumerator_ `ds_min_rtn_u64 = 103`
- L2288 _public enumerator_ `ds_max_rtn_u64 = 104`
- L2289 _public enumerator_ `ds_and_rtn_b64 = 105`
- L2290 _public enumerator_ `ds_or_rtn_b64 = 106`
- L2291 _public enumerator_ `ds_xor_rtn_b64 = 107`
- L2292 _public enumerator_ `ds_mskor_rtn_b64 = 108`
- L2293 _public enumerator_ `ds_wrxchg_rtn_b64 = 109`
- L2294 _public enumerator_ `ds_wrxchg2_rtn_b64 = 110`
- L2295 _public enumerator_ `ds_wrxchg2st64_rtn_b64 = 111`
- L2296 _public enumerator_ `ds_cmpst_rtn_b64 = 112`
- L2297 _public enumerator_ `ds_cmpst_rtn_f64 = 113`
- L2298 _public enumerator_ `ds_min_rtn_f64 = 114`
- L2299 _public enumerator_ `ds_max_rtn_f64 = 115`
- L2300 _public enumerator_ `ds_read_b64 = 118`
- L2301 _public enumerator_ `ds_read2_b64 = 119`
- L2302 _public enumerator_ `ds_read2st64_b64 = 120`
- L2303 _public enumerator_ `ds_condxchg32_rtn_b64 = 126`
- L2304 _public enumerator_ `ds_write_b8_d16_hi = 160`
- L2305 _public enumerator_ `ds_write_b16_d16_hi = 161`
- L2306 _public enumerator_ `ds_read_u8_d16 = 162`
- L2307 _public enumerator_ `ds_read_u8_d16_hi = 163`
- L2308 _public enumerator_ `ds_read_i8_d16 = 164`
- L2309 _public enumerator_ `ds_read_i8_d16_hi = 165`
- L2310 _public enumerator_ `ds_read_u16_d16 = 166`
- L2311 _public enumerator_ `ds_read_u16_d16_hi = 167`
- L2312 _public enumerator_ `ds_write_addtid_b32 = 176`
- L2313 _public enumerator_ `ds_read_addtid_b32 = 177`
- L2314 _public enumerator_ `ds_permute_b32 = 178`
- L2315 _public enumerator_ `ds_bpermute_b32 = 179`
- L2316 _public enumerator_ `ds_write_b96 = 222`
- L2317 _public enumerator_ `ds_write_b128 = 223`
- L2318 _public enumerator_ `ds_read_b96 = 254`
- L2319 _public enumerator_ `ds_read_b128 = 255`

#### enum `RDNA2::EGLOBALOps`  
`enum class EGLOBALOps : uint16`  
_L2458-2517_
- L2460 _public enumerator_ `global_load_ubyte = 8`
- L2461 _public enumerator_ `global_load_sbyte = 9`
- L2462 _public enumerator_ `global_load_ushort = 10`
- L2463 _public enumerator_ `global_load_sshort = 11`
- L2464 _public enumerator_ `global_load_dword = 12`
- L2465 _public enumerator_ `global_load_dwordx2 = 13`
- L2466 _public enumerator_ `global_load_dwordx4 = 14`
- L2467 _public enumerator_ `global_load_dwordx3 = 15`
- L2468 _public enumerator_ `global_load_dword_addtid = 22`
- L2469 _public enumerator_ `global_store_dword_addtid = 23`
- L2470 _public enumerator_ `global_store_byte = 24`
- L2471 _public enumerator_ `global_store_byte_d16_hi = 25`
- L2472 _public enumerator_ `global_store_short = 26`
- L2473 _public enumerator_ `global_store_short_d16_hi = 27`
- L2474 _public enumerator_ `global_store_dword = 28`
- L2475 _public enumerator_ `global_store_dwordx2 = 29`
- L2476 _public enumerator_ `global_store_dwordx4 = 30`
- L2477 _public enumerator_ `global_store_dwordx3 = 31`
- L2478 _public enumerator_ `global_load_ubyte_d16 = 32`
- L2479 _public enumerator_ `global_load_ubyte_d16_hi = 33`
- L2480 _public enumerator_ `global_load_sbyte_d16 = 34`
- L2481 _public enumerator_ `global_load_sbyte_d16_hi = 35`
- L2482 _public enumerator_ `global_load_short_d16 = 36`
- L2483 _public enumerator_ `global_load_short_d16_hi = 37`
- L2484 _public enumerator_ `global_atomic_swap = 48`
- L2485 _public enumerator_ `global_atomic_cmpswap = 49`
- L2486 _public enumerator_ `global_atomic_add = 50`
- L2487 _public enumerator_ `global_atomic_sub = 51`
- L2488 _public enumerator_ `global_atomic_csub = 52`
- L2489 _public enumerator_ `global_atomic_smin = 53`
- L2490 _public enumerator_ `global_atomic_umin = 54`
- L2491 _public enumerator_ `global_atomic_smax = 55`
- L2492 _public enumerator_ `global_atomic_umax = 56`
- L2493 _public enumerator_ `global_atomic_and = 57`
- L2494 _public enumerator_ `global_atomic_or = 58`
- L2495 _public enumerator_ `global_atomic_xor = 59`
- L2496 _public enumerator_ `global_atomic_inc = 60`
- L2497 _public enumerator_ `global_atomic_dec = 61`
- L2498 _public enumerator_ `global_atomic_fcmpswap = 62`
- L2499 _public enumerator_ `global_atomic_fmin = 63`
- L2500 _public enumerator_ `global_atomic_fmax = 64`
- L2501 _public enumerator_ `global_atomic_swap_x2 = 80`
- L2502 _public enumerator_ `global_atomic_cmpswap_x2 = 81`
- L2503 _public enumerator_ `global_atomic_add_x2 = 82`
- L2504 _public enumerator_ `global_atomic_sub_x2 = 83`
- L2505 _public enumerator_ `global_atomic_smin_x2 = 85`
- L2506 _public enumerator_ `global_atomic_umin_x2 = 86`
- L2507 _public enumerator_ `global_atomic_smax_x2 = 87`
- L2508 _public enumerator_ `global_atomic_umax_x2 = 88`
- L2509 _public enumerator_ `global_atomic_and_x2 = 89`
- L2510 _public enumerator_ `global_atomic_or_x2 = 90`
- L2511 _public enumerator_ `global_atomic_xor_x2 = 91`
- L2512 _public enumerator_ `global_atomic_inc_x2 = 92`
- L2513 _public enumerator_ `global_atomic_dec_x2 = 93`
- L2514 _public enumerator_ `global_atomic_fcmpswap_x2 = 94`
- L2515 _public enumerator_ `global_atomic_fmin_x2 = 95`
- L2516 _public enumerator_ `global_atomic_fmax_x2 = 96`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RDNA2`
- L83 _function_ `const char* ToString(ESOP1Ops Op)` (scope `RDNA2`)
- L85 _macro_ `#define OP_TO_STRING_CASE(x) case ESOP1Ops::x: return #x`
- L216 _function_ `const char* ToString(ESOP2Ops Op)` (scope `RDNA2`)
- L218 _macro_ `#define OP_TO_STRING_CASE(x) case ESOP2Ops::x: return #x`
- L311 _function_ `const char* ToString(ESOPKOps Op)` (scope `RDNA2`)
- L313 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPKOps::x: return #x`
- L391 _function_ `const char* ToString(ESOPPOps Op)` (scope `RDNA2`)
- L393 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPPOps::x: return #x`
- L460 _function_ `const char* ToString(ESMEMOps Op)` (scope `RDNA2`)
- L462 _macro_ `#define OP_TO_STRING_CASE(x) case ESMEMOps::x: return #x`
- L511 _function_ `const char* ToString(ESOPCOps Op)` (scope `RDNA2`)
- L513 _macro_ `#define OP_TO_STRING_CASE(x) case ESOPCOps::x: return #x`
- L627 _function_ `const char* ToString(EVOP1Ops Op)` (scope `RDNA2`)
- L629 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP1Ops::x: return #x`
- L747 _function_ `const char* ToString(EVOP3POps Op)` (scope `RDNA2`)
- L749 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP3POps::x: return #x`
- L836 _function_ `const char* ToString(EVOP2Ops Op)` (scope `RDNA2`)
- L838 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP2Ops::x: return #x`
- L1093 _function_ `const char* ToString(EVOPCOps Op)` (scope `RDNA2`)
- L1095 _macro_ `#define OP_TO_STRING_CASE(x) case EVOPCOps::x: return #x`
- L1415 _function_ `inline bool IsVOP3BEncoding(EVOP3ABOps Op)` (scope `RDNA2`)
- L1435 _function_ `const char* ToString(EVOP3ABOps Op)` (scope `RDNA2`)
- L1437 _macro_ `#define OP_TO_STRING_CASE(x) case EVOP3ABOps::x: return #x`
- L1570 _function_ `const char* ToString(EVINTERPOps Op)` (scope `RDNA2`)
- L1572 _macro_ `#define OP_TO_STRING_CASE(x) case EVINTERPOps::x: return #x`
- L1685 _function_ `const char* ToString(EMIMGOps Op)` (scope `RDNA2`)
- L1687 _macro_ `#define OP_TO_STRING_CASE(x) case EMIMGOps::x: return #x`
- L1872 _function_ `const char* ToString(EMUBUFOps Op)` (scope `RDNA2`)
- L1874 _macro_ `#define OP_TO_STRING_CASE(x) case EMUBUFOps::x: return #x`
- L1980 _function_ `const char* ToString(EMTBUFOps Op)` (scope `RDNA2`)
- L1982 _macro_ `#define OP_TO_STRING_CASE(x) case EMTBUFOps::x: return #x`
- L2067 _function_ `const char* ToString(EFLATOps Op)` (scope `RDNA2`)
- L2069 _macro_ `#define OP_TO_STRING_CASE(x) case EFLATOps::x: return #x`
- L2160 _function_ `const char* ToString(ESCRATCHOps Op)` (scope `RDNA2`)
- L2162 _macro_ `#define OP_TO_STRING_CASE(x) case ESCRATCHOps::x: return #x`
- L2322 _function_ `const char* ToString(ELDSGDSOps Op)` (scope `RDNA2`)
- L2324 _macro_ `#define OP_TO_STRING_CASE(x) case ELDSGDSOps::x: return #x`
- L2519 _function_ `const char* ToString(EGLOBALOps Op)` (scope `RDNA2`)
- L2521 _macro_ `#define OP_TO_STRING_CASE(x) case EGLOBALOps::x: return #x`
- L2589 _function_ `inline bool HasTrailingLiteral(RDNA2::EVOP2Ops Op)` (scope `RDNA2`)
- L2606 _function_ `void PrintSMEM(const FInstSMEM& Inst)` (scope `RDNA2`)
- L2612 _function_ `void PrintSOP1(const FInstSOP1& Inst)` (scope `RDNA2`)
- L2618 _function_ `void PrintSOP2(const FInstSOP2& Inst)` (scope `RDNA2`)
- L2624 _function_ `void PrintSOPP(const FInstSOPP& Inst)` (scope `RDNA2`)
- L2630 _function_ `void PrintSOPC(const FInstSOPC& Inst)` (scope `RDNA2`)
- L2636 _function_ `void PrintSOPK(const FInstSOPK& Inst)` (scope `RDNA2`)
- L2642 _function_ `void PrintMIMG(const FInstMIMG& Inst)` (scope `RDNA2`)
- L2648 _function_ `void PrintVINTERP(const FInstVINTERP& Inst)` (scope `RDNA2`)
- L2654 _function_ `void PrintVOP1(const FInstVOP1& Inst)` (scope `RDNA2`)
- L2660 _function_ `void PrintVOP2(const FInstVOP2& Inst)` (scope `RDNA2`)
- L2666 _function_ `void PrintVOP3A(const FInstVOP3A& Inst)` (scope `RDNA2`)
- L2696 _function_ `void PrintVOP3B(const FInstVOP3B& Inst)` (scope `RDNA2`)
- L2702 _function_ `void PrintVOP3P(const FInstVOP3P& Inst)` (scope `RDNA2`)
- L2708 _function_ `void PrintVOPC(const FInstVOPC& Inst)` (scope `RDNA2`)
- L2714 _function_ `void PrintLDSGDS(const FInstLDSGDS& Inst)` (scope `RDNA2`)
- L2720 _function_ `void PrintMUBUF(const FInstMUBUF& Inst)` (scope `RDNA2`)
- L2726 _function_ `void PrintMTBUF(const FInstMTBUF& Inst)` (scope `RDNA2`)
- L2732 _function_ `void PrintEXPORT(const FInstEXPORT& Inst)` (scope `RDNA2`)
- L2737 _function_ `void PrintFLAT(const FInstFSG& Inst)` (scope `RDNA2`)
- L2743 _function_ `void PrintSCRATCH(const FInstFSG& Inst)` (scope `RDNA2`)
- L2749 _function_ `void PrintGLOBAL(const FInstFSG& Inst)` (scope `RDNA2`)
- L2755 _function_ `void PrintFSG(const FInstFSG& Inst)` (scope `RDNA2`)

### `Source/Developer/ShaderCompilerCommon/Private/ISAParser/RDNA_Common.h` (Private)


#### enum `EInstructionType`  
`enum class EInstructionType : uint8`  
_L32-54_
- L34 _public enumerator_ `SOP2`
- L35 _public enumerator_ `SOPK`
- L36 _public enumerator_ `SOP1`
- L37 _public enumerator_ `SOPC`
- L38 _public enumerator_ `SOPP`
- L39 _public enumerator_ `SMEM`
- L40 _public enumerator_ `VOP2`
- L41 _public enumerator_ `VOP1`
- L42 _public enumerator_ `VOP3`
- L43 _public enumerator_ `VOPC`
- L44 _public enumerator_ `VOP3P`
- L45 _public enumerator_ `VINTERP`
- L46 _public enumerator_ `LDSGDS`
- L47 _public enumerator_ `MUBUF`
- L48 _public enumerator_ `MTBUF`
- L49 _public enumerator_ `MIMG`
- L50 _public enumerator_ `EXPORT`
- L51 _public enumerator_ `FSG`
- L53 _public enumerator_ `UNKNOWN`

#### struct `FInstSOP2`  
`struct FInstSOP2`  
_L56-63_
- L58 _public member_ `uint32 SSRC0 : 8;`
- L59 _public member_ `uint32 SSRC1 : 8;`
- L60 _public member_ `uint32 SDST : 7;`
- L61 _public member_ `uint32 OP : 7;`
- L62 _public member_ `uint32 ID : 2;`

#### struct `FInstSOPK`  
`struct FInstSOPK`  
_L65-71_
- L67 _public member_ `uint32 SIMM16 : 16;`
- L68 _public member_ `uint32 SDST : 7;`
- L69 _public member_ `uint32 OP : 5;`
- L70 _public member_ `uint32 ID : 4;`

#### struct `FInstSOP1`  
`struct FInstSOP1`  
_L73-79_
- L75 _public member_ `uint32 SSRC0 : 8;`
- L76 _public member_ `uint32 OP : 8;`
- L77 _public member_ `uint32 SDST : 7;`
- L78 _public member_ `uint32 ID : 9;`

#### struct `FInstSOPC`  
`struct FInstSOPC`  
_L81-87_
- L83 _public member_ `uint32 SSRC0 : 8;`
- L84 _public member_ `uint32 SSRC1 : 8;`
- L85 _public member_ `uint32 OP : 7;`
- L86 _public member_ `uint32 ID : 9;`

#### struct `FInstSOPP`  
`struct FInstSOPP`  
_L89-94_
- L91 _public member_ `uint32 SIMM16 : 16;`
- L92 _public member_ `uint32 OP : 7;`
- L93 _public member_ `uint32 ID : 9;`

#### struct `FInstSMEM`  
`struct FInstSMEM`  
_L96-110_
- L98 _public member_ `uint32 SBASE : 6;`
- L99 _public member_ `uint32 SDATA : 7;`
- L100 _public member_ `uint32 UNUSED1 : 1;`
- L101 _public member_ `uint32 DLC : 1;`
- L102 _public member_ `uint32 UNUSED2 : 1;`
- L103 _public member_ `uint32 GLC : 1;`
- L104 _public member_ `uint32 UNUSED3 : 1;`
- L105 _public member_ `uint32 OP : 8;`
- L106 _public member_ `uint32 ID : 6;`
- L107 _public member_ `int32 OFFSET : 21;` — signed
- L108 _public member_ `uint32 UNUSED4 : 4;`
- L109 _public member_ `uint32 SOFFSET : 7;`

#### struct `FInstVOP2`  
`struct FInstVOP2`  
_L112-119_
- L114 _public member_ `uint32 SRC0 : 9;`
- L115 _public member_ `uint32 VSRC1 : 8;`
- L116 _public member_ `uint32 VDST : 8;`
- L117 _public member_ `uint32 OP : 6;`
- L118 _public member_ `uint32 ID : 1;`

#### struct `FInstVOP3A`  
`struct FInstVOP3A`  
_L121-134_
- L123 _public member_ `uint32 VDST : 8;`
- L124 _public member_ `uint32 ABS : 3;`
- L125 _public member_ `uint32 OP_SEL : 4;`
- L126 _public member_ `uint32 CLMP : 1;`
- L127 _public member_ `uint32 OP : 10;`
- L128 _public member_ `uint32 ID : 6;`
- L129 _public member_ `uint32 SRC0 : 9;`
- L130 _public member_ `uint32 SRC1 : 9;`
- L131 _public member_ `uint32 SRC2 : 9;`
- L132 _public member_ `uint32 OMOD : 2;`
- L133 _public member_ `uint32 NEG : 3;`

#### struct `FInstVOP3B`  
`struct FInstVOP3B`  
_L136-148_
- L138 _public member_ `uint32 VDST : 8;`
- L139 _public member_ `uint32 SDST : 7;`
- L140 _public member_ `uint32 CLMP : 1;`
- L141 _public member_ `uint32 OP : 10;`
- L142 _public member_ `uint32 ID : 6;`
- L143 _public member_ `uint32 SRC0 : 9;`
- L144 _public member_ `uint32 SRC1 : 9;`
- L145 _public member_ `uint32 SRC2 : 9;`
- L146 _public member_ `uint32 OMOD : 2;`
- L147 _public member_ `uint32 NEG : 3;`

#### struct `FInstVOP3`  
`struct FInstVOP3`  
_L150-158_
- L157 _public member_ `Encoding;`

#### union `FInstVOP3::FEncoding`  
`union FEncoding`  
_L152-156_
- L154 _public member_ `FInstVOP3A VOP3A;`
- L155 _public member_ `FInstVOP3B VOP3B;`

#### struct `FInstVOP1`  
`struct FInstVOP1`  
_L160-166_
- L162 _public member_ `uint32 SRC0 : 9;`
- L163 _public member_ `uint32 OP : 8;`
- L164 _public member_ `uint32 VDST : 8;`
- L165 _public member_ `uint32 ID : 7;`

#### struct `FInstVOPC`  
`struct FInstVOPC`  
_L168-174_
- L170 _public member_ `uint32 SRC0 : 9;`
- L171 _public member_ `uint32 VSRC : 8;`
- L172 _public member_ `uint32 OP : 8;`
- L173 _public member_ `uint32 ID : 7;`

#### struct `FInstVOP3P`  
`struct FInstVOP3P`  
_L176-191_
- L178 _public member_ `uint32 VDST : 8;`
- L179 _public member_ `uint32 NEG_HI : 3;`
- L180 _public member_ `uint32 OP_SEL : 3;`
- L181 _public member_ `uint32 OP_SEL_HI : 1;`
- L182 _public member_ `uint32 CLMP : 1;`
- L183 _public member_ `uint32 OP : 7;`
- L184 _public member_ `uint32 Unused : 3;`
- L185 _public member_ `uint32 ID : 6;`
- L186 _public member_ `uint32 SRC0 : 9;`
- L187 _public member_ `uint32 SRC1 : 9;`
- L188 _public member_ `uint32 SRC2 : 9;`
- L189 _public member_ `uint32 OP_SEL_HI_2 : 2;`
- L190 _public member_ `uint32 NEG : 3;`

#### struct `FInstVINTERP`  
`struct FInstVINTERP`  
_L193-201_
- L195 _public member_ `uint32 VSRC : 8;`
- L196 _public member_ `uint32 ATTR_CHAN : 2;`
- L197 _public member_ `uint32 ATTR : 6;`
- L198 _public member_ `uint32 OP : 2;`
- L199 _public member_ `uint32 VDST : 8;`
- L200 _public member_ `uint32 ID : 6;`

#### struct `FInstLDSGDS`  
`struct FInstLDSGDS`  
_L203-215_
- L205 _public member_ `uint32 OFFSET0 : 8;`
- L206 _public member_ `uint32 OFFSET1 : 8;`
- L207 _public member_ `uint32 UNUSED : 1;`
- L208 _public member_ `uint32 GDS : 1;`
- L209 _public member_ `uint32 OP : 8;`
- L210 _public member_ `uint32 ID : 6;`
- L211 _public member_ `uint32 ADDR : 8;`
- L212 _public member_ `uint32 DATA0 : 8;`
- L213 _public member_ `uint32 DATA1 : 8;`
- L214 _public member_ `uint32 VDST : 8;`

#### struct `FInstMUBUF`  
`struct FInstMUBUF`  
_L217-236_
- L219 _public member_ `uint32 OFFSET : 12;`
- L220 _public member_ `uint32 OFFEN : 1;`
- L221 _public member_ `uint32 IDXEN : 1;`
- L222 _public member_ `uint32 GLC : 1;`
- L223 _public member_ `uint32 DLC : 1;`
- L224 _public member_ `uint32 LDS : 1;`
- L225 _public member_ `uint32 UNUSED0 : 1;`
- L226 _public member_ `uint32 OP : 7;`
- L227 _public member_ `uint32 OPM : 1;`
- L228 _public member_ `uint32 ID : 6;`
- L229 _public member_ `uint32 VADDR : 8;`
- L230 _public member_ `uint32 VDATA : 8;`
- L231 _public member_ `uint32 SRSRC : 5;`
- L232 _public member_ `uint32 UNUSED1 : 1;`
- L233 _public member_ `uint32 SLC : 1;`
- L234 _public member_ `uint32 TFE : 1;`
- L235 _public member_ `uint32 SOFFSET : 8;`

#### struct `FInstMTBUF`  
`struct FInstMTBUF`  
_L238-255_
- L240 _public member_ `uint32 OFFSET : 12;`
- L241 _public member_ `uint32 OFFEN : 1;`
- L242 _public member_ `uint32 IDXEN : 1;`
- L243 _public member_ `uint32 GLC : 1;`
- L244 _public member_ `uint32 DLC : 1;`
- L245 _public member_ `uint32 OP : 3;`
- L246 _public member_ `uint32 FORMAT : 7;`
- L247 _public member_ `uint32 ID : 6;`
- L248 _public member_ `uint32 VADDR : 8;`
- L249 _public member_ `uint32 VDATA : 8;`
- L250 _public member_ `uint32 SRSRC : 5;`
- L251 _public member_ `uint32 OPM : 1;`
- L252 _public member_ `uint32 SLC : 1;`
- L253 _public member_ `uint32 TFE : 1;`
- L254 _public member_ `uint32 SOFFSET : 8;`

#### struct `FInstMIMG`  
`struct FInstMIMG`  
_L257-293_
- L259 _public member_ `uint32 OPM : 1;`
- L260 _public member_ `uint32 NSA : 2;`
- L261 _public member_ `uint32 DIM : 3;`
- L262 _public member_ `uint32 UNUSED0 : 1;`
- L263 _public member_ `uint32 DLC : 1;`
- L264 _public member_ `uint32 DMASK : 4;`
- L265 _public member_ `uint32 UNRM : 1;`
- L266 _public member_ `uint32 GLC : 1;`
- L267 _public member_ `uint32 UNUSED1 : 1;`
- L268 _public member_ `uint32 R128 : 1;`
- L269 _public member_ `uint32 TFE : 1;`
- L270 _public member_ `uint32 LWE : 1;`
- L271 _public member_ `uint32 OP : 7;`
- L272 _public member_ `uint32 SLC : 1;`
- L273 _public member_ `uint32 ID : 6;`
- L274 _public member_ `uint32 VADDR : 8;`
- L275 _public member_ `uint32 VDATA : 8;`
- L276 _public member_ `uint32 SRSRC : 5;`
- L277 _public member_ `uint32 SSAMP : 5;`
- L278 _public member_ `uint32 UNUSED2 : 4;`
- L279 _public member_ `uint32 A16 : 1;`
- L280 _public member_ `uint32 D16 : 1;`
- L281 _public member_ `uint32 ADDR1 : 8;`
- L282 _public member_ `uint32 ADDR2 : 8;`
- L283 _public member_ `uint32 ADDR3 : 8;`
- L284 _public member_ `uint32 ADDR4 : 8;`
- L285 _public member_ `uint32 ADDR5 : 8;`
- L286 _public member_ `uint32 ADDR6 : 8;`
- L287 _public member_ `uint32 ADDR7 : 8;`
- L288 _public member_ `uint32 ADDR8 : 8;`
- L289 _public member_ `uint32 ADDR9 : 8;`
- L290 _public member_ `uint32 ADDR10 : 8;`
- L291 _public member_ `uint32 ADDR11 : 8;`
- L292 _public member_ `uint32 ADDR12 : 8;`

#### struct `FInstEXPORT`  
`struct FInstEXPORT`  
_L295-308_
- L297 _public member_ `uint32 EN : 4;`
- L298 _public member_ `uint32 TARGET : 6;`
- L299 _public member_ `uint32 COMPR : 1;`
- L300 _public member_ `uint32 DONE : 1;`
- L301 _public member_ `uint32 VM : 1;`
- L302 _public member_ `uint32 UNUSED : 13;`
- L303 _public member_ `uint32 ID : 6;`
- L304 _public member_ `uint32 VSRC0 : 8;`
- L305 _public member_ `uint32 VSRC1 : 8;`
- L306 _public member_ `uint32 VSRC2 : 8;`
- L307 _public member_ `uint32 VSRC3 : 8;`

#### struct `FInstFSG`  
`struct FInstFSG`  
_L310-326_
- L312 _public member_ `uint32 OFFSET : 12;`
- L313 _public member_ `uint32 DLC : 1;`
- L314 _public member_ `uint32 LDS : 1;`
- L315 _public member_ `uint32 SEG : 2;`
- L316 _public member_ `uint32 GLC : 1;`
- L317 _public member_ `uint32 SLC : 1;`
- L318 _public member_ `uint32 OP : 7;`
- L319 _public member_ `uint32 UNUSED0 : 1;`
- L320 _public member_ `uint32 ID : 6;`
- L321 _public member_ `uint32 ADDR8 : 8;`
- L322 _public member_ `uint32 DATA : 8;`
- L323 _public member_ `uint32 SADDR : 7;`
- L324 _public member_ `uint32 UNUSED1 : 1;`
- L325 _public member_ `uint32 VDST : 8;`

#### struct `FDPP16`  
`struct FDPP16`  
_L328-341_
- L330 _public member_ `uint32 SRC0 : 8;`
- L331 _public member_ `uint32 DPPCTRL : 9;`
- L332 _public member_ `uint32 UNUSED : 1;`
- L333 _public member_ `uint32 FI : 1;`
- L334 _public member_ `uint32 BC : 1;`
- L335 _public member_ `uint32 SRC0_NEG : 1;`
- L336 _public member_ `uint32 SRC0_ABS : 1;`
- L337 _public member_ `uint32 SRC1_NEG : 1;`
- L338 _public member_ `uint32 SRC1_ABS : 1;`
- L339 _public member_ `uint32 BANK_MASK : 4;`
- L340 _public member_ `uint32 ROW_MASK : 4;`

#### Free symbols / members of external scopes

- L7 _variable_ `static const uint32 SOP2Header = 0b10;` — Then 7bits for Op
- L8 _variable_ `static const uint32 SOPKHeader = 0b1011;` — Then 5bits for Op
- L9 _variable_ `static const uint32 SOP1Header = 0b101111101;`
- L10 _variable_ `static const uint32 SOPCHeader = 0b101111110;`
- L11 _variable_ `static const uint32 SOPPHeader = 0b101111111;`
- L12 _variable_ `static const uint32 SMEMHeader = 0b111101;`
- L13 _variable_ `static const uint32 VOP2Header = 0b0;` — Then 6bits for Op
- L14 _variable_ `static const uint32 VOP1Header = 0b0111111;`
- L15 _variable_ `static const uint32 VOP3Header = 0b110101;`
- L16 _variable_ `static const uint32 VOPCHeader = 0b0111110;`
- L17 _variable_ `static const uint32 VOP3PHeader = 0b110011;`
- L18 _variable_ `static const uint32 VINTERPHeader = 0b110010;`
- L19 _variable_ `static const uint32 LDSGDSHeader = 0b110110;`
- L20 _variable_ `static const uint32 MUBUFHeader = 0b111000;`
- L21 _variable_ `static const uint32 MTBUFHeader = 0b111010;`
- L22 _variable_ `static const uint32 MIMGHeader = 0b111100;`
- L23 _variable_ `static const uint32 EXPORTHeader = 0b111110;`
- L24 _variable_ `static const uint32 FSGHeader = 0b110111;`
- L26 _variable_ `static const uint32 Operand_DPP8 = 233;`
- L27 _variable_ `static const uint32 Operand_DPP8FI = 234;`
- L28 _variable_ `static const uint32 Operand_DPP16 = 250;`
- L29 _variable_ `static const uint32 Operand_SDWA = 249;`
- L30 _variable_ `static const uint32 Operand_Literal = 255;`
- L343 _function_ `inline uint32 GetAdvanceAmount(EInstructionType InstructionType)`
- L372 _function_ `inline bool IsSOP2(const uint32* Code, uint32& AdvanceAmount)`
- L388 _function_ `inline bool IsSOPK(const uint32* Code, uint32& AdvanceAmount)`
- L402 _function_ `inline bool IsSOP1(const uint32* Code, uint32& AdvanceAmount)`
- L418 _function_ `inline bool IsSOPC(const uint32* Code, uint32& AdvanceAmount)`
- L434 _function_ `inline bool IsSOPP(const uint32* Code, uint32& AdvanceAmount)`
- L445 _function_ `inline bool IsSMEM(const uint32* Code, uint32& AdvanceAmount)`
- L456 _function_ `inline bool IsVOP2(const uint32* Code, uint32& AdvanceAmount)`
- L471 _function_ `inline bool IsVOP3(const uint32* Code, uint32& AdvanceAmount)`
- L489 _function_ `inline bool IsVOP1(const uint32* Code, uint32& AdvanceAmount)`
- L504 _function_ `inline bool IsVOPC(const uint32* Code, uint32& AdvanceAmount)`
- L519 _function_ `inline bool IsVOP3P(const uint32* Code, uint32& AdvanceAmount)`
- L530 _function_ `inline bool IsVINTERP(const uint32* Code, uint32& AdvanceAmount)`
- L541 _function_ `inline bool IsLDSGDS(const uint32* Code, uint32& AdvanceAmount)`
- L552 _function_ `inline bool IsMUBUF(const uint32* Code, uint32& AdvanceAmount)`
- L563 _function_ `inline bool IsMTBUF(const uint32* Code, uint32& AdvanceAmount)`
- L574 _function_ `inline bool IsMIMG(const uint32* Code, uint32& AdvanceAmount)`
- L586 _function_ `inline bool IsEXPORT(const uint32* Code, uint32& AdvanceAmount)`
- L597 _function_ `inline bool IsFSG(const uint32* Code, uint32& AdvanceAmount)`
- L608 _function_ `inline EInstructionType DecodeInstructionType(const uint32* Code, uint32& AdvanceAmount)`
- L631 _function_ `inline const char* ToString(EInstructionType Inst)`
- L633 _macro_ `#define OP_TO_STRING_CASE(x) case EInstructionType::x: return #x`

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCECommon.h` (Private)


#### struct `UE::ShaderMinifier::SDCE::TMutableStringView`  
`template<typename T> struct TMutableStringView`  
_L20-47_
- desc: Simple mutable view
- L22 _public function_ `TMutableStringView() : Begin(nullptr), Length(0)`
- L27 _public function_ `TMutableStringView(TString<T>& InView) : Begin(InView.GetCharArray().GetData()), Length(InView.Len())`
- L32 _public function_ `TMutableStringView(T* InBegin, int32 InLength) : Begin(InBegin), Length(InLength)`
- L37 _public function_ `TMutableStringView(T* InBegin) : TMutableStringView(InBegin, TCString<T>::Strlen(InBegin))`
- L42 _public function_ `T* begin() const`
- L43 _public function_ `T* end() const`
- L45 _public member_ `T* Begin;`
- L46 _public member_ `int32 Length;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_SHADER_SDCE_LOG_ALL 0` — Enable logging for debugging
- L10 _macro_ `#define UE_SHADER_SDCE_LOG_STRUCTURAL 0`
- L11 _macro_ `#define UE_SHADER_SDCE_LOG_COMPLEX 0`
- L14 _macro_ `#define UE_SHADER_SDCE_TAGGED_ONLY 0` — If true, only populate symbols for tagged types, speeds up parsing but may miss nested type handling
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L16 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L56 _typedef_ `using FParseCharType = TCHAR;` (scope `UE::ShaderMinifier::SDCE`) — Note that while the minifier parses contents on its ansi sources, SDCE is invoked during actual shader compilation which acts on wide characters. Despite that, we implicitly assume that tokenization segment lookups may operate on their ansi counterpart without accounting for encoding differences (i.e., the wide character is ansi)
- L57 _typedef_ `using FParseViewType = TMutableStringView<FParseCharType>;` (scope `UE::ShaderMinifier::SDCE`)
- L58 _typedef_ `using FParseConstViewType = TStringView<FParseCharType>;` (scope `UE::ShaderMinifier::SDCE`)
- L59 _typedef_ `using FParseStringType = TString<FParseCharType>;` (scope `UE::ShaderMinifier::SDCE`)
- L60 _typedef_ `using FLookupCharType = ANSICHAR;` (scope `UE::ShaderMinifier::SDCE`)
- L61 _typedef_ `using FLookupViewType = TStringView<FLookupCharType>;` (scope `UE::ShaderMinifier::SDCE`)
- L66 _variable_ `static const TCHAR* ShaderMetadataPrefix = TEXT("SDC` (scope `UE::ShaderMinifier::SDCE`) — Shader metadata prefix, e.g., UESHADERMETADATA_SDCE <name>
- L68 _typedef_ `using FMemStackSetAllocator = TSetAllocator<TSparseArrayAllocator<TMemStackAllocator<>, TMemStackAllocator<>>, TMemStackAllocator<>>;` (scope `UE::ShaderMinifier::SDCE`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCEContext.h` (Private)


#### class `UE::ShaderMinifier::SDCE::FContext`  
`class FContext`  
_L16-312_
- desc: Symbolic Dead-Code-Elimination Context Effectively a shallow parser with in-place semantics.
- L22 _public function_ `FContext(const TConstArrayView<FParseConstViewType>& DCESymbols) : SemanticCtx(SymbolCtx)`
- L34 _public function_ `void Analyze(const FParseViewType& Code)` — Parse a given code chunk and generate relevant semantics
- L43 _public function_ `void MinifyInPlace()` — Minify all parsed chunks in-place against their stores
- L119 _private function_ `void VisitStructPrologue(const FSmallStringView& ID)`
- L148 _private function_ `void VisitStructEpilogue()`
- L155 _private function_ `void VisitFunctionPrologue()`
- L169 _private function_ `void VisitFunctionEpilogue()`
- L176 _private function_ `void VisitDeclaration()`
- L183 _private function_ `void VisitDrain(EPrecedence Precedence, const TCHAR* DebugReason)`
- L192 _private function_ `void VisitType(const FSmallStringView& Type)`
- L200 _private function_ `void VisitAlias()`
- L213 _private function_ `void VisitFramePrologue()`
- L219 _private function_ `void VisitFrameEpilogue()`
- L225 _private function_ `void VisitAggregateComposite()`
- L233 _private function_ `void VisitPrimaryMemberAccess(const FSmallStringView& ID)`
- L245 _private function_ `void VisitPrimaryID(const FSmallStringView& ID)`
- L253 _private function_ `void VisitComplexID(const FSmallStringView& ID)`
- L259 _private function_ `void VisitBinary(FToken Op)`
- L269 _private function_ `void VisitStatementPrologue(FParseCharType* Cursor)`
- L277 _private function_ `void VisitStatementEpilogue(FParseCharType* Cursor)`
- L300 _private member_ `FParseCharType* CurrentStatementPrologueCursor = nullptr;` — Statement prologue cursor
- L304 _private member_ `FShallowParser Parser;` — Shared shallow parser
- L307 _private member_ `FSymbolContext SymbolCtx;` — Contexts
- L308 _private member_ `FSemanticContext SemanticCtx;`
- L311 _private member_ `TSet<FConstSmallStringView, FConstSmallStringKeyFuncs, FMemStackSetAllocator> TaggedTypes;` — Actual set of types we're minifying

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L10 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L47 _function_ `` (scope `UE::ShaderMinifier::SDCE::FContext::MinifyInPlace`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCEOpBuffer.h` (Private)


#### struct `UE::ShaderMinifier::SDCE::TOpBuffer`  
`template<typename T, uint32 ChunkSize> struct TOpBuffer`  
_L9-86_
- L12 _public function_ `T& EmplaceUninitialized()` — Emplace a new op
- L31 _public function_ `void Add(const T& Value)` — Add a new chunk value
- L37 _public function_ `const T& operator[](int32 Index) const` — Get an op by its index
- L45 _public function_ `T& operator[](int32 Index)` — Get an op by its index
- L53 _public function_ `bool IsEmpty() const` — Any ops?
- L59 _public function_ `void SetNumNoAlloc(int32 InCount)` — Set the number of ops
- L66 _public function_ `void Empty()` — Clear this buffer
- L72 _public function_ `int32 Num() const` — Number of available ops
- L83 _private member_ `TArray<Chunk*, TMemStackAllocator<>> Chunks;`
- L85 _private member_ `int32 Count = 0;`

#### struct `UE::ShaderMinifier::SDCE::TOpBuffer::Chunk`  
`struct Chunk`  
_L78-81_
- L80 _public member_ `T Ops[ChunkSize];`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L6 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCESemanticContext.h` (Private)


#### enum `UE::ShaderMinifier::SDCE::ESemanticOp`  
`enum class ESemanticOp`  
_L12-22_
- L14 _public enumerator_ `ID`
- L15 _public enumerator_ `Type`
- L16 _public enumerator_ `Access`
- L17 _public enumerator_ `Binary`
- L18 _public enumerator_ `Declare`
- L19 _public enumerator_ `Drain`
- L20 _public enumerator_ `FramePrologue`
- L21 _public enumerator_ `FrameEpilogue`

#### struct `UE::ShaderMinifier::SDCE::FSemanticOp`  
`struct FSemanticOp`  
_L24-48_
- L26 _public member_ `ESemanticOp Type;`
- L27 _public member_ `EPrecedence Precedence;`

#### union `UE::ShaderMinifier::SDCE::FSemanticOp::(anonymous)`  
``  
_L31-47_

#### struct `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a::(anonymous)`  
``  
_L37-39_

#### struct `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a::(anonymous)`  
``  
_L43-46_

#### class `UE::ShaderMinifier::SDCE::FSemanticContext`  
`class FSemanticContext`  
_L57-663_
- desc: Simple semantic evaluator, reduces a set of semantic operations by their natural precedence with a naive shunting yard approach. This was picked over an "AST" like structure to keep things as lightweight as possible.
- L60 _public function_ `FSemanticContext(FSymbolContext& SymCtx) : SymCtx(SymCtx)`
- L66 _public function_ `void Empty()` — Clear the context
- L72 _public function_ `FSemanticOp& PushOp()` — Create a new op
- L77 _public function_ `const FSemanticOp& GetOp(int32 Index) const`
- L82 _public function_ `int32 OpCount() const`
- L88 _public function_ `void Evaluate(const FParseViewType& StatementRegion)` — Evaluate all pushed ops
- L222 _public function_ `void RemoveRealizedLoads(const FValueSpan& Span)` — Remove all the realized from a span of values
- L266 _private function_ `void Reduce()` — Reduce the top most op
- L492 _private function_ `void PushOp(const FReduceOp& Op)` — Push a new op
- L516 _private function_ `bool IsTrivialNonCompoundAssignment()`
- L589 _private function_ `FSymbol* ResolveValueSymbol(const FStackValue& Value) const` — Helper, get the symbol of a stack value
- L605 _private function_ `FSymbol* ResolveValueSymbolReadSite(const FStackValue& Value)` — Helper, get the symbol of a stack value
- L632 _private function_ `void PushValue(const FStackValue& Value)` — Helper, push a value to the stack
- L639 _private function_ `void PushUnresolvedValue(const FValueSpan& Span)` — Helper, push an unresolved value
- L648 _private member_ `TOpBuffer<FSemanticOp, 128> OpBuffer;` — Current op buffer
- L651 _private member_ `TArray<FStackValue, TInlineAllocator<64, TMemStackAllocator<>>> ValueStack;` — Evaluation stacks
- L652 _private member_ `TArray<FReduceOp, TInlineAllocator<64, TMemStackAllocator<>>> OpStack;`
- L653 _private member_ `TArray<FFrameHead, TInlineAllocator<64, TMemStackAllocator<>>> FrameStack;`
- L656 _private member_ `TOpBuffer<FStackValue, 1024> ValueHistory;` — Evaluation value history, not a stack
- L659 _private member_ `FParseViewType CurrentStatementRegion;` — Current statement code region
- L662 _private member_ `FSymbolContext& SymCtx;`

#### struct `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp`  
`struct FReduceOp`  
_L242-260_
- desc: Internal reduction op
- L244 _public member_ `ESemanticOp Type;`
- L245 _public member_ `EPrecedence Precedence;`

#### union `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::(anonymous)`  
``  
_L249-259_

#### struct `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a::(anonymous)`  
``  
_L251-253_

#### struct `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a::(anonymous)`  
``  
_L256-258_

#### struct `UE::ShaderMinifier::SDCE::FSemanticContext::FStackValue`  
`struct FStackValue`  
_L566-579_
- desc: Value on the stack
- L569 _public member_ `FSymbol* Symbol = nullptr;` — Optional, resolved symbol
- L572 _public member_ `FSmallStringView ID{};` — If unresolved, identifer of this value
- L575 _public member_ `FValueSpan Span;` — The effectively value span this represents
- L578 _public member_ `bool bIsReadSite = false;` — Should this be treated as a read site?

#### struct `UE::ShaderMinifier::SDCE::FSemanticContext::FFrameHead`  
`struct FFrameHead`  
_L582-586_
- desc: Frame counters for drains
- L584 _public member_ `int32 OpHead = 0;`
- L585 _public member_ `int32 ValueHead = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L10 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L33 _member_ `FSmallStringView ID;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a`) — ESemanticOp::ID
- L38 _member_ `FToken Op;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a::__anon1c99b31b0208`)
- L39 _member_ `} Binary;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a`)
- L44 _member_ `int32 Count;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a::__anon1c99b31b0308`)
- L45 _member_ `const TCHAR* DebugReason;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a::__anon1c99b31b0308`)
- L46 _member_ `} Drain;` (scope `UE::ShaderMinifier::SDCE::FSemanticOp::__anon1c99b31b010a`)
- L252 _member_ `FToken Op;` (scope `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a::__anon1c99b31b0508`)
- L253 _member_ `} Binary;` (scope `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a`)
- L257 _member_ `int32 Count;` (scope `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a::__anon1c99b31b0608`)
- L258 _member_ `} Drain;` (scope `UE::ShaderMinifier::SDCE::FSemanticContext::FReduceOp::__anon1c99b31b040a`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCEShallowParser.h` (Private)


#### enum `UE::ShaderMinifier::SDCE::EPrecedence`  
`enum class EPrecedence`  
_L11-20_
- desc: Standardized precedence for all operations
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `Primary`
- L15 _public enumerator_ `Access`
- L16 _public enumerator_ `Declare`
- L17 _public enumerator_ `BinaryGeneric`
- L18 _public enumerator_ `BinaryAssign`
- L19 _public enumerator_ `Statement`

#### class `UE::ShaderMinifier::SDCE::FShallowParser`  
`class FShallowParser`  
_L27-1448_
- desc: As per its name, the *shallow* parser doesn't require full program understanding it instead attempts to parse what it can, and treat the rest as "complex". It's up to the visitor to interpret this as it sees fit.
- L30 _public function_ `FShallowParser()`
- L87 _public function_ `template<typename T> void ParseCode(const FParseViewType& Code, T&& Visitor)` — Parse a code chunk, visitor statically invoked
- L197 _private function_ `template<typename F> void WithStatement(FShallowTokenizer& Tk, F&& functor)` — Helper, appends prologue/epilogue around a statement
- L206 _private function_ `void ParseStruct(FShallowTokenizer& Tk)`
- L236 _private function_ `bool ParseBody(FShallowTokenizer& Tk)`
- L246 _private function_ `void ParseBodyInner(FShallowTokenizer& Tk)`
- L254 _private function_ `void ParseStatement(FShallowTokenizer& Tk, bool bConsumeEOS = true)`
- L273 _private function_ `void ParseReturn(FShallowTokenizer& Tk)`
- L287 _private function_ `void ParseDXCPragma(FShallowTokenizer& Tk)`
- L294 _private function_ `bool ParseIf(FShallowTokenizer& Tk)`
- L325 _private function_ `bool ParseWhile(FShallowTokenizer& Tk)`
- L345 _private function_ `bool ParseFor(FShallowTokenizer& Tk)`
- L392 _private function_ `void ParseStatementBody(FShallowTokenizer& Tk)`
- L404 _private function_ `bool ParseSwitch(FShallowTokenizer& Tk)`
- L469 _private function_ `void ParseBreak(FShallowTokenizer& Tk)`
- L474 _private function_ `bool TryParseStatementInside(FShallowTokenizer& Tk)`
- L545 _private function_ `void SkipStatement(FShallowTokenizer& Tk)`
- L562 _private function_ `void MarkIdentifiersAsComplexBase(const FParseViewType& Region)`
- L584 _private function_ `bool TryParseFunction(FShallowTokenizer& TkOuter)`
- L643 _private function_ `bool TryParseDeclaration(FShallowTokenizer& TkOuter, bool bAllowMultiDeclarators = true)`
- L719 _private function_ `bool TryParseType(FShallowTokenizer& Tk, FToken& Type)`
- L742 _private function_ `void TryParseTypePostfix(FShallowTokenizer& TkOuter)`
- L780 _private function_ `bool IsUnaryPrimaryValueModifier(ETokenType Type)`
- L796 _private function_ `bool ParseParenthesis(FShallowTokenizer& Tk)`
- L829 _private function_ `void ParseTernary(FShallowTokenizer& Tk, bool bAllowExpressionCarry = true)`
- L860 _private function_ `bool TryParseExpression(FShallowTokenizer& TkOuter, bool bAllowExpressionCarry = true)`
- L898 _private function_ `bool ParseUnary(FShallowTokenizer& Tk)`
- L904 _private function_ `bool ParseAggregateInitializer(FShallowTokenizer& Tk)`
- L931 _private function_ `bool TryParsePrimary(FShallowTokenizer& TkOuter, bool bAllowCall = true)`
- L969 _private function_ `void PushDrain(int32 Anchor, const TCHAR* Reason)`
- L1076 _private function_ `bool TryParsePrimaryAccessors(FShallowTokenizer& Tk, bool bAllowCall = true)`
- L1167 _private function_ `bool TryParseBinary(FShallowTokenizer& Tk)`
- L1224 _private function_ `bool TryParseUsingAlias(FShallowTokenizer& Tk)`
- L1251 _private function_ `bool TryParseTypedefAlias(FShallowTokenizer& Tk)`
- L1273 _private function_ `void SkipAnnotations(FShallowTokenizer& Tk)`
- L1283 _private function_ `bool SkipTemplate(FShallowTokenizer& Tk)`
- L1300 _private function_ `void SkipTemplateSpecialization(FShallowTokenizer& Tk)`
- L1316 _private function_ `void SkipDeclarationBindings(FShallowTokenizer& Tk)`
- L1330 _private function_ `void SkipQualifiers(FShallowTokenizer& Tk)`
- L1360 _private function_ `FShallowTokenizer Branch(const FShallowTokenizer& Tk)`
- L1367 _private function_ `void Reject(FShallowTokenizer& Tk)`
- L1373 _private function_ `void Accept(FShallowTokenizer& TkOuter, FShallowTokenizer& Tk)`
- L1443 _private member_ `TOpBuffer<FVisitOp, 256> OpBuffer;` — Current visitation buffer
- L1447 _private member_ `TSet<FConstSmallStringView, FConstSmallStringKeyFuncs, FMemStackSetAllocator> TemplatedTypes;` — Tracked templated types

#### enum `UE::ShaderMinifier::SDCE::FShallowParser::EVisitOp`  
`enum class EVisitOp`  
_L1379-1398_
- L1381 _public enumerator_ `ID`
- L1382 _public enumerator_ `ComplexID`
- L1383 _public enumerator_ `Type`
- L1384 _public enumerator_ `Binary`
- L1385 _public enumerator_ `MemberAccess`
- L1386 _public enumerator_ `AggregateComposite`
- L1387 _public enumerator_ `Declaration`
- L1388 _public enumerator_ `StatementPrologue`
- L1389 _public enumerator_ `StatementEpilogue`
- L1390 _public enumerator_ `StructPrologue`
- L1391 _public enumerator_ `StructEpilogue`
- L1392 _public enumerator_ `FunctionPrologue`
- L1393 _public enumerator_ `FunctionEpilogue`
- L1394 _public enumerator_ `FramePrologue`
- L1395 _public enumerator_ `FrameEpilogue`
- L1396 _public enumerator_ `Alias`
- L1397 _public enumerator_ `Drain`

#### struct `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp`  
`struct FVisitOp`  
_L1400-1438_
- L1402 _public member_ `EVisitOp Type;`

#### union `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::(anonymous)`  
``  
_L1406-1437_

#### struct `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::(anonymous)`  
``  
_L1415-1417_

#### struct `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::(anonymous)`  
``  
_L1421-1423_

#### struct `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::(anonymous)`  
``  
_L1427-1430_

#### struct `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::(anonymous)`  
``  
_L1434-1436_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L8 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L309 _function_ `WithStatement(Tk, [&] { TryParseExpression(Tk); });` (scope `UE::ShaderMinifier::SDCE::FShallowParser::ParseIf`)
- L334 _function_ `WithStatement(Tk, [&] { TryParseExpression(Tk); });` (scope `UE::ShaderMinifier::SDCE::FShallowParser::ParseWhile`)
- L617 _function_ `WithStatement(Tk, [&] { TryParseDeclaration(Tk, false); });` (scope `UE::ShaderMinifier::SDCE::FShallowParser::TryParseFunction`)
- L1408 _member_ `FSmallStringView ID;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`) — EVisitOp::ID/ComplexID
- L1411 _member_ `bool bPrivate;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`) — EVisitOp::FramePrologue/FrameEpilogue
- L1416 _member_ `FSmallStringView ID;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::__anon29b11dc90508`)
- L1417 _member_ `} Struct;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`)
- L1422 _member_ `FToken Token;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::__anon29b11dc90608`)
- L1423 _member_ `} Binary;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`)
- L1428 _member_ `const TCHAR* Reason;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::__anon29b11dc90708`)
- L1429 _member_ `EPrecedence Type;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::__anon29b11dc90708`)
- L1430 _member_ `} Drain;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`)
- L1435 _member_ `FParseCharType* Cursor;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a::__anon29b11dc90808`)
- L1436 _member_ `} Statement;` (scope `UE::ShaderMinifier::SDCE::FShallowParser::FVisitOp::__anon29b11dc9040a`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCESymbolContext.h` (Private)


#### enum `UE::ShaderMinifier::SDCE::ESymbolKind`  
`enum class ESymbolKind`  
_L10-17_
- L13 _public enumerator_ `Composite` — Generic composite type, e.g., structs
- L16 _public enumerator_ `Variable` — Declaration symbols

#### struct `UE::ShaderMinifier::SDCE::FSymbol`  
`struct FSymbol`  
_L19-47_
- L22 _public member_ `ESymbolKind Kind;` — Kind of this symbol
- L25 _public member_ `FSmallStringView ID{};` — Name of this symbol
- L28 _public member_ `bool bTagged = false;` — Is this symbol tagged? i.e., can we perform SDCE on it?
- L37 _public member_ `} Variable;`
- L46 _public member_ `} Composite;`

#### struct `UE::ShaderMinifier::SDCE::FSymbol::(anonymous)`  
``  
_L31-37_

#### struct `UE::ShaderMinifier::SDCE::FSymbol::(anonymous)`  
``  
_L40-46_

#### struct `UE::ShaderMinifier::SDCE::FSymbolScope`  
`struct FSymbolScope`  
_L49-56_
- L52 _public member_ `FSymbol* Composite = nullptr;` — Owning composite of this scope
- L55 _public member_ `TMap<FSmallStringView, FSymbol*, FMemStackSetAllocator, FSmallStringKeyFuncs> Symbols;` — All declared symbols within this scope

#### struct `UE::ShaderMinifier::SDCE::FValueSpan`  
`struct FValueSpan`  
_L59-89_
- desc: Value span, represents a range of values
- L61 _public function_ `FValueSpan() : FValueSpan(0, 0)`
- L66 _public function_ `FValueSpan(int32 InBegin, int32 InEnd)`
- L72 _public function_ `FValueSpan operator|(const FValueSpan& RHS) const`
- L80 _public function_ `FValueSpan& operator|=(const FValueSpan& RHS)`
- L87 _public member_ `int32 Begin;`
- L88 _public member_ `int32 End;`

#### struct `UE::ShaderMinifier::SDCE::FMemberStoreSite`  
`struct FMemberStoreSite`  
_L91-109_
- L94 _public member_ `FSymbol* AddressSymbol = nullptr;` — Symbols
- L95 _public member_ `FSymbol* ValueSymbol = nullptr;`
- L98 _public member_ `FValueSpan AddressSpan;` — Value spans
- L99 _public member_ `FValueSpan ValueSpan;`
- L102 _public member_ `bool bVisited = false;` — Has this site been visited? Used for iterative elimination
- L105 _public member_ `bool bIsResolvedToComplex = false;` — Was this determined to be a complex site?
- L108 _public member_ `FSmallStringView AssignmentSite;` — Textual site

#### class `UE::ShaderMinifier::SDCE::FSymbolContext`  
`class FSymbolContext`  
_L111-210_
- L114 _public function_ `FSymbolContext()`
- L121 _public function_ `FSymbol* LinearCompositeFindSymbol(FSymbol* Base, const FSmallStringView& View)` — Find a symbol within a composite
- L140 _public function_ `FSymbol* FindSymbol(const FSmallStringView& View)` — Find a symbol in the current scope
- L178 _public function_ `FSymbol* CreateSymbol(ESymbolKind Kind)` — Create a new symbol
- L186 _public function_ `void AddComplexAccessor(FSmallStringView ID)` — Add a complex accessor to the set
- L199 _public member_ `TArray<FSymbolScope, TMemStackAllocator<>> SymbolStack;` — All symbol stacks
- L202 _public member_ `TSet<FSmallStringView, FSmallStringKeyFuncs, FMemStackSetAllocator> ComplexBaseSet;` — All accessors that we're treating as complex
- L205 _public member_ `TArray<FMemberStoreSite, TMemStackAllocator<>> StoreSites;` — All tracked store sites
- L209 _private member_ `TChunkedArray<FSymbol, 256, TMemStackAllocator<>> Symbols;` — Symbol container

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L8 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L33 _member_ `FSymbol* Type = nullptr;` (scope `UE::ShaderMinifier::SDCE::FSymbol::__anon4afc80dd0108`) — Type of this variable
- L36 _member_ `int32 RealizedLoadCount = 0;` (scope `UE::ShaderMinifier::SDCE::FSymbol::__anon4afc80dd0108`) — Number of realized loads, zero implies safe DCE'ing
- L45 _member_ `TArray<FSymbol*, TMemStackAllocator<>> ContainedSymbols;` (scope `UE::ShaderMinifier::SDCE::FSymbol::__anon4afc80dd0208`) — All symbols within TODO: I really, really don't like bloating all symbols like this

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCEToken.h` (Private)


#### enum `UE::ShaderMinifier::SDCE::ETokenType`  
`enum class ETokenType : uint16_t`  
_L91-106_
- L94 _public enumerator_ `ID` — Standard identifier
- L97 _public enumerator_ `Numeric` — Numeric identifier
- L100 _public enumerator_ `Unknown` — Unknown token
- L104 _public enumerator_ `UE_MINIFIER_SDCE_KEYWORD_TABLE #undef X`

#### struct `UE::ShaderMinifier::SDCE::FToken`  
`struct FToken`  
_L108-126_
- L111 _public function_ `void SetIDNoHash(const FParseViewType& View)` — Set from an identifier
- L119 _public member_ `ETokenType Type;` — DW0
- L120 _public member_ `uint16_t Length;`
- L123 _public member_ `uint32_t XXHash32;` — DW1 Each token inlines the identifier hash, this is faster than doing it on demand
- L125 _public member_ `FParseCharType* Begin;` — DW2-4

#### struct `UE::ShaderMinifier::SDCE::FSmallStringView`  
`struct FSmallStringView`  
_L128-161_
- L131 _public function_ `static FSmallStringView Get(const FToken& Token)` — Get from a token
- L141 _public function_ `static uint32_t Hash(const FParseCharType* Data, uint16 Length)` — Hash a text region
- L149 _public function_ `bool operator==(const FSmallStringView& RHS) const` — Comparator
- L157 _public member_ `FParseCharType* Begin;` — DW0-2
- L159 _public member_ `uint32_t XXHash32;` — DW2
- L160 _public member_ `uint16_t Length;`

#### struct `UE::ShaderMinifier::SDCE::FConstSmallStringView`  
`struct FConstSmallStringView`  
_L163-201_
- L165 _public prototype_ `FConstSmallStringView() = default;`
- L167 _public function_ `FConstSmallStringView(const FSmallStringView& Mutable) : Begin(Mutable.Begin), XXHash32(Mutable.XXHash32), Length(Mutable.Length)`
- L173 _public function_ `static FConstSmallStringView Text(const FParseCharType* Data)` — Create from a text region
- L179 _public function_ `static FConstSmallStringView Text(const FParseCharType* Data, uint16 Length)` — Create from a text region
- L189 _public function_ `bool operator==(const FConstSmallStringView& RHS) const` — Comparator
- L197 _public member_ `const FParseCharType* Begin;` — DW0-2
- L199 _public member_ `uint32_t XXHash32;` — DW2
- L200 _public member_ `uint16_t Length;`

#### struct `UE::ShaderMinifier::SDCE::TSmallStringKeyFuncs`  
`template<typename T> struct TSmallStringKeyFuncs : DefaultKeyFuncs<T>`  
_L204-226_
- inherits: `DefaultKeyFuncs<T>`
- L206 _public function_ `static FORCEINLINE T GetSetKey(T K)`
- L212 _public function_ `template <typename U> static FORCEINLINE T GetSetKey(const TPair<T, U>& P)`
- L217 _public function_ `static FORCEINLINE bool Matches(T A, T B)`
- L222 _public function_ `static FORCEINLINE uint32 GetKeyHash(T Key)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L8 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L11 _macro_ `#define UE_MINIFIER_SDCE_KEYWORD_TABLE \` — Full keyword/segment table
- L103 _macro_ `#define X(N, S) N,` — Segments
- L228 _typedef_ `using FSmallStringKeyFuncs = TSmallStringKeyFuncs<FSmallStringView>;` (scope `UE::ShaderMinifier::SDCE`)
- L229 _typedef_ `using FConstSmallStringKeyFuncs = TSmallStringKeyFuncs<FConstSmallStringView>;` (scope `UE::ShaderMinifier::SDCE`)

### `Source/Developer/ShaderCompilerCommon/Private/SDCE/SDCETokenizer.h` (Private)


#### struct `UE::ShaderMinifier::SDCE::FTokenizerSegmentAnsiNode`  
`struct FTokenizerSegmentAnsiNode`  
_L24-31_
- L27 _public member_ `ETokenType Type = ETokenType::Unknown;` — Token at this ansi node
- L30 _public member_ `FTokenizerSegmentAnsiNode* Trees[TArraySizeFor<FLookupCharType>]{};` — Child nodes

#### struct `UE::ShaderMinifier::SDCE::FTokenizerStatic`  
`struct FTokenizerStatic`  
_L33-139_
- L35 _public function_ `FTokenizerStatic()`
- L75 _public function_ `void AddSegment(ETokenType Type, const FLookupViewType& Value)`
- L96 _public function_ `static void AddCharBit(uint32_t Set[], FLookupCharType Value)`
- L102 _public function_ `static bool GetCharBit(uint32_t Set[], FLookupCharType Value)`
- L108 _public function_ `static bool IsDigit(FLookupCharType Ch)`
- L113 _public function_ `bool IsAlphaNumeric(FLookupCharType Ch)`
- L118 _public function_ `bool IsAlpha(FLookupCharType Ch)`
- L123 _public function_ `bool IsSpace(FLookupCharType Ch)`
- L129 _public member_ `uint32_t AlphaMask [TMask32SizeFor<FLookupCharType>]{};` — Lookup masks
- L130 _public member_ `uint32_t AlphaNumericMask[TMask32SizeFor<FLookupCharType>]{};`
- L131 _public member_ `uint32_t SpaceMask [TMask32SizeFor<FLookupCharType>]{};`
- L134 _public member_ `FTokenizerSegmentAnsiNode SegmentRoot;` — Base segment
- L138 _private member_ `TChunkedArray<FTokenizerSegmentAnsiNode, sizeof(FTokenizerSegmentAnsiNode) * 256> AnsiNodeAllocator;` — Chunked node allocator for coherence

#### struct `UE::ShaderMinifier::SDCE::FShallowTokenizer`  
`struct FShallowTokenizer`  
_L141-471_
- L143 _public prototype_ `FShallowTokenizer() = default;`
- L146 _public function_ `FShallowTokenizer(FShallowTokenizer&& rhs) : Token(rhs.Token), OpHead(rhs.OpHead), Begin(rhs.Begin), End(rhs.End)` — Move constructor
- L152 _public function_ `~FShallowTokenizer()`
- L158 _public function_ `FShallowTokenizer& operator=(FShallowTokenizer&& rhs)`
- L172 _public function_ `FShallowTokenizer Branch() const` — Branch this tokenizer
- L183 _public function_ `void Accept(FShallowTokenizer& RHS)` — Accept another tokenizer onto this
- L194 _public function_ `bool Is(ETokenType Type)` — Check if the current token type is <Type>
- L200 _public function_ `bool IsConsume(ETokenType Type)` — Check if the current token type is <Type> and consume it
- L212 _public function_ `FToken Next()` — Get the current token and proceed
- L221 _public function_ `void NextInternal()` — Actual tokenization internals
- L372 _public function_ `FParseCharType PeekInternal(const FParseCharType* Cursor, uint32 Offset = 0)` — Peek a character
- L383 _public function_ `bool SkipUntil(FParseCharType Ch)` — Skip until we meet a character
- L396 _public function_ `bool SkipUntil(FParseConstViewType ChSet)` — Skip until we meet a set of characters
- L409 _public function_ `void SkipWhitespace()` — Skip all whitespaces
- L436 _public function_ `bool IsEOS()` — Is this end of stream?
- L443 _public function_ `static bool IsOneOf(char Ch, FParseConstViewType ChSet)` — Check if a character is in a set
- L457 _public function_ `uint32_t Offset() const` — Current cursor offset
- L463 _public member_ `FToken Token;` — Current token
- L466 _public member_ `int32 OpHead = 0;` — Operation buffer head, used for parser branching logic
- L469 _public member_ `FParseCharType* Begin = nullptr;` — Cursors
- L470 _public member_ `FParseCharType* End = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L8 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L15 _variable_ `template<typename T> constexpr uint32 TArraySizeFor = 1u << (sizeof(T) * 8);` (scope `UE::ShaderMinifier::SDCE`) — Array size needed for a bit-width
- L19 _variable_ `template<typename T> constexpr uint32 TMask32SizeFor = TArraySizeFor<T> / 32;` (scope `UE::ShaderMinifier::SDCE`) — Mask size needed for a bit-width
- L22 _variable_ `static constexpr int32_t TokenizerInvalidOpHead = INT32_MAX;` (scope `UE::ShaderMinifier::SDCE`) — Invalid operation head
- L38 _macro_ `#define X(N, S) AddSegment(ETokenType::N, S);` — Populate all segments
- L139 _variable_ `} static TokenizerStatic;` (scope `UE::ShaderMinifier::SDCE`)

### `Source/Developer/ShaderCompilerCommon/Public/CrossCompiler.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace CrossCompiler`
- L12 _prototype_ `extern FCriticalSection* GetCrossCompilerLock();` (scope `CrossCompiler`)

### `Source/Developer/ShaderCompilerCommon/Public/CrossCompilerDefinitions.h` (Public)
_(no declarations extracted)_

### `Source/Developer/ShaderCompilerCommon/Public/DXCUtils.inl` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define DXCUTILS_HAS_DXCCREATEINSTANCE 1`
- L13 _function_ `static void DumpDebugBlobDetail(IDxcBlob* Blob, const TCHAR* BlobName) #else static void DumpDebugBlobDetail(IDxcBlob* Blob, const TCHAR* BlobName, TRefCountPtr<IDxcContainerReflection> Reflection) #endif`
- L82 _function_ `static HRESULT RetrieveDebugNameAndBlob(TRefCountPtr<IDxcResult>& CompileResult, FString& OutDebugBlobName, IDxcBlob** OutDebugBlob, DxcShaderHash& ShaderHash)`

### `Source/Developer/ShaderCompilerCommon/Public/DXCWrapper.h` (Public)


#### struct `FDllHandle`  
`struct FDllHandle : public FRefCountedObject`  
_L11-19_
- inherits: `FRefCountedObject`
- L14 _private member_ `void* Handle = nullptr;`
- L17 _public prototype_ `FDllHandle(const TCHAR* InFilename);`
- L18 _public prototype_ `virtual ~FDllHandle();`

#### class `FDxcModuleWrapper`  
`class FDxcModuleWrapper`  
_L21-33_
- L24 _private member_ `uint32 ModuleVersionHash = 0;`
- L26 _protected function_ `FORCEINLINE uint32 GetModuleVersionHash() const`
- L31 _public prototype_ `FDxcModuleWrapper();`
- L32 _public prototype_ `virtual ~FDxcModuleWrapper();`

#### class `FShaderConductorModuleWrapper`  
`class FShaderConductorModuleWrapper : private FDxcModuleWrapper`  
_L35-47_
- inherits: `FDxcModuleWrapper`
- L38 _private member_ `uint32 ModuleVersionHash = 0;`
- L40 _protected function_ `FORCEINLINE uint32 GetModuleVersionHash() const`
- L45 _public prototype_ `FShaderConductorModuleWrapper();`
- L46 _public prototype_ `virtual ~FShaderConductorModuleWrapper();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SHADERCOMPILERCOMMON_API`

### `Source/Developer/ShaderCompilerCommon/Public/HlslccHeaderWriter.h` (Public)


#### class `CrossCompiler::FHlslccHeaderWriter`  
`class FHlslccHeaderWriter`  
_L23-88_
- L27 _public prototype_ `void WriteSourceInfo(const TCHAR* VirtualSourceFilePath, const TCHAR* EntryPointName);`
- L28 _public prototype_ `void WriteCompilerInfo(const TCHAR* CompilerName = TEXT("Shad`
- L30 _public prototype_ `void WriteInputAttribute(const SpvReflectInterfaceVariable& Attribute);`
- L31 _public prototype_ `void WriteInputAttribute(const TCHAR* AttributeName, const TCHAR* TypeSpecifier, int32 Location, bool bLocationPrefix, bool bLocationSuffix);`
- L32 _public prototype_ `void WriteOutputAttribute(const SpvReflectInterfaceVariable& Attribute);`
- L33 _public prototype_ `void WriteOutputAttribute(const TCHAR* AttributeName, const TCHAR* TypeSpecifier, int32 Location, bool bLocationPrefix, bool bLocationSuffix);`
- L34 _public prototype_ `void WriteUniformBlock(const TCHAR* ResourceName, uint32 BindingIndex);`
- L35 _public prototype_ `void WritePackedGlobal(const TCHAR* ResourceName, EPackedTypeName PackedType, uint32 ByteOffset, uint32 ByteSize);`
- L36 _public prototype_ `void WritePackedGlobal(const SpvReflectBlockVariable& Variable);`
- L37 _public prototype_ `void WritePackedUB(uint32 BindingIndex);`
- L38 _public prototype_ `void WritePackedUBField(const TCHAR* ResourceName, uint32 ByteOffset, uint32 ByteSize);`
- L39 _public prototype_ `void WritePackedUB(const FString& UBName, uint32 BindingIndex);`
- L40 _public prototype_ `void WritePackedUBField(const FString& UBName, const TCHAR* ResourceName, uint32 ByteOffset, uint32 ByteSize);`
- L41 _public prototype_ `void WritePackedUBCopy(uint32 SourceCB, uint32 SourceOffset, uint32 DestCBIndex, uint32 DestCBPrecision, uint32 DestOffset, uint32 Size, bool bGroupFlattenedUBs = false);`
- L42 _public prototype_ `void WritePackedUBGlobalCopy(uint32 SourceCB, uint32 SourceOffset, uint32 DestCBIndex, uint32 DestCBPrecision, uint32 DestOffset, uint32 Size, bool bGroupFlattenedUBs = false);`
- L43 _public prototype_ `void WriteSRV(const TCHAR* ResourceName, uint32 BindingIndex, uint32 Count = 1);`
- L44 _public prototype_ `void WriteSRV(const TCHAR* ResourceName, uint32 BindingIndex, uint32 Count, const TArray<FString>& AssociatedResourceNames);`
- L45 _public prototype_ `void WriteUAV(const TCHAR* ResourceName, uint32 BindingIndex, uint32 Count = 1);`
- L46 _public prototype_ `void WriteSamplerState(const TCHAR* ResourceName, uint32 BindingIndex);`
- L47 _public prototype_ `void WriteNumThreads(uint32 NumThreadsX, uint32 NumThreadsY, uint32 NumThreadsZ);`
- L48 _public prototype_ `void WriteAccelerationStructures(const TCHAR* ResourceName, uint32 BindingIndex);`
- L50 _public prototype_ `void WriteSideTable(const TCHAR* ResourceName, uint32 SideTableIndex);`
- L51 _public prototype_ `void WriteArgumentBuffers(uint32 BindingIndex, const TArray<uint32>& ResourceIndices);`
- L54 _public prototype_ `FString ToString() const;` — Returns the finalized meta data.
- L55 _public prototype_ `static EPackedTypeName EncodePackedGlobalType(const SpvReflectTypeDescription& TypeDescription, bool bHalfPrecision = false);`
- L57 _public prototype_ `static void WriteIOAttribute(FString& OutMetaData, const SpvReflectInterfaceVariable& Attribute, bool bIsInput);`
- L60 _private prototype_ `void WriteIOAttribute(FString& OutMetaData, const TCHAR* AttributeName, const TCHAR* TypeSpecifier, int32 Location, bool bLocationPrefix, bool bLocationSuffix);`
- L86 _private member_ `FMetaDataStrings Strings;`

#### struct `CrossCompiler::FHlslccHeaderWriter::FMetaDataStrings`  
`struct FMetaDataStrings`  
_L63-83_
- L65 _public member_ `FString SourceInfo;`
- L66 _public member_ `FString CompilerInfo;`
- L67 _public member_ `FString InputAttributes;`
- L68 _public member_ `FString OutputAttributes;`
- L69 _public member_ `FString UniformBlocks;`
- L70 _public member_ `FString PackedGlobals;`
- L71 _public member_ `TMap<FString, FString> PackedUBs;`
- L72 _public member_ `TMap<FString, FString> PackedUBFields;`
- L73 _public member_ `FString PackedUBCopies;`
- L74 _public member_ `FString PackedUBGlobalCopies;`
- L75 _public member_ `FString SRVs;` — Shader resource views (SRV) and samplers
- L76 _public member_ `FString UAVs;` — Unordered access views (UAV)
- L77 _public member_ `FString SamplerStates;`
- L78 _public member_ `FString NumThreads;`
- L79 _public member_ `FString ExternalTextures;` — External texture resources (Vulkan ES3.1 profile only)
- L80 _public member_ `FString SideTable;` — Side table for additional indices, e.,g. "spvBufferSizeConstants(31)" (Metal only)
- L81 _public member_ `FString ArgumentBuffers;` — Indirect argument buffers (Metal only)
- L82 _public member_ `FString AccelerationStructures;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SHADERCOMPILERCOMMON_API`
- L21 _namespace_ `namespace CrossCompiler`

### `Source/Developer/ShaderCompilerCommon/Public/ISAParser/ISAParser.h` (Public)


#### enum `EInstructionSet`  
`enum class EInstructionSet : uint8`  
_L7-11_
- L9 _public enumerator_ `RDNA1`
- L10 _public enumerator_ `RDNA2`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ISAParser`
- L15 _prototype_ `extern bool HasDerivativeOps(bool& bHasDerivativeOps, const char* Code, uint32 CodeLength, EInstructionSet InstructionSet);` (scope `ISAParser`)

### `Source/Developer/ShaderCompilerCommon/Public/ShaderCompilerCommon.h` (Public)


#### struct `UE::ShaderCompilerCommon::FDebugShaderDataOptions`  
`struct FDebugShaderDataOptions`  
_L103-120_
- L111 _public member_ `const TCHAR* OverrideBaseFilename = nullptr;`
- L112 _public member_ `const TCHAR* FilenamePrefix = nullptr;`
- L115 _public member_ `TArray<FAdditionalOutput> AdditionalOutputs;`
- L117 _public member_ `bool bSourceOnly = false;` — `UE_DEPRECATED(5.7, "bSourceOnly flag on debug data options is no longer supported")`
- L119 _public prototype_ `FString GetDebugShaderPath(const FShaderCompilerInput& Input, const TCHAR* Suffix = nullptr) const;`

#### struct `UE::ShaderCompilerCommon::FDebugShaderDataOptions::FAdditionalOutput`  
`struct FAdditionalOutput`  
_L105-109_
- L107 _public member_ `const TCHAR* BaseFileName;`
- L108 _public member_ `const TCHAR* Data;`

#### class `UE::ShaderCompilerCommon::FBaseShaderFormat`  
`class FBaseShaderFormat : public IShaderFormat`  
_L167-182_
- inherits: `IShaderFormat`
- L170 _public prototype_ `virtual bool PreprocessShader( const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& Environment, FShaderPreprocessOutput& PreprocessOutput) const override;`
- L175 _public prototype_ `virtual void OutputDebugData( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerOutput& Output, FShaderDebugDataContext& Ctx) const override;`
- L181 _public prototype_ `virtual void OutputDebugDataMinimal(const FShaderCompilerInput& Input, FShaderDebugDataContext& Ctx) const override;`

#### enum `EUniformBufferMemberReflectionReason`  
`enum class EUniformBufferMemberReflectionReason`  
_L185-191_
- L187 _public enumerator_ `None = 0`
- L188 _public enumerator_ `NeedsReflection = 1 << 0`
- L189 _public enumerator_ `Bindless = 1 << 1`
- L190 _public enumerator_ `MaterialUBBindError = 1 << 2`

#### struct `FScopedDeclarations`  
`struct UE_DEPRECATED(5.7, "FScopedDeclarations has been moved into internal module HlslParser and is no longer supported as public interface.") FScopedDeclarations`  
_L389-398_
- desc: Structure to hold forward declarations for a specific scope/namespace chain for the HlslParser
- L391 _public function_ `FScopedDeclarations(TConstArrayView<FStringView> InScope, TConstArrayView<FStringView> InSymbols) : Scope(InScope) , Symbols(InSymbols)`
- L396 _public member_ `TConstArrayView<FStringView> Scope;`
- L397 _public member_ `TConstArrayView<FStringView> Symbols;`

#### enum `EShaderParameterStorageClass`  
`enum class UE_DEPRECATED(5.7, "EShaderParameterStorageClass has been moved into internal module HlslParser and is no longer supported as public interface.") EShaderParameterStorageClass`  
_L413-417_
- desc: Shader input/output parameter storage classes. Naming adopted from SPIR-V nomenclature.
- L415 _public enumerator_ `Input`
- L416 _public enumerator_ `Output`

#### enum `EShaderConductorTarget`  
`enum class EShaderConductorTarget`  
_L435-439_
- L437 _public enumerator_ `Dxil`
- L438 _public enumerator_ `Spirv`

#### struct `CrossCompiler::FHlslccHeader`  
`struct FHlslccHeader`  
_L463-562_
- L465 _public prototype_ `FHlslccHeader();`
- L466 _public prototype_ `virtual ~FHlslccHeader() = default;`
- L468 _public prototype_ `bool Read(const ANSICHAR*& ShaderSource, int32 SourceLen);`
- L471 _public function_ `virtual bool ParseCustomHeaderEntries(const ANSICHAR*& ShaderSource)` — After the standard header, different backends can output their own info
- L545 _public member_ `FString Name;`
- L546 _public member_ `TArray<FInOut> Inputs;`
- L547 _public member_ `TArray<FInOut> Outputs;`
- L548 _public member_ `TArray<FAttribute> UniformBlocks;`
- L550 _public member_ `TArray<FPackedGlobal> PackedGlobals;` — TArray<FUniform> Uniforms;
- L551 _public member_ `TArray<FPackedUB> PackedUBs;`
- L552 _public member_ `TArray<FPackedUBCopy> PackedUBCopies;`
- L553 _public member_ `TArray<FPackedUBCopy> PackedUBGlobalCopies;`
- L554 _public member_ `TArray<FSampler> Samplers;`
- L555 _public member_ `TArray<FUAV> UAVs;`
- L556 _public member_ `TArray<FAttribute> SamplerStates;`
- L557 _public member_ `TArray<FAccelerationStructure> AccelerationStructures;`
- L558 _public member_ `uint32 NumThreads[3];`
- L560 _public prototype_ `static bool ReadInOut(const ANSICHAR*& ShaderSource, TArray<FInOut>& OutAttributes);`
- L561 _public prototype_ `static bool ReadCopies(const ANSICHAR*& ShaderSource, bool bGlobals, TArray<FPackedUBCopy>& OutCopies);`

#### struct `CrossCompiler::FHlslccHeader::FInOut`  
`struct FInOut`  
_L476-482_
- L478 _public member_ `FString Type;`
- L479 _public member_ `int32 Index;`
- L480 _public member_ `int32 ArrayCount;`
- L481 _public member_ `FString Name;`

#### struct `CrossCompiler::FHlslccHeader::FAttribute`  
`struct FAttribute`  
_L484-488_
- L486 _public member_ `int32 Index;`
- L487 _public member_ `FString Name;`

#### struct `CrossCompiler::FHlslccHeader::FPackedGlobal`  
`struct FPackedGlobal`  
_L490-496_
- L492 _public member_ `ANSICHAR PackedType;`
- L493 _public member_ `FString Name;`
- L494 _public member_ `int32 Offset;`
- L495 _public member_ `int32 Count;`

#### struct `CrossCompiler::FHlslccHeader::FPackedUB`  
`struct FPackedUB`  
_L502-512_
- L504 _public member_ `FAttribute Attribute;`
- L511 _public member_ `TArray<FMember> Members;`

#### struct `CrossCompiler::FHlslccHeader::FPackedUB::FMember`  
`struct FMember`  
_L505-510_
- L507 _public member_ `FString Name;`
- L508 _public member_ `int32 Offset;`
- L509 _public member_ `int32 Count;`

#### struct `CrossCompiler::FHlslccHeader::FPackedUBCopy`  
`struct FPackedUBCopy`  
_L514-522_
- L516 _public member_ `int32 SourceUB;`
- L517 _public member_ `int32 SourceOffset;`
- L518 _public member_ `int32 DestUB;`
- L519 _public member_ `ANSICHAR DestPackedType;`
- L520 _public member_ `int32 DestOffset;`
- L521 _public member_ `int32 Count;`

#### struct `CrossCompiler::FHlslccHeader::FSampler`  
`struct FSampler`  
_L524-530_
- L526 _public member_ `FString Name;`
- L527 _public member_ `int32 Offset;`
- L528 _public member_ `int32 Count;`
- L529 _public member_ `TArray<FString> SamplerStates;`

#### struct `CrossCompiler::FHlslccHeader::FUAV`  
`struct FUAV`  
_L532-537_
- L534 _public member_ `FString Name;`
- L535 _public member_ `int32 Offset;`
- L536 _public member_ `int32 Count;`

#### struct `CrossCompiler::FHlslccHeader::FAccelerationStructure`  
`struct FAccelerationStructure`  
_L539-543_
- L541 _public member_ `FString Name;`
- L542 _public member_ `int32 Offset = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SHADERCOMPILERCOMMON_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ShaderCompilerCommon` (scope `UE`)
- L19 _variable_ `static constexpr const TCHAR* kUniformBufferConstantBufferPrefix = TEXT("Uni` (scope `UE::ShaderCompilerCommon`)
- L20 _variable_ `static constexpr const TCHAR* kPlatformHashStatName = TEXT("Pla` (scope `UE::ShaderCompilerCommon`)
- L30 _prototype_ `extern bool BuildResourceTableMapping( const FShaderResourceTableMap& ResourceTableMap, const TMap<FString,FUniformBufferEntry>& UniformBufferMap, TBitArray<>& UsedUniformBufferSlots, FShaderParameterMap& ParameterMap, FShaderCompilerResourceTable& OutSRT );` — This function looks for resources specified in ResourceTableMap in the parameter map, adds them to the resource table, and removes them from the parameter map. If a resource is used from a currently unmapped uniform buffer we allocate a slot for it from UsedUniformBufferSlots. Returns false if there's any internal error.
- L39 _prototype_ `extern void CullGlobalUniformBuffers(const TMap<FString, FUniformBufferEntry>& UniformBufferMap, FShaderParameterMap& ParameterMap);` — Culls global uniform buffer entries from the parameter map.
- L47 _prototype_ `extern void BuildResourceTableTokenStream( const TArray<uint32>& InResourceMap, int32 MaxBoundResourceTable, TArray<uint32>& OutTokenStream, bool bGenerateEmptyTokenStreamIfNoResources = false );` — Builds a token stream out of the resource map. The resource map is one of the arrays generated by BuildResourceTableMapping. The token stream is used at runtime to gather resources from tables and bind them to the appropriate slots.
- L55 _prototype_ `extern int16 GetNumUniformBuffersUsed(const FShaderCompilerResourceTable& InSRT);` — Finds the number of used uniform buffers in a resource map
- L57 _namespace_ `namespace UE`
- L57 _namespace_ `namespace ShaderCompilerCommon` (scope `UE`)
- L59 _prototype_ `extern void BuildShaderResourceTable(const FShaderCompilerResourceTable& GenericSRT, FShaderResourceTable& OutSRT, bool bGenerateEmptyTokenStreamIfNoResources = false);` (scope `UE::ShaderCompilerCommon`)
- L61 _prototype_ `extern bool ExecuteShaderPreprocessingSteps( FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& Environment, const FShaderCompilerDefinitions& AdditionalDefines );` (scope `UE::ShaderCompilerCommon`)
- L68 _prototype_ `extern bool ExecuteShaderPreprocessingSteps( FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& Environment );` (scope `UE::ShaderCompilerCommon`)
- L74 _prototype_ `extern FStringView RemoveConstantBufferPrefix(FStringView InName);` (scope `UE::ShaderCompilerCommon`)
- L75 _prototype_ `extern FString RemoveConstantBufferPrefix(const FString& InName);` (scope `UE::ShaderCompilerCommon`)
- L77 _prototype_ `extern bool ValidatePackedResourceCounts(FShaderCompilerOutput& Output, const FShaderCodePackedResourceCounts& PackedResourceCounts);` (scope `UE::ShaderCompilerCommon`)
- L79 _prototype_ `extern void ParseRayTracingEntryPoint(const FString& Input, FString& OutMain, FString& OutAnyHit, FString& OutIntersection);` (scope `UE::ShaderCompilerCommon`)
- L91 _prototype_ `extern void ParseRayTracingEntryPoint(const FStringView& Input, FStringView& OutMain, FStringView& OutAnyHit, FStringView& OutIntersection);` (scope `UE::ShaderCompilerCommon`) — Parses ray tracing shader entry point specification string in one of the following formats: 1) Verbatim single entry point name, e.g. "MainRGS" 2) Complex entry point for ray tracing hit group shaders: a) "closesthit=MainCHS" b) "closesthit=MainCHS anyhit=MainAHS" c) "closesthit=MainCHS anyhit=MainAHS intersection=MainIS" d) "closesthit=MainCHS intersection=MainIS" NOTE: closesthit attribute must always be provided for complex hit group entry points
- L99 _prototype_ `extern bool RemoveDeadCode(FShaderSource& InOutPreprocessedShaderSource, const FString& EntryPoint, TArray<FShaderCompilerError>& OutErrors);` (scope `UE::ShaderCompilerCommon`) — Rewrites a fully preprocessed shader source code, removing any functions or structs that are not reachable from a given entry point or list of symbols. This is a high-level wrapper for UE::ShaderMinifier that should be used in all shader compiler back-ends for consistency. Any errors encountered during parsing or minification are added to OutErrors. InOutPreprocessedShaderSource is replaced with the rewritten code on success and is kept intact on failure.
- L100 _prototype_ `extern bool RemoveDeadCode(FShaderSource& InOutPreprocessedShaderSource, const FString& EntryPoint, TConstArrayView<FStringView> RequiredSymbols, TArray<FShaderCompilerError>& OutErrors);` (scope `UE::ShaderCompilerCommon`)
- L101 _prototype_ `extern bool RemoveDeadCode(FShaderSource& InOutPreprocessedShaderSource, TConstArrayView<FStringView> RequiredSymbols, TArray<FShaderCompilerError>& OutErrors);` (scope `UE::ShaderCompilerCommon`)
- L123 _prototype_ `extern void DumpExtendedDebugShaderData( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerOutput& Output, const UE::ShaderCompilerCommon::FDebugShaderDataOptions& Options = FDebugShaderDataOptions());` (scope `UE::ShaderCompilerCommon`) — `UE_DEPRECATED(5.7, "DumpExtendedDebugShaderData now requires a FShaderDebugDataContext struct parameter")`
- L139 _prototype_ `extern void DumpExtendedDebugShaderData( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerOutput& Output, FShaderDebugDataContext& Ctx, const UE::ShaderCompilerCommon::FDebugShaderDataOptions& Options = FDebugShaderDataOptions());` (scope `UE::ShaderCompilerCommon`) — Dumps extended debug information; including all outputs from DumpDebugShaderData as well as the following: - OutputHash.txt file containing the SHA hash of the shader job output - Diagnostics.txt file containing all errors/warnings encountered for the job (if EShaderDebugInfoFlags::Diagnostics is set on Input.DebugInfoFlags) - InputHash.txt file containing the hash used as the key to the shader job cache (if EShaderDebugInfoFlags::InputHash is set on Input.DebugInfoFlags and specified InputHash is non-empty) - any outputs specified on the AdditionalOutputs array in the Options struct This is intended to be used by shader formats implementing the independent preprocessing API.
- L147 _prototype_ `extern void SerializeEnvironmentFromBase64(FShaderCompilerEnvironment& Env, const FString& DebugUSF);` (scope `UE::ShaderCompilerCommon`) — `UE_DEPRECATED(5.7, "No longer used")`
- L149 _prototype_ `extern FString SerializeEnvironmentToBase64(const FShaderCompilerEnvironment& Env);` (scope `UE::ShaderCompilerCommon`) — `UE_DEPRECATED(5.7, "No longer used")`
- L160 _prototype_ `extern FString GetDebugShaderContents(const FShaderCompilerInput& Input, FStringView PreprocessedSource, const FDebugShaderDataOptions& Options = FDebugShaderDataOptions(), const TCHAR* Suffix = nullptr);` (scope `UE::ShaderCompilerCommon`) — Constructs the modified preprocessed source that would be dumped to a .usf file via DumpDebugShaderData, including the following additions: - comments containing the names and values of all defines when preprocessing this shader - a comment containing the FShaderCompilerInput DebugDescription - any additions performed by the AppendPreSource/AppendPostSource TFunctions @param	Input The input of the compilation job @param	PreprocessedSource The unmodified preprocessed source (used as input to the compilation) @param	Options Options which can change behaviour of the debug dump; see above.
- L165 _prototype_ `extern bool ValidateShaderAgainstKnownIssues(const FString& InSourceCode, TArray<FString>& OutErrors, const TCHAR* InSourceCodeFilename = nullptr);` (scope `UE::ShaderCompilerCommon`) — Runs a few validation steps and reports any known issues such as parameter names that might cause problems on certain backend compilers, especially the old FXC compiler.
- L192 _prototype_ `ENUM_CLASS_FLAGS(EUniformBufferMemberReflectionReason);`
- L194 _prototype_ `EUniformBufferMemberReflectionReason ShouldReflectUniformBufferMembers( const FShaderCompilerInput& Input, FStringView UniformBufferName );`
- L199 _prototype_ `extern void HandleReflectedGlobalConstantBufferMember( const FShaderCompilerInput& Input, const FShaderParameterParser& ShaderParameterParser, FStringView MemberName, uint32 ConstantBufferIndex, int32 ReflectionOffset, int32 ReflectionSize, FShaderCompilerOutput& CompilerOutput );`
- L210 _prototype_ `extern void HandleReflectedGlobalConstantBufferMember( FStringView MemberName, uint32 ConstantBufferIndex, int32 ReflectionOffset, int32 ReflectionSize, FShaderCompilerOutput& CompilerOutput );` — `UE_DEPRECATED(5.8, "HandleReflectedGlobalConstantBufferMember now needs Input and ShaderParameterParser parameters for future features")`
- L218 _prototype_ `extern void HandleReflectedUniformBufferConstantBufferMember( const FShaderCompilerInput& Input, EUniformBufferMemberReflectionReason Reason, FStringView UniformBufferName, int32 UniformBufferSlot, FStringView MemberName, int32 ReflectionOffset, int32 ReflectionSize, FShaderCompilerOutput& CompilerOutput );`
- L229 _prototype_ `extern void HandleReflectedRootConstantBufferMember( const FShaderCompilerInput& Input, const FShaderParameterParser& ShaderParameterParser, FStringView MemberName, int32 ReflectionOffset, int32 ReflectionSize, FShaderCompilerOutput& CompilerOutput );`
- L238 _prototype_ `extern void HandleReflectedRootConstantBuffer( int32 ConstantBufferSize, FShaderCompilerOutput& CompilerOutput );`
- L243 _prototype_ `extern void HandleReflectedUniformBuffer( const FShaderCompilerInput& Input, FStringView UniformBufferName, int32 ReflectionSlot, int32 BaseIndex, int32 BufferSize, FShaderCompilerOutput& CompilerOutput );`
- L252 _function_ `inline void HandleReflectedUniformBuffer(const FShaderCompilerInput& Input, FStringView UniformBufferName, int32 ReflectionSlot, int32 BufferSize, FShaderCompilerOutput& CompilerOutput)`
- L257 _function_ `inline void HandleReflectedUniformBuffer(const FShaderCompilerInput& Input, FStringView UniformBufferName, int32 ReflectionSlot, FShaderCompilerOutput& CompilerOutput)`
- L262 _prototype_ `extern void HandleReflectedShaderResource( FStringView ResourceName, int32 BindOffset, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput );`
- L270 _prototype_ `extern void UpdateStructuredBufferStride( const FShaderCompilerInput& Input, FStringView ResourceName, uint16 BindPoint, uint16 Stride, FShaderCompilerOutput& CompilerOutput );`
- L278 _prototype_ `extern void AddShaderValidationSRVType( uint16 BindPoint, EShaderCodeResourceBindingType TypeDecl, FShaderCompilerOutput& CompilerOutput);`
- L283 _prototype_ `extern void AddShaderValidationUAVType( uint16 BindPoint, EShaderCodeResourceBindingType TypeDecl, FShaderCompilerOutput& CompilerOutput);`
- L288 _prototype_ `extern void AddShaderValidationUBSize( uint16 BindPoint, uint32_t Size, FShaderCompilerOutput& CompilerOutput);`
- L293 _function_ `inline void HandleReflectedShaderResource(FStringView ResourceName, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput)`
- L298 _function_ `inline void HandleReflectedShaderResource(FStringView ResourceName, int32 ReflectionSlot, FShaderCompilerOutput& CompilerOutput)`
- L303 _prototype_ `extern void HandleReflectedShaderUAV( FStringView UAVName, int32 BindOffset, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput );`
- L311 _function_ `inline void HandleReflectedShaderUAV(FStringView UAVName, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput)`
- L316 _function_ `inline void HandleReflectedShaderUAV(FStringView UAVName, int32 ReflectionSlot, FShaderCompilerOutput& CompilerOutput)`
- L321 _prototype_ `extern void HandleReflectedShaderSampler( FStringView SamplerName, int32 BindOffset, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput );`
- L329 _function_ `inline void HandleReflectedShaderSampler(FStringView SamplerName, int32 ReflectionSlot, int32 BindCount, FShaderCompilerOutput& CompilerOutput)`
- L334 _function_ `inline void HandleReflectedShaderSampler(FStringView SamplerName, int32 ReflectionSlot, FShaderCompilerOutput& CompilerOutput)`
- L340 _prototype_ `extern void AddNoteToDisplayShaderParameterStructureOnCppSide( const FShaderParametersMetadata* ParametersStructure, FShaderCompilerOutput& CompilerOutput);` — Adds a note to CompilerOutput.Error about where the shader parameter structure is on C++ side.
- L345 _prototype_ `extern void AddUnboundShaderParameterError( const FShaderCompilerInput& CompilerInput, const FShaderParameterParser& ShaderParameterParser, FStringView ParameterBindingName, FShaderCompilerOutput& CompilerOutput);` — Adds an error to CompilerOutput.Error about a shader parameters that could not be bound.
- L352 _prototype_ `extern void CleanupUniformBufferCode(const FShaderCompilerEnvironment& Environment, FShaderSource& PreprocessedShaderSource);` — Convert generated UniformBuffer code and references into something the shader compilers can use.
- L355 _function_ `template <typename CharType> const CharType* FindMatchingBlock(const CharType* OpeningCharPtr, char OpenChar, char CloseChar)`
- L382 _function_ `template <typename CharType> const CharType* FindMatchingClosingBrace(const CharType* OpeningCharPtr)`
- L384 _prototype_ `extern const TCHAR* ParseHLSLSymbolName(const TCHAR* SearchString, FString& SymboName);`
- L385 _prototype_ `extern void ParseHLSLTypeName(const TCHAR* SearchString, const TCHAR*& TypeNameStartPtr, const TCHAR*& TypeNameEndPtr);`
- L386 _prototype_ `extern FStringView FindNextHLSLDefinitionOfType(FStringView Typename, FStringView StartPos);`
- L401 _function_ `inline bool RemoveUnusedOutputs(...)` — `UE_DEPRECATED(5.7, "RemoveUnusedOutputs() has been moved into internal module HlslParser and is no longer supported as public interface.")`
- L407 _function_ `inline bool RemoveUnusedInputs(...)` — `UE_DEPRECATED(5.7, "RemoveUnusedInputs() has been moved into internal module HlslParser and is no longer supported as public interface.")`
- L421 _function_ `inline bool FindEntryPointParameters(...)` — `UE_DEPRECATED(5.7, "FindEntryPointParameters() has been moved into internal module HlslParser and is no longer supported as public interface.")` — Returns the semantic names of all individual entry point parameters (i.e. all structure fields are inlined)
- L426 _prototype_ `extern bool ConvertFromFP32ToFP16(FString& InOutSourceCode, TArray<FString>& OutErrors);`
- L433 _prototype_ `extern bool InlineFunction(FString& InOutSourceCode, FString& InOutEntryPoint, const FStringView FunctionToInline, TArray<FString>& OutErrors);` — EXPERIMENTAL: Adds a new function to the shader where calls to `FunctionToInline` from `EntryPoint` are inlined using AST manipulation Current limitations: - Inlining from nested compound statement scopes is not supported (currently only trivial call statements in the body are processed) - Functions with return statements cannot be inlined - Multiple levels of inlining are not supported
- L440 _prototype_ `extern void WriteShaderConductorCommandLine(const FShaderCompilerInput& Input, const FString& SourceFilename, EShaderConductorTarget Target);`
- L442 _prototype_ `extern void DumpDebugShaderText(const FShaderCompilerInput& Input, const FString& InSource, const FString& FileExtension);`
- L443 _prototype_ `extern void DumpDebugShaderText(const FShaderCompilerInput& Input, ANSICHAR* InSource, int32 InSourceLength, const FString& FileExtension);`
- L444 _prototype_ `extern void DumpDebugShaderText(const FShaderCompilerInput& Input, ANSICHAR* InSource, int32 InSourceLength, const FString& FileName, const FString& FileExtension);`
- L445 _prototype_ `extern void DumpDebugShaderBinary(const FShaderCompilerInput& Input, void* InData, int32 InDataByteSize, const FString& FileExtension);`
- L446 _prototype_ `extern void DumpDebugShaderBinary(const FShaderCompilerInput& Input, void* InData, int32 InDataByteSize, const FString& FileName, const FString& FileExtension);`
- L447 _prototype_ `extern void DumpDebugShaderDisassembledSpirv(const FShaderCompilerInput& Input, void* InData, int32 InDataByteSize, const FString& FileExtension);`
- L448 _prototype_ `extern void DumpDebugShaderDisassembledDxil(const FShaderCompilerInput& Input, void* InData, int32 InDataByteSize, const FString& FileExtension);`
- L451 _prototype_ `extern void CompileShaderOffline(const FShaderCompilerInput& Input, FShaderCompilerOutput& ShaderOutput, const ANSICHAR* ShaderSource, const int32 SourceSize, bool bVulkanSpirV, const ANSICHAR* VulkanSpirVEntryPoint = nullptr);` — calls 'Offline Compiler' to compile the source code and extract the stats
- L459 _namespace_ `namespace CrossCompiler`
- L461 _prototype_ `extern void ParseHlslccError(TArray<FShaderCompilerError>& OutErrors, const FString& InLine, bool bUseAbsolutePaths = false);` (scope `CrossCompiler`)
- L564 _prototype_ `extern const TCHAR* GetFrequencyName(EShaderFrequency Frequency);` (scope `CrossCompiler`)
- L566 _function_ `inline bool ParseIdentifier(const ANSICHAR*& Str, FString& OutStr)` (scope `CrossCompiler`)
- L582 _function_ `inline bool ParseIdentifier(const TCHAR*& Str, FString& OutStr)` (scope `CrossCompiler`)
- L598 _function_ `inline bool ParseString(const ANSICHAR*& Str, FString& OutStr)` (scope `CrossCompiler`)
- L611 _function_ `inline bool ParseString(const TCHAR*& Str, FString& OutStr)` (scope `CrossCompiler`)
- L624 _function_ `FORCEINLINE bool Match(const ANSICHAR*& Str, ANSICHAR Char)` (scope `CrossCompiler`)
- L635 _function_ `FORCEINLINE bool Match(const TCHAR*& Str, ANSICHAR Char)` (scope `CrossCompiler`)
- L646 _function_ `FORCEINLINE bool Match(const ANSICHAR*& Str, const ANSICHAR* Sub)` (scope `CrossCompiler`)
- L658 _function_ `FORCEINLINE bool Match(const TCHAR*& Str, const TCHAR* Sub)` (scope `CrossCompiler`)
- L671 _function_ `template <typename T> inline bool ParseIntegerNumber(const ANSICHAR*& Str, T& OutNum)` (scope `CrossCompiler`)
- L684 _function_ `template <typename T> inline bool ParseIntegerNumber(const TCHAR*& Str, T& OutNum)` (scope `CrossCompiler`)
- L696 _function_ `inline bool ParseSignedNumber(const ANSICHAR*& Str, int32& OutNum)` (scope `CrossCompiler`)
- L709 _function_ `inline bool ParseSignedNumber(const TCHAR*& Str, int32& OutNum)` (scope `CrossCompiler`)

### `Source/Developer/ShaderCompilerCommon/Public/ShaderConductorContext.h` (Public)


#### struct `CrossCompiler::FHlslShaderModel`  
`struct FHlslShaderModel`  
_L24-61_
- desc: Shader model version for HLSL input language.
- L27 _public member_ `uint16 Major;` — Major shader model version (e.g. 6 in SM6.2).
- L30 _public member_ `uint16 Minor;` — Minor shader model version (e.g. 2 in SM6.2).
- L32 _public function_ `FORCEINLINE bool operator == (const FHlslShaderModel& Rhs) const`
- L37 _public function_ `FORCEINLINE bool operator != (const FHlslShaderModel& Rhs) const`
- L42 _public function_ `FORCEINLINE bool operator < (const FHlslShaderModel& Rhs) const`
- L47 _public function_ `FORCEINLINE bool operator <= (const FHlslShaderModel& Rhs) const`
- L52 _public function_ `FORCEINLINE bool operator > (const FHlslShaderModel& Rhs) const`
- L57 _public function_ `FORCEINLINE bool operator >= (const FHlslShaderModel& Rhs) const`

#### struct `CrossCompiler::FShaderConductorOptions`  
`struct FShaderConductorOptions`  
_L64-137_
- desc: Wrapper structure to pass options descriptor to ShaderConductor. This is mapped to <struct ShaderConductor::Compiler::Options>.
- L66 _public prototype_ `FShaderConductorOptions() = default;`
- L69 _public function_ `FORCEINLINE FShaderConductorOptions(const FShaderCompilerFlags& InCompilerFlags)` — Initializes the options with a call to ApplyCommonCompilerFlags().
- L75 _public member_ `bool bRemoveUnusedGlobals = false;` — Removes unused global variables and resources. This can only be used in the HLSL rewrite pass, i.e. 'RewriteHlslSource'.
- L78 _public member_ `bool bPackMatricesInRowMajor = true;` — Experimental: Decide how a matrix get packed. Default in HLSL is row-major. This will be inverted in the SPIR-V backend to match SPIR-V's column-major default.
- L81 _public member_ `bool bEnable16bitTypes = false;` — Enable 16-bit types, such as half, uint16_t. Requires shader model 6.2+.
- L84 _public member_ `bool bEnableDebugInfo = false;` — Embed debug info into the binary.
- L87 _public member_ `bool bDisableOptimizations = false;` — Force to turn off optimizations. Ignore optimizationLevel below.
- L90 _public member_ `bool bEnableFMAPass = false;` — Enable a pass that converts floating point MUL+ADD pairs into FMAs to avoid re-association.
- L93 _public member_ `bool bDisableScalarBlockLayout = true;` — Disables scalar block layout for structured buffers. True for Vulkan mobile due to low coverage of 'VK_EXT_scalar_block_layout' extension.
- L96 _public member_ `bool bEnableSeparateSamplersInGlsl = false;` — Enables separate samplers in GLSL via extensions.
- L99 _public member_ `bool bSvPositionImplicitInvariant = true;` — Decorate SV_Position implicitly as invariant. This can drastically reduce Z-fighting but also prevent certain optimizations.
- L102 _public member_ `bool bSupportPreciseOutputs = false;` — Decorate output semantics as precise.
- L105 _public member_ `bool bPreserveStorageInput = false;` — Preserve storage inputs used for OpenGL
- L106 _public member_ `bool bForceStorageImageFormat = false;`
- L109 _public member_ `bool bWarningsAsErrors = false;` — Treat warnigns as errors. This adds '-WX' to the DXC arguments. See CFLAG_WarningsAsErrors.
- L118 _public member_ `ETargetEnvironment TargetEnvironment = ETargetEnvironment::Vulkan_1_1;`
- L121 _public member_ `FHlslShaderModel ShaderModel = { 6, 2 };` — Shader model version of the input language. By default SM6.2.
- L124 _public member_ `uint32 HlslVersion = 2018;` — HLSL language input version: 2015, 2016, 2017, 2018 (Default), 2021 (Breaking changes in short-circuiting evaluation).
- L130 _public member_ `FString SpirvCustomOptimizationPasses;` — SPIR-V specific optimization passes to override the default '-O' argument. This will be passed to DXC via the '-Oconfig=...' argument. Use "preset(relax-nested-expr)" for pre-defined set of optimization passes to relax nested expressions.
- L136 _public prototype_ `void ApplyCommonCompilerFlags(const FShaderCompilerFlags& InCompilerFlags);` — Applies common compiler flags to this options struct: WarningsAsErrors, ForceSpirvDebugInfo, and HLSL2021. Other flags must be individually applied depending on the shader backend.

#### enum `CrossCompiler::FShaderConductorOptions::ETargetEnvironment`  
`enum class ETargetEnvironment`  
_L111-117_
- L113 _public enumerator_ `Vulkan_1_0`
- L114 _public enumerator_ `Vulkan_1_1`
- L115 _public enumerator_ `Vulkan_1_2`
- L116 _public enumerator_ `Vulkan_1_3`

#### enum `CrossCompiler::EShaderConductorLanguage`  
`enum class EShaderConductorLanguage`  
_L140-147_
- desc: Target high level languages for ShaderConductor output.
- L142 _public enumerator_ `Hlsl`
- L143 _public enumerator_ `Glsl`
- L144 _public enumerator_ `Essl`
- L145 _public enumerator_ `Metal_macOS`
- L146 _public enumerator_ `Metal_iOS`

#### enum `CrossCompiler::EShaderConductorIR`  
`enum class EShaderConductorIR`  
_L150-154_
- desc: Intermediate representation languages for ShaderConductor disassembly output.
- L152 _public enumerator_ `Spirv`
- L153 _public enumerator_ `Dxil`

#### struct `CrossCompiler::FShaderConductorTarget`  
`struct FShaderConductorTarget`  
_L157-177_
- desc: Shader conductor output target descriptor.
- L159 _public prototype_ `FShaderConductorTarget();`
- L162 _public member_ `EShaderConductorLanguage Language = EShaderConductorLanguage::Glsl;` — Target shader semantics, e.g. "macOS" or "iOS" for Metal GPU semantics.
- L170 _public member_ `int32 Version = 0;` — Target shader version. Valid values for HLSL: 50, 60, 61, 62, 63, 64, 65, 66. Valid values for Metal family: 20300, 20200, 20100, 20000, 10200, 10100, 10000. Valid values for GLSL family: 310, 320, 330, 430.
- L173 _public member_ `TPimplPtr<FShaderCompilerDefinitions> CompileFlags;` — Cross compilation flags. This is used for high-level cross compilation (such as Metal output) that is send over to SPIRV-Cross, e.g. { "invariant_float_math", "1" }.
- L176 _public member_ `TFunction<bool(const FAnsiStringView& VariableName, const FAnsiStringView& TypeName, FString& OutRenamedTypeName)> VariableTypeRenameCallback;` — Optional callback to rename certain variable types.

#### struct `CrossCompiler::FShaderConductorIdentifierTable`  
`struct FShaderConductorIdentifierTable`  
_L180-193_
- desc: Container for all special case SPIR-V identifiers generated by ShaderConductor.
- L183 _public member_ `const ANSICHAR* InputAttribute;` — Identifier for vertex input attributes: "in.var.ATTRIBUTE".
- L186 _public member_ `const ANSICHAR* GlobalsUniformBuffer;` — Identifier for globals uniform buffers: "$Globals".
- L189 _public member_ `const ANSICHAR* IntermediateTessControlOutput;` — Identifier for the intermediate output variable in a tessellation-control shader.
- L192 _public member_ `const ANSICHAR* DummySampler;` — Identifier for dummy samplers used for platforms where samplers are required

#### class `CrossCompiler::FShaderConductorContext`  
`class FShaderConductorContext`  
_L196-287_
- desc: Wrapper class to handle interface between UE and ShaderConductor. Use to compile HLSL shaders to SPIR-V or high-level languages such as Metal.
- L200 _public prototype_ `FShaderConductorContext();` — Initializes the context with internal buffers used for the conversion of input and option descriptors between UE and ShaderConductor.
- L203 _public prototype_ `~FShaderConductorContext();` — Release the internal buffers.
- L206 _public prototype_ `FShaderConductorContext(FShaderConductorContext&& Rhs);` — Move constructor to take ownership of internal buffers from 'Rhs'.
- L209 _public prototype_ `FShaderConductorContext& operator = (FShaderConductorContext&& Rhs);` — Move operator to take ownership of internal buffers from 'Rhs'.
- L211 _public prototype_ `FShaderConductorContext(const FShaderConductorContext&) = delete;`
- L212 _public prototype_ `FShaderConductorContext& operator = (const FShaderConductorContext&) = delete;`
- L215 _public prototype_ `bool LoadSource(FStringView ShaderSource, const FString& Filename, const FString& EntryPoint, EShaderFrequency ShaderStage, const FShaderCompilerDefinitions* Definitions = nullptr, const TArray<FString>* ExtraDxcArgs = nullptr);` — Loads the shader source and converts the input descriptor to a format suitable for ShaderConductor. If 'Definitions' is null, the previously loaded definitions are not modified.
- L216 _public prototype_ `bool LoadSource(FAnsiStringView ShaderSource, const FString& Filename, const FString& EntryPoint, EShaderFrequency ShaderStage, const FShaderCompilerDefinitions* Definitions = nullptr, const TArray<FString>* ExtraDxcArgs = nullptr);`
- L217 _public prototype_ `bool LoadSource(const ANSICHAR* ShaderSource, const ANSICHAR* Filename, const ANSICHAR* EntryPoint, EShaderFrequency ShaderStage, const FShaderCompilerDefinitions* Definitions = nullptr, const TArray<FString>* ExtraDxcArgs = nullptr);`
- L220 _public prototype_ `bool CompileHlslToDxil(const FShaderConductorOptions& Options, TArray<uint32>& OutDxil);` — Compiles the specified HLSL shader source code to DXIL.
- L223 _public prototype_ `bool CompileHlslToSpirv(const FShaderConductorOptions& Options, TArray<uint32>& OutSpirv);` — Compiles the specified HLSL shader source code to SPIR-V.
- L226 _public prototype_ `void RemoveLineDirectives();` — Replaces #line 123 directives with //ine 123. Required to work around platform-specific shader debug data handling issues.
- L229 _public prototype_ `bool OptimizeSpirv(TArray<uint32>& Spirv, const ANSICHAR* const * OptConfigs, int32 OptConfigCount);` — Performs the specified optimization passes (e.g. "-O" or "--strip-reflect") on the SPIR-V module.
- L232 _public prototype_ `bool CompileSpirvToSource(const FShaderConductorOptions& Options, const FShaderConductorTarget& Target, const void* InSpirv, uint32 InSpirvByteSize, FString& OutSource);` — Compiles the specified SPIR-V shader binary code to high level source code (Metal or GLSL).
- L235 _public prototype_ `bool CompileSpirvToSourceAnsi(const FShaderConductorOptions& Options, const FShaderConductorTarget& Target, const void* InSpirv, uint32 InSpirvByteSize, TArray<ANSICHAR>& OutSource);` — Compiles the specified SPIR-V shader binary code to high level source code (Metal or GLSL) stored as null terminated ANSI string.
- L238 _public prototype_ `bool CompileSpirvToSourceBuffer(const FShaderConductorOptions& Options, const FShaderConductorTarget& Target, const void* InSpirv, uint32 InSpirvByteSize, const TFunction<void(const void* Data, uint32 Size)>& OutputCallback);` — Compiles the specified SPIR-V shader binary code to high level source code (Metal or GLSL) stored as byte buffer (without null terminator as it comes from ShaderConductor).
- L241 _public prototype_ `void FlushErrors(TArray<FShaderCompilerError>& OutErrors);` — Flushes the list of current compile errors and moves the ownership to the caller.
- L244 _public prototype_ `const ANSICHAR* GetSourceString() const;` — Returns a pointer to a null terminated ANSI string of the internal loaded sources, or null if no source has been loaded yet. This is automatically updated when RewriteHlsl() is called.
- L247 _public prototype_ `int32 GetSourceLength() const;` — Returns a length of the internal loaded sources (excluding the null terminator). This is automatically updated when RewriteHlsl() is called.
- L250 _public prototype_ `FString GenerateDxcArguments(const FShaderConductorOptions& Options) const;` — Returns the DXC command line arguments for the specified options. This does not include an output file, i.e. "-Fo" argument is not included.
- L253 _public function_ `inline const TArray<FShaderCompilerError>& GetErrors() const` — Returns the list of current compile errors.
- L260 _public prototype_ `static void ConvertCompileErrors(FAnsiStringView ErrorsString, TArray<FShaderCompilerError>& OutErrors);` — Convert raw ANSI string buffer containing DXC errors into array of <FShaderCompilerError>.
- L264 _public prototype_ `static bool IsIntermediateSpirvOutputVariable(const ANSICHAR* SpirvVariableName);` — Returns whether the specified variable name denotes an intermediate output variable. This is only true for a special identifiers generated by DXC to communicate patch constant data in the Hull Shader.
- L267 _public prototype_ `static const FShaderConductorIdentifierTable& GetIdentifierTable();` — Returns the table of special identifiers generated by ShaderConductor.
- L270 _public prototype_ `static bool Disassemble(EShaderConductorIR Language, const void* Binary, uint32 BinaryByteSize, TArray<ANSICHAR>& OutAssemblyText);` — Disassembles the specified SPIR-V or DXIL module and returns its assembly as text representation.
- L273 _public prototype_ `static bool Disassemble(EShaderConductorIR Language, const void* Binary, uint32 BinaryByteSize, FGenericShaderStat& OutShaderStat);` — Helper function to disassemble the specified SPIR-V or DXIL module and add it to the output code reflection array.
- L276 _public prototype_ `static const TCHAR* GetShaderFileExt(EShaderConductorLanguage Language, EShaderFrequency ShaderStage = SF_NumFrequencies);` — Returns a filename extension for the specified shading language and shader stage, e.g. "frag" for a GLSL pixel shader.
- L279 _public prototype_ `static void Shutdown();` — Explicitly shut down ShaderConductor and DXC shared libraries. Only used for Linux to prevent dangling mutex on exit.
- L285 _private member_ `TArray<FShaderCompilerError> Errors;`
- L286 _private member_ `FShaderConductorIntermediates* Intermediates;` — Pimpl idiom

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SHADERCOMPILERCOMMON_API`
- L20 _namespace_ `namespace CrossCompiler`

### `Source/Developer/ShaderCompilerCommon/Public/ShaderMinifier.h` (Public)


#### enum `UE::ShaderMinifier::EMinifyShaderFlags`  
`enum EMinifyShaderFlags`  
_L15-30_
- L17 _public enumerator_ `None = 0`
- L20 _public enumerator_ `OutputReasons = 1 << 1` — Add `// REASON: foo` comments next to emitted code blocks to identify which other block uses it or other reason why it was included
- L23 _public enumerator_ `OutputStats = 1 << 2` — Add a comment describing how many functions, structs, etc. were emitted
- L26 _public enumerator_ `OutputLines = 1 << 3` — Add `#line <line> <filename>` directives for each emitted code block
- L29 _public enumerator_ `OutputCommentLines = 1 << 4` — Keep original global scope comment lines, such as `// #define FOO 123` that were added by UE shader preprocessor

#### struct `UE::ShaderMinifier::FDiagnosticMessage`  
`struct FDiagnosticMessage`  
_L33-40_
- L35 _public member_ `FString Message;`
- L36 _public member_ `FString File;`
- L37 _public member_ `int32 Offset = INDEX_NONE;`
- L38 _public member_ `int32 Line = INDEX_NONE;`
- L39 _public member_ `int32 Column = INDEX_NONE;`

#### struct `UE::ShaderMinifier::FDiagnostics`  
`struct FDiagnostics`  
_L42-46_
- L44 _public member_ `TArray<FDiagnosticMessage> Errors;`
- L45 _public member_ `TArray<FDiagnosticMessage> Warnings;`

#### struct `UE::ShaderMinifier::FMinifiedShader`  
`struct FMinifiedShader`  
_L48-57_
- L50 _public member_ `FShaderSource::FStringType Code;`
- L51 _public member_ `FDiagnostics Diagnostics;`
- L53 _public function_ `bool Success() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L59 _prototype_ `extern FMinifiedShader Minify(const FShaderSource& PreprocessedShader, const FShaderSource::FViewType EntryPoint, EMinifyShaderFlags Flags = EMinifyShaderFlags::None);` (scope `UE::ShaderMinifier`)
- L60 _prototype_ `extern FMinifiedShader Minify(const FShaderSource& PreprocessedShader, TConstArrayView<FShaderSource::FViewType> RequiredSymbols, EMinifyShaderFlags Flags = EMinifyShaderFlags::None);` (scope `UE::ShaderMinifier`)

### `Source/Developer/ShaderCompilerCommon/Public/ShaderSDCE.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace ShaderMinifier` (scope `UE`)
- L6 _namespace_ `namespace SDCE` (scope `UE::ShaderMinifier`)
- L11 _prototype_ `void MinifyInPlace(const TConstArrayView<FStringView>& DCESymbols, FString& Code);` (scope `UE::ShaderMinifier::SDCE`) — Minify shader sources
- L16 _prototype_ `bool MinifyInPlace(const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, FString& Code);` (scope `UE::ShaderMinifier::SDCE`) — Minify shader sources from preprocessor output

### `Source/Developer/ShaderCompilerCommon/Public/ShaderSymbolExport.h` (Public)


#### class `FShaderSymbolExport`  
`class FShaderSymbolExport`  
_L26-88_
- L29 _public prototype_ `FShaderSymbolExport() = delete;`
- L30 _public prototype_ `FShaderSymbolExport(FName InShaderFormat);`
- L31 _public prototype_ `~FShaderSymbolExport();`
- L38 _public function_ `void NotifyShaderCompiled(const TConstArrayView<uint8>& PlatformSymbolData, const FString& DebugInfo = FString())` — `UE_DEPRECATED(5.6, "Use overload accepting an FCompressedBuffer for symbol data.")`
- L41 _public prototype_ `template<typename TPlatformShaderSymbolData> void NotifyShaderCompiled(const FCompressedBuffer& PlatformSymbolDataCompressed, const FString& DebugInfo = FString());`
- L44 _public prototype_ `void NotifyShaderCompilersShutdown();` — Called at the end of a cook to free resources and finalize artifacts created during the cook.
- L47 _private prototype_ `void Initialize();`
- L48 _private prototype_ `void WriteSymbolData(const FString& Filename, const FString& DebugInfo, TConstArrayView<uint8> Contents);`
- L49 _private prototype_ `void WriteFile(const FString& Filename, const TConstArrayView<uint8>& Contents, bool bAllowRetry);`
- L51 _private member_ `const FName ShaderFormat;`
- L53 _private member_ `TUniquePtr<FZipArchiveWriter> ZipWriter;`
- L54 _private member_ `TSet<FString> ExportedShaders;`
- L60 _private member_ `TMap<FString, FSymbolFileInfo> ExportedSymbolInfo;`
- L61 _private member_ `FString ExportPath;`
- L62 _private member_ `FString InfoFilePath;`
- L63 _private member_ `FString ExportFileName;`
- L64 _private member_ `uint64 TotalSymbolDataBytes{ 0 };`
- L65 _private member_ `uint64 TotalSymbolData{ 0 };`
- L66 _private member_ `bool bExportShaderSymbols{ false };`
- L68 _private member_ `TMap<FString, FString> ShaderInfos;`
- L70 _private member_ `std::atomic<uint32> DuplicateSymbols{ 0 };`
- L77 _private member_ `bool bMultiprocessOwner{ false };` — If true, the current process is the first process in a multiprocess group, or is not in a group, and should combine artifacts produced by the other processes. Will also be false if no combination is necessary for given settings.
- L79 _private member_ `std::atomic<bool> bInitialized{ false };`
- L80 _private member_ `FCriticalSection InitCs;`
- L85 _private member_ `FRWLock SymbolWriteLock;` — Write task synchronization: tasks run concurrently for decompress/deserialize; PendingTaskCount tracks in-flight tasks; AllTasksDoneEvent is triggered when it reaches zero so NotifyShaderCompilersShutdown can drain without holding references to each task.
- L86 _private member_ `std::atomic<int32> PendingTaskCount{ 0 };`
- L87 _private member_ `FEventRef AllTasksDoneEvent{ EEventMode::ManualReset };`
- L91 _function_ `template<typename TPlatformShaderSymbolData> inline void FShaderSymbolExport::NotifyShaderCompiled(const FCompressedBuffer& PlatformSymbolDataCompressed, const FString& DebugInfo)`

#### struct `FShaderSymbolExport::FSymbolFileInfo`  
`struct FSymbolFileInfo`  
_L55-59_
- L57 _public member_ `uint64 Hash;`
- L58 _public member_ `int32 Size;`

#### Free symbols / members of external scopes

- L118 _function_ `` (scope `FShaderSymbolExport::NotifyShaderCompiled`)

### `Source/Developer/ShaderCompilerCommon/Public/SpirvCommon.h` (Public)


#### class `TSpirvForwardIterator`  
`template <typename T> class TSpirvForwardIterator`  
_L17-119_
- desc: Template forward iterator for SPIR-V instructions.
- L21 _public function_ `TSpirvForwardIterator() : Ptr(nullptr)` — Initializes the iterator with a null pointer.
- L26 _public prototype_ `TSpirvForwardIterator(const TSpirvForwardIterator& Other) = default;`
- L27 _public prototype_ `TSpirvForwardIterator& operator = (const TSpirvForwardIterator& Other) = default;`
- L30 _public function_ `TSpirvForwardIterator(T* InPtr, bool bPointsAtHeader = false) : Ptr(InPtr)` — Initializes the iterator with the specified pointer.
- L52 _public function_ `SpvOp Opcode() const` — Returns the opcode of the current instruction.
- L58 _public function_ `uint32 WordCount() const` — Returns the word count of the current instruction. A valid SPIR-V instruction must have a word count greater zero.
- L64 _public function_ `uint32 Operand(int32 WordOffset) const` — Dereferences the value the current operand points to.
- L71 _public function_ `template <typename TDst> TDst OperandAs(int32 WordOffset) const` — Returns the operand as the specified reinterpreted type.
- L77 _public function_ `const ANSICHAR* OperandAsString(int32 WordOffset) const` — Returns the operand pointer as ANSI C string.
- L83 _public function_ `T* operator * () const` — Returns a pointer to the beginning of the SPIR-V instruction this iterator currently points to.
- L89 _public function_ `TSpirvForwardIterator& operator ++ ()` — Increments the iterator to point to the next SPIR-V instruction.
- L98 _public function_ `TSpirvForwardIterator operator ++ (int)` — Increments the iterator to point to the next SPIR-V instruction and returns the previous iterator state.
- L106 _public function_ `bool operator == (const TSpirvForwardIterator& Other) const` — Returns whether this iterator points to the same address as the other iterator.
- L112 _public function_ `bool operator != (const TSpirvForwardIterator& Other) const` — Returns whether this iterator does not point to the same address as the other iterator.
- L118 _private member_ `T* Ptr;`

#### struct `FSpirv`  
`struct FSpirv`  
_L125-189_
- desc: Base structure for SPIR-V modules in the shader backends.
- L127 _public member_ `TArray<uint32> Data;`
- L130 _public function_ `FORCEINLINE int8* GetByteData()` — Returns a byte pointer to the SPIR-V data.
- L136 _public function_ `FORCEINLINE const int8* GetByteData() const` — Returns a byte pointer to the SPIR-V data.
- L142 _public function_ `FORCEINLINE int32 GetByteSize() const` — Returns the size of this SPIR-V module in bytes.
- L148 _public function_ `FORCEINLINE uint32 GetWordOffset(const FSpirvConstIterator& Iter, uint32 OperandWordOffset = 0) const` — Returns the word offset to the instruction the specified iterator points to plus additional operand word offset.
- L155 _public function_ `FORCEINLINE FSpirvConstIterator cbegin() const` — Returns a constant iterator to the first instruction in this SPIR-V module.
- L161 _public function_ `FORCEINLINE FSpirvConstIterator begin() const` — Returns a constant iterator to the first instruction in this SPIR-V module.
- L167 _public function_ `FORCEINLINE FSpirvIterator begin()` — Returns an iterator to the first instruction in this SPIR-V module.
- L173 _public function_ `FORCEINLINE FSpirvConstIterator cend() const` — Returns a constant iterator to the end of this SPIR-V module.
- L179 _public function_ `FORCEINLINE FSpirvConstIterator end() const` — Returns a constant iterator to the end of this SPIR-V module.
- L185 _public function_ `FORCEINLINE FSpirvIterator end()` — Returns an iterator to the end of this SPIR-V module.

#### struct `FSpirvStructureMemberData`  
`struct FSpirvStructureMemberData`  
_L207-212_
- desc: Parse global variables (anything but function local variables) of specified storage class from the specified SPIR-V module.  Currently only supports plain data (integers, floats, vectors).
- L209 _public member_ `FString Name;`
- L210 _public member_ `int32 Offset = -1;`
- L211 _public member_ `uint32 Size = 0;`

#### Free symbols / members of external scopes

- L121 _typedef_ `using FSpirvIterator = TSpirvForwardIterator<uint32>;`
- L122 _typedef_ `using FSpirvConstIterator = TSpirvForwardIterator<const uint32>;`
- L192 _prototype_ `const TCHAR* SpirvBuiltinToString(const SpvBuiltIn BuiltIn);` — Returns the string representation of the specified SPIR-V built-in variable, e.g. SpvBuiltInPosition to TEXT("gl_Position"). Returns nullptr for invalid value.
- L195 _prototype_ `void FindOffsetToSpirvEntryPoint(const FSpirv& Spirv, const ANSICHAR* EntryPointName, uint32& OutWordOffsetToEntryPoint, uint32& OutWordOffsetToMainName);` — Returns word offset to the entry point (OpEntryPoint) and name of the entry point (OpName). If the respective entry has not been found, the output offset is 0.
- L198 _prototype_ `extern const ANSICHAR* FindSpirvEntryPoint(const FSpirv& Spirv);` — Finds the entry point name name.
- L201 _prototype_ `const ANSICHAR* PatchSpirvEntryPointWithCRC(FSpirv& Spirv, uint32& OutCRC);` — Renames the fixed-size entry point name (which must be "main_00000000_00000000") to the formatted name including a CRC over the module. Returns the new entry point name.
- L204 _prototype_ `void ParseSpirvGlobalVariables(const FSpirv& Spirv, SpvStorageClass StorageClass, TArray<FString>& OutVariableNames);` — Parse global variables (anything but function local variables) of specified storage class from the specified SPIR-V module.
- L213 _prototype_ `TArray<FSpirvStructureMemberData> ParseSpirvStructureMembers(const FSpirv& Spirv, FAnsiStringView StructureName);`

### `Source/Developer/ShaderCompilerCommon/Public/SpirvReflectCommon.h` (Public)


#### struct `FSpirvReflectBindings`  
`struct FSpirvReflectBindings`  
_L19-55_
- desc: Container structure for all SPIR-V reflection resources and in/out attributes.
- L21 _public member_ `TArray<SpvReflectInterfaceVariable*> InputAttributes;`
- L22 _public member_ `TArray<SpvReflectInterfaceVariable*> OutputAttributes;`
- L23 _public member_ `TArray<SpvReflectInterfaceVariable*> PushConstants;`
- L24 _public member_ `TSet<SpvReflectDescriptorBinding*> AtomicCounters;`
- L25 _public member_ `TArray<SpvReflectDescriptorBinding*> InputAttachments;` — for subpass inputs
- L26 _public member_ `TArray<SpvReflectDescriptorBinding*> UniformBuffers;`
- L27 _public member_ `TArray<SpvReflectDescriptorBinding*> Samplers;`
- L28 _public member_ `TArray<SpvReflectDescriptorBinding*> TextureSRVs;`
- L29 _public member_ `TArray<SpvReflectDescriptorBinding*> TextureUAVs;`
- L30 _public member_ `TArray<SpvReflectDescriptorBinding*> TBufferSRVs;`
- L31 _public member_ `TArray<SpvReflectDescriptorBinding*> TBufferUAVs;`
- L32 _public member_ `TArray<SpvReflectDescriptorBinding*> SBufferSRVs;`
- L33 _public member_ `TArray<SpvReflectDescriptorBinding*> SBufferUAVs;`
- L34 _public member_ `TArray<SpvReflectDescriptorBinding*> AccelerationStructures;`
- L35 _public member_ `int32 NumBindlessSamplers = 0;`
- L36 _public member_ `int32 NumBindlessResources = 0;`
- L39 _public prototype_ `void AddDescriptorBinding(SpvReflectDescriptorBinding* InBinding);` — Adds the specified descriptor binding to the corresponding container iff the descriptor is marked as being accessed.
- L42 _public prototype_ `void GatherDescriptorBindings(const spv_reflect::ShaderModule& SpirvReflection);` — Gathers all descriptor bindings from the specified SPIRV-Reflect module.
- L45 _public prototype_ `void GatherInputAttributes(const spv_reflect::ShaderModule& SpirvReflection);` — Gathers all input interface variables from the specified SPIRV-Reflect module.
- L48 _public prototype_ `void GatherOutputAttributes(const spv_reflect::ShaderModule& SpirvReflection);` — Gathers all output interface variables from the specified SPIRV-Reflect module.
- L51 _public prototype_ `void GatherPushConstants(const spv_reflect::ShaderModule& SpirvReflection);` — Gathers all push constant variables from the specified SPIRV-Reflect module.
- L54 _public prototype_ `void AssignInputAttributeLocationsBySemanticIndex(spv_reflect::ShaderModule& SpirvReflection, const ANSICHAR* SemanticName);` — Assigns the binding location for all input attributes by its semantic index if their name is equal to 'SemanticName'. Used for vertex shaders where all input attributes have the "ATTRIBUTE" semantic.
