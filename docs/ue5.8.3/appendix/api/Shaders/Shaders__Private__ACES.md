# Shaders / Shaders/Private/ACES

- files: 6; lines: 3028
- record kinds: define=4, function=111, include=5, member=45, static_const=79, struct=5

### `Shaders/Private/ACES/ACESCommon.ush` (Private)

- lines: 301; parse: all-branches

#### Macros (#define, 1)

- L5 `#define WhiteStandard uint`
- L3 #pragma `once`

#### Structs / classes (1)

- L10-15 _struct_ **`FColorSpace`** `struct FColorSpace`
  - L12 _member_ `WhiteStandard White;`
  - L13 _member_ `float3x3 XYZtoRGB;`
  - L14 _member_ `float3x3 RGBtoXYZ;`

#### static const (20)

- L6 _static_const_ `static const WhiteStandard WhiteStandard_D65 = 0;`
- L7 _static_const_ `static const WhiteStandard WhiteStandard_D60 = 1;`
- L8 _static_const_ `static const WhiteStandard WhiteStandard_DCI = 2;`
- L17-22 _static_const_ `static const float3x3 AP0_2_XYZ_MAT = { 0.9525523959, 0.0000000000, 0.0000936786, 0.3439664498, 0.7281660966,-0.0721325464, 0.0000000000, 0.0000000000, 1.0088251844, };`
- L24-29 _static_const_ `static const float3x3 XYZ_2_AP0_MAT = { 1.0498110175, 0.0000000000,-0.0000974845, -0.4959030231, 1.3733130458, 0.0982400361, 0.0000000000, 0.0000000000, 0.9912520182, };`
- L31-36 _static_const_ `static const float3x3 AP1_2_XYZ_MAT = { 0.6624541811, 0.1340042065, 0.1561876870, 0.2722287168, 0.6740817658, 0.0536895174, -0.0055746495, 0.0040607335, 1.0103391003, };`
- L38-43 _static_const_ `static const float3x3 XYZ_2_AP1_MAT = { 1.6410233797, -0.3248032942, -0.2364246952, -0.6636628587, 1.6153315917, 0.0167563477, 0.0117218943, -0.0082844420, 0.9883948585, };`
- L45-50 _static_const_ `static const float3x3 AP0_2_AP1_MAT = { 1.4514393161, -0.2365107469, -0.2149285693, -0.0765537734, 1.1762296998, -0.0996759264, 0.0083161484, -0.0060324498, 0.9977163014, };` — mul( AP0_2_XYZ_MAT, XYZ_2_AP1_MAT );
- L52-57 _static_const_ `static const float3x3 AP1_2_AP0_MAT = { 0.6954522414, 0.1406786965, 0.1638690622, 0.0447945634, 0.8596711185, 0.0955343182, -0.0055258826, 0.0040252103, 1.0015006723, };` — mul( AP1_2_XYZ_MAT, XYZ_2_AP0_MAT );
- L59-64 _static_const_ `static const float3 AP1_RGB2Y = { 0.2722287168, 0.6740817658, 0.0536895174, };`
- L67-72 _static_const_ `static const float3x3 XYZ_2_sRGB_MAT = { 3.2409699419, -1.5373831776, -0.4986107603, -0.9692436363, 1.8759675015, 0.0415550574, 0.0556300797, -0.2039769589, 1.0569715142, };` — REC 709 primaries
- L74-79 _static_const_ `static const float3x3 sRGB_2_XYZ_MAT = { 0.4123907993, 0.3575843394, 0.1804807884, 0.2126390059, 0.7151686788, 0.0721923154, 0.0193308187, 0.1191947798, 0.9505321522, };`
- L82-87 _static_const_ `static const float3x3 XYZ_2_Rec2020_MAT = { 1.7166511880, -0.3556707838, -0.2533662814, -0.6666843518, 1.6164812366, 0.0157685458, 0.0176398574, -0.0427706133, 0.9421031212, };` — REC 2020 primaries
- L89-94 _static_const_ `static const float3x3 Rec2020_2_XYZ_MAT = { 0.6369580483, 0.1446169036, 0.1688809752, 0.2627002120, 0.6779980715, 0.0593017165, 0.0000000000, 0.0280726930, 1.0609850577, };`
- L97-102 _static_const_ `static const float3x3 XYZ_2_P3D65_MAT = { 2.4934969119, -0.9313836179, -0.4027107845, -0.8294889696, 1.7626640603, 0.0236246858, 0.0358458302, -0.0761723893, 0.9568845240, };` — P3, D65 primaries
- L104-109 _static_const_ `static const float3x3 P3D65_2_XYZ_MAT = { 0.4865709486, 0.2656676932, 0.1982172852, 0.2289745641, 0.6917385218, 0.0792869141, 0.0000000000, 0.0451133819, 1.0439443689, };`
- L112-117 _static_const_ `static const float3x3 D65_2_D60_CAT = { 1.0130349146, 0.0061052578, -0.0149709436, 0.0076982301, 0.9981633521, -0.0050320385, -0.0028413174, 0.0046851567, 0.9245061375, };` — Bradford chromatic adaptation transforms between ACES white point (D60) and sRGB white point (D65)
- L119-124 _static_const_ `static const float3x3 D60_2_D65_CAT = { 0.9872240087, -0.0061132286, 0.0159532883, -0.0075983718, 1.0018614847, 0.0053300358, 0.0030725771, -0.0050959615, 1.0816806031, };`
- L126-131 _static_const_ `static const float3x3 CAM16_2_XYZ_MAT = { 2.0512756811, -1.1400313439, 0.0887556628, 0.4269389763, 0.7005835277, -0.1275225040, -0.0174712779, -0.0384725929, 1.0589468739 };`
- L133-138 _static_const_ `static const float3x3 XYZ_2_CAM16_MAT = { 0.3640744835, 0.5947008156, 0.04110127349, -0.2222450987, 1.0738554823, 0.14794533610, -0.0020676190, 0.0488260453, 0.95038755696 };`

#### Functions (10)

- L140-145 _function_ `float rgb_2_saturation(float3 rgb)`
- L148-164 _function_ `float rgb_2_hue(float3 rgb)` — Transformations from RGB to other color representations
- L166-172 _function_ `float center_hue(float hue, float centerH)`
- L176-186 _function_ `float3 XYZ_2_xyY(float3 XYZ)` — Transformations between CIE XYZ tristimulus values and CIE x,y chromaticity coordinates
- L188-196 _function_ `float3 xyY_2_XYZ(float3 xyY)`
- L199-231 _function_ `float3x3 ChromaticAdaptation( float2 src_xy, float2 dst_xy )`
- L234-249 _function_ `float glow_fwd(float ycIn, float glowGainIn, float glowMid)`
- L251-266 _function_ `float glow_inv(float ycOut, float glowGainIn, float glowMid)`
- L268-290 _function_ `float rgb_2_yc(float3 rgb, float ycRadiusWeight = 1.75)`
- L292-299 _function_ `float sigmoid_shaper(float x)`

### `Shaders/Private/ACES/ACESDisplayEncoding.ush` (Private)

- lines: 47; parse: all-branches
- includes: L12 `ACESOutputTransform.ush`
- L10 #pragma `once`

#### Functions (2)

- L14-33 _function_ `float3 apply_white_scale( float3 XYZluminance, ODTParams PARAMS, bool _invert)`
- L35-46 _function_ `float3 clamp_zero_to_peakLuminance( float3 XYZ_in, ODTParams PARAMS)`

### `Shaders/Private/ACES/ACESOutputTransform.ush` (Private)

- lines: 1023; parse: all-branches
- includes: L13 `ACESUtilities.ush`, L14 `ACESTonescale.ush`
- L11 #pragma `once`

#### Structs / classes (1)

- L59-98 _struct_ **`ODTParams`** `struct ODTParams`
  - L61 _member_ `float peakLuminance;`
  - L64 _member_ `float n_r;` — Tonescale // Set via TSParams structure
  - L65 _member_ `float g;` — surround / contrast
  - L66 _member_ `float t_1;` — shadow toe or flare/glare compensation
  - L67 _member_ `float c_t;`
  - L68 _member_ `float s_2;`
  - L69 _member_ `float u_2;`
  - L70 _member_ `float m_2;`
  - L73 _member_ `float limitJmax;` — Chroma Compression
  - L74 _member_ `float midJ;`
  - L75 _member_ `float model_gamma;`
  - L76 _member_ `float sat;`
  - L77 _member_ `float sat_thr;`
  - L78 _member_ `float compr;`
  - L79 _member_ `float chromaCompressScale;`
  - L81 _member_ `float focusDist;`
  - L84 _member_ `float3x3 LIMIT_RGB_TO_XYZ;` — Limit
  - L85 _member_ `float3x3 LIMIT_XYZ_TO_RGB;`
  - L86 _member_ `float3 XYZ_w_limit;`
  - L89 _member_ `float3x3 OUTPUT_RGB_TO_XYZ;` — Output
  - L90 _member_ `float3x3 OUTPUT_XYZ_TO_RGB;`
  - L91 _member_ `float3 XYZ_w_output;`
  - L93 _member_ `float lowerHullGamma;`
  - L95 _member_ `Texture2D<float> reach_table;`
  - L96 _member_ `Texture2D<float> gamut_table;`
  - L97 _member_ `Texture2D<float> gamma_table;`

#### static const (24)

- L17 _static_const_ `static const float smoothCusps = 0.12;` — Gamut compression constants
- L18 _static_const_ `static const float smoothM = 0.27;`
- L19 _static_const_ `static const float cuspMidBlend = 1.3;`
- L21 _static_const_ `static const float focusGainBlend = 0.3;`
- L22 _static_const_ `static const float focusAdjustGain = 0.55;`
- L23 _static_const_ `static const float focusDistance = 1.35;`
- L24 _static_const_ `static const float focusDistanceScaling = 1.75;`
- L27 _static_const_ `static const float compressionThreshold = 0.75;` — Constant used in gamut mapping
- L29 _static_const_ `static const int tableSize = 360;` — add 1 extra entry at end that is to duplicate first entry for wrapped hue
- L30 _static_const_ `static const int additionalTableEntries = 2;` — allots for extra entries to wrap the hues without special cases
- L31 _static_const_ `static const int totalTableSize = tableSize + additionalTableEntries;`
- L32 _static_const_ `static const int baseIndex = 1;` — array index for smallest hue, which is not necessarily a 0.0 hue angle
- L34 _static_const_ `static const float gammaMinimum = 0.0;`
- L35 _static_const_ `static const float gammaMaximum = 5.0;`
- L36 _static_const_ `static const float gammaSearchStep = 0.4;`
- L37 _static_const_ `static const float gammaAccuracy = 1e-5;`
- L39 _static_const_ `static const float referenceLuminance = 100.;`
- L42 _static_const_ `static const float L_A = 100.;` — CAM Parameters
- L43 _static_const_ `static const float Y_b = 20.;`
- L45 _static_const_ `static const float ac_resp = 1.0;`
- L46 _static_const_ `static const float ra = 2. * ac_resp;`
- L47 _static_const_ `static const float ba = 0.05 + (2. - ra);`
- L49 _static_const_ `static const float3 surround = float3(0.9, 0.59, 0.9);`
- L52-57 _static_const_ `static const float3x3 panlrcm = { 460.0, 451.0, 288.0 , 460.0, -891.0, -261.0 , 460.0, -220.0, -6300.0 };` — Matrix for Hellwig inverse

#### Functions (36)

- L100-108 _function_ `float wrap_to_360(float hue)`
- L110-115 _function_ `int hue_position_in_uniform_table(float hue, int table_size)`
- L117-121 _function_ `int next_position_in_table(int entry, int table_size)`
- L123-127 _function_ `float base_hue_for_position(int i_lo, int table_size)`
- L130-136 _function_ `float3 post_adaptation_non_linear_response_compression_forward(float3 RGB, float F_L)` — CAM Functions
- L138-143 _function_ `float3 post_adaptation_non_linear_response_compression_inverse(float3 RGB, float F_L)`
- L145-201 _function_ `float3 XYZ_to_Hellwig2022_JMh( float3 XYZ, float3 XYZ_w)`
- L203-263 _function_ `float3 Hellwig2022_JMh_to_XYZ( float3 JMh, float3 XYZ_w)`
- L265-282 _function_ `float Hellwig_J_to_Y(float J, float surround = 0.59, float L_A = 100., float Y_b = 20.)`
- L284-301 _function_ `float Y_to_Hellwig_J(float Y, float surround = 0.59, float L_A = 100., float Y_b = 20.)`
- L303-313 _function_ `float3 clamp_AP1(float3 AP1, float peakLuminance)`
- L315-332 _function_ `float3 aces_to_JMh(float3 aces, float peakLuminance)`
- L334-349 _function_ `float3 JMh_to_aces(float3 JMh, float peakLuminance)`
- L351-437 _function_ `ODTParams init_ODTParams( float peakLuminance, float3x3 LIMIT_RGB_TO_XYZ, float3x3 LIMIT_XYZ_TO_RGB, float3x3 OUTPUT_RGB_TO_XYZ, float3x3 OUTPUT_XYZ_TO_RGB, Texture2D<float> reach_table, Texture2D<float> gamut_table, Texture2D<float> gamma_table )`
- L445-467 _function_ `float chromaCompressionNorm(float h, ODTParams PARAMS)` — Chroma compression Compresses colors inside the gamut with the aim for colorfulness to have an appropriate rate of change from display black to display white, and from achromatic outward to purer colors.
- L472-487 _function_ `float toe_fwd(float x, float limit, float k1_in, float k2_in)` — A "toe" function that remaps the given value x between 0 and limit. The k1 and k2 parameters change the size and shape of the toe. https://www.desmos.com/calculator/6vplvw14ti
- L489-502 _function_ `float toe_inv(float x, float limit, float k1_in, float k2_in)`
- L504-513 _function_ `float reachMFromTable(float h, Texture2D<float> reach_table)`
- L520-591 _function_ `float chromaCompression(float3 JMh, float origJ, ODTParams PARAMS, bool _invert = false)` — In-gamut chroma compression Compresses colors inside the gamut with the aim for colorfulness to have an appropriate rate of change from display black to display white, and from achromatic outward to purer colors.
- L593-627 _function_ `float compressionFunction(float v, float thr, float lim, bool _invert = false)`
- L629-632 _function_ `int midpoint(int low, int high)`
- L634-669 _function_ `float2 cuspFromTable(float h, Texture2D<float> gamut_table)`
- L672-693 _function_ `float3 tonemapAndCompress_fwd(float3 inputJMh, ODTParams PARAMS)`
- L695-716 _function_ `float3 tonemapAndCompress_inv(float3 JMh, ODTParams PARAMS)`
- L718-727 _function_ `float3 JMh_to_output_XYZ(float3 JMh, ODTParams PARAMS)`
- L729-738 _function_ `float3 XYZ_output_to_JMh(float3 XYZ, ODTParams PARAMS)`
- L740-754 _function_ `float hueDependentUpperHullGamma(float h, Texture2D<float> gamma_table)`
- L756-773 _function_ `float getFocusGain(float J, float cuspJ, float limitJmax)`
- L775-816 _function_ `float solve_J_intersect(float J, float M, float focusJ, float maxJ, float slope_gain)`
- L818-863 _function_ `float3 findGamutBoundaryIntersection(float3 JMh_s, float2 JM_cusp_in, float J_focus, float J_max, float slope_gain, float gamma_top, float gamma_bottom)`
- L865-894 _function_ `float3 getReachBoundary(float J, float M, float h, ODTParams PARAMS, float2 JMcusp, float focusJ)`
- L896-959 _function_ `float3 compressGamut(float3 JMh, ODTParams PARAMS, float Jx, bool _invert = false)`
- L961-966 _function_ `float3 gamutMap_fwd(float3 JMh, ODTParams PARAMS )`
- L968-990 _function_ `float3 gamutMap_inv(float3 JMh, ODTParams PARAMS)`
- L992-1005 _function_ `float3 outputTransform_fwd( float3 aces, ODTParams PARAMS)`
- L1007-1023 _function_ `float3 outputTransform_inv( float3 XYZ, ODTParams PARAMS)`

### `Shaders/Private/ACES/ACESTonescale.ush` (Private)

- lines: 96; parse: all-branches
- L13 #pragma `once`

#### Structs / classes (1)

- L15-25 _struct_ **`TSParams`** `struct TSParams`
  - L17 _member_ `float n;`
  - L18 _member_ `float n_r;`
  - L19 _member_ `float g;`
  - L20 _member_ `float t_1;`
  - L21 _member_ `float c_t;`
  - L22 _member_ `float s_2;`
  - L23 _member_ `float u_2;`
  - L24 _member_ `float m_2;`

#### Functions (3)

- L28-69 _function_ `TSParams init_TSParams(float peakLuminance)` — Tonescale pre-calculations
- L73-83 _function_ `float tonescale_fwd( float x, TSParams params )` — --- Tone scale math ---
- L85-95 _function_ `float tonescale_inv( float Y, TSParams params )`

### `Shaders/Private/ACES/ACESUtilities.ush` (Private)

- lines: 79; parse: all-branches
- includes: L11 `ACESCommon.ush`

#### Macros (#define, 3)

- L13 `#define UE_ACES_SAFE_FUNCTIONS 1`
- L69 `#define spow pow` _[#if !(UE_ACES_SAFE_FUNCTIONS)]_
- L76 `#define satan2 atan2` _[#if !(UE_ACES_SAFE_FUNCTIONS)]_
- L9 #pragma `once`

#### Functions (10)

- L15-18 _function_ `float radians_to_degrees( float radians )`
- L20-23 _function_ `float degrees_to_radians( float degrees )`
- L25-28 _function_ `float copysign(float x, float y)`
- L30-33 _function_ `float3 copysign(float3 x, float3 y)`
- L35-39 _function_ `float smin(float a, float b, float s)`
- L43-46 _function_ `float spow(float base, float exponent)` _[#if UE_ACES_SAFE_FUNCTIONS]_
- L48-55 _function_ `float3 spow(float3 base, float3 exponent)` _[#if UE_ACES_SAFE_FUNCTIONS]_
- L57-60 _function_ `float sdiv(float a, float b)` _[#if UE_ACES_SAFE_FUNCTIONS]_
- L62-65 _function_ `float satan2(float y, float x)` _[#if UE_ACES_SAFE_FUNCTIONS]_
- L71-74 _function_ `float sdiv(float a, float b)` _[#if !(UE_ACES_SAFE_FUNCTIONS)]_

### `Shaders/Private/ACES/ACES_v1.3.ush` (Private)

- lines: 1482; parse: all-branches
- includes: L81 `ACESCommon.ush`
- L79 #pragma `once`

#### Structs / classes (2)

- L261-266 _struct_ **`TsPoint`** `struct TsPoint`
  - L263 _member_ `float x;` — ACES
  - L264 _member_ `float y;` — luminance
  - L265 _member_ `float slope;`
- L268-275 _struct_ **`TsParams`** `struct TsParams`
  - L270 _member_ `TsPoint Min;`
  - L271 _member_ `TsPoint Mid;`
  - L272 _member_ `TsPoint Max;`
  - L273 _member_ `float coefsLow[6];`
  - L274 _member_ `float coefsHigh[6];`

#### static const (35)

- L85 _static_const_ `static const float HALF_MAX = 65504.0;`
- L86 _static_const_ `static const float HALF_POS_INF = 65535.0f;`
- L88 _static_const_ `static const float MIN_STOP_SDR = -6.5;`
- L89 _static_const_ `static const float MAX_STOP_SDR = 6.5;`
- L91 _static_const_ `static const float MIN_STOP_RRT = -15.;`
- L92 _static_const_ `static const float MAX_STOP_RRT = 18.;`
- L94 _static_const_ `static const float MIN_LUM_SDR = 0.02;`
- L95 _static_const_ `static const float MAX_LUM_SDR = 48.0;`
- L97 _static_const_ `static const float MIN_LUM_RRT = 0.0001;`
- L98 _static_const_ `static const float MAX_LUM_RRT = 10000.0;`
- L154-159 _static_const_ `static const float3x3 M1 = { { 0.5, -1.0, 0.5 }, { -1.0, 1.0, 0.5 }, { 0.5, 0.0, 0.0 } };` — note: this matrix is not transposed unlike other matrix operations because instead of doing v_out = mul(M, v_in), we do v_out = mul(v_in, M) Textbook monomial to basis-function conversion matrix.
- L676 _static_const_ `static const float pq_m1 = 0.1593017578125;` — Constants from SMPTE ST 2084-2014
- L677 _static_const_ `static const float pq_m2 = 78.84375;` — ( 2523.0 / 4096.0 ) * 128.0;
- L678 _static_const_ `static const float pq_c1 = 0.8359375;` — 3424.0 / 4096.0 or pq_c3 - pq_c2 + 1.0;
- L679 _static_const_ `static const float pq_c2 = 18.8515625;` — ( 2413.0 / 4096.0 ) * 32.0;
- L680 _static_const_ `static const float pq_c3 = 18.6875;` — ( 2392.0 / 4096.0 ) * 32.0;
- L682 _static_const_ `static const float pq_C = 10000.0;`
- L851 _static_const_ `static const float RRT_SAT_FACTOR = 0.96;` — Desaturation contants
- L852 _static_const_ `static const float ONE_MINUS_RRT_SAT_FACTOR = 0.04;`
- L853-862 _static_const_ `static const float3x3 RRT_SAT_MAT = { {0.970889148672, 0.02696327063, 0.0021475807}, {0.010889148672, 0.98696327063, 0.0021475807}, {0.010889148672, 0.02696327063, 0.9621475807} };`
- L864-869 _static_const_ `static const float3x3 RRT_SAT_MAT_INV = { { 1.03032386 , -0.0280867405 , -0.00223706313 }, { -0.0113428626 , 1.01357996 , -0.00223706337 }, { -0.0113428626 , -0.0280867405 , 1.03942955 } };`
- L873 _static_const_ `static const float RRT_GLOW_GAIN = 0.05;` — "Glow" module constants
- L874 _static_const_ `static const float RRT_GLOW_MID = 0.08;`
- L877 _static_const_ `static const float RRT_RED_SCALE = 0.82;` — Red modifier constants
- L878 _static_const_ `static const float RRT_RED_PIVOT = 0.03;`
- L879 _static_const_ `static const float RRT_RED_HUE = 0.;`
- L880 _static_const_ `static const float RRT_RED_WIDTH = 135.;`
- L984 _static_const_ `static const float DIM_SURROUND_GAMMA = 0.9811;` — Gamma compensation factor
- L1382 _static_const_ `static const float LIM_CYAN = 1.147;` — --- Gamut Compress Parameters --- Distance from achromatic which will be compressed to the gamut boundary Values calculated to encompass the encoding gamuts of common digital cinema cameras
- L1383 _static_const_ `static const float LIM_MAGENTA = 1.264;`
- L1384 _static_const_ `static const float LIM_YELLOW = 1.312;`
- L1389 _static_const_ `static const float THR_CYAN = 0.815;` — Percentage of the core gamut to protect Values calculated to protect all the colors of the ColorChecker Classic 24 as given by ISO 17321-1 and Ohta (1997)
- L1390 _static_const_ `static const float THR_MAGENTA = 0.803;`
- L1391 _static_const_ `static const float THR_YELLOW = 0.880;`
- L1394 _static_const_ `static const float PWR = 1.2;` — Aggressiveness of the compression curve

#### Functions (50)

- L100-103 _function_ `float pow10(float x)`
- L106-150 _function_ `float cubic_basis_shaper ( float x, float w )`
- L165-188 _function_ `float roll_white_fwd( float inValue, float new_wht, float width )`
- L190-216 _function_ `float roll_white_rev( float inValue, float new_wht, float width )`
- L218-235 _function_ `float3 limit_to_primaries ( float3 XYZ, FColorSpace LIMITING_PRI )`
- L238-242 _function_ `float interpolate1D(const float2 table[2], float value)` — + TODO: check if valid
- L245-251 _function_ `float lookup_ACESmin(float minLum)`
- L253-259 _function_ `float lookup_ACESmax(float maxLum)`
- L277-304 _function_ `void init_coefsLow( TsPoint TsPointLow, TsPoint TsPointMid, out float coefsLow[5] )`
- L306-333 _function_ `void init_coefsHigh( TsPoint TsPointMid, TsPoint TsPointMax, out float coefsHigh[5] )`
- L335-338 _function_ `float shift(float inValue, float expShift)`
- L340-366 _function_ `TsParams init_TsParams( float minLum, float maxLum, float expShift = 0 )`
- L368-419 _function_ `float ssts ( const float x, const TsParams C )`
- L421-523 _function_ `float inv_ssts ( const float y, const TsParams C )`
- L525-537 _function_ `float3 ssts_f3 ( const float3 x, const TsParams C )`
- L539-551 _function_ `float3 inv_ssts_f3 ( const float3 x, const TsParams C )`
- L553-564 _function_ `float moncurve_f(float x, float gamma, float offs)`
- L566-577 _function_ `float moncurve_r(float y, float gamma, float offs)`
- L579-586 _function_ `float3 moncurve_f_f3(float3 x, float gamma, float offs)`
- L588-595 _function_ `float3 moncurve_r_f3(float3 y, float gamma, float offs)`
- L597-605 _function_ `float bt1886_f(float V, float gamma, float Lw, float Lb)`
- L607-615 _function_ `float bt1886_r(float L, float gamma, float Lw, float Lb)`
- L617-624 _function_ `float3 bt1886_f_f3(float3 V, float gamma, float Lw, float Lb)`
- L626-633 _function_ `float3 bt1886_r_f3(float3 L, float gamma, float Lw, float Lb)`
- L637-643 _function_ `float smpteRange_to_fullRange(float inValue)` — SMPTE Range vs Full Range scaling formulas
- L645-651 _function_ `float fullRange_to_smpteRange(float inValue)`
- L653-661 _function_ `float3 smpteRange_to_fullRange_f3(float3 rgbIn)`
- L663-671 _function_ `float3 fullRange_to_smpteRange_f3(float3 rgbIn)`
- L688-699 _function_ `float ST2084_2_Y(float N)` — Converts from the non-linear perceptually quantized space to linear cd/m^2 Note that this is in float, and assumes normalization from 0 - 1 (0 - pq_C for linear) and does not handle the integer coding in the Annex sections of SMPTE ST 2084-2014
- L705-715 _function_ `float Y_2_ST2084(float C)` — Converts from linear cd/m^2 to the non-linear perceptually quantized space Note that this is in float, and assumes normalization from 0 - 1 (0 - pq_C for linear) and does not handle the integer coding in the Annex sections of SMPTE ST 2084-2014
- L717-727 _function_ `float3 Y_2_ST2084_f3(float3 inValue)`
- L729-739 _function_ `float3 ST2084_2_Y_f3(float3 inValue)`
- L742-798 _function_ `float3 ST2084_2_HLG_1000nits_f3(float3 PQ)` — Conversion of PQ signal to HLG, as detailed in Section 7 of ITU-R BT.2390-0
- L802-848 _function_ `float3 HLG_2_ST2084_1000nits_f3(float3 HLG)` — Conversion of HLG to PQ signal, as detailed in Section 7 of ITU-R BT.2390-0
- L883-910 _function_ `float3 rrt_sweeteners(float3 inValue)`
- L912-953 _function_ `float3 inv_rrt_sweeteners(float3 inValue)`
- L955-958 _function_ `float Y_2_linCV(float Y, float Ymax, float Ymin)`
- L960-963 _function_ `float linCV_2_Y(float linCV, float Ymax, float Ymin)`
- L965-972 _function_ `float3 Y_2_linCV_f3(float3 Y, float Ymax, float Ymin)`
- L974-981 _function_ `float3 linCV_2_Y_f3(float3 linCV, float Ymax, float Ymin)`
- L986-996 _function_ `float3 darkSurround_to_dimSurround(float3 linearCV)`
- L998-1008 _function_ `float3 dimSurround_to_darkSurround(float3 linearCV)`
- L1010-1016 _function_ `float3 dark_to_dim(float3 XYZ)`
- L1018-1024 _function_ `float3 dim_to_dark(float3 XYZ)`
- L1026-1201 _function_ `float3 outputTransform ( float3 inValue, TsParams PARAMS, FColorSpace DISPLAY_PRI, FColorSpace LIMITING_PRI, int EOTF, int SURROUND, bool STRETCH_BLACK = true, bool D60_SIM = false, bool LEGAL_RANGE = false )`
- L1203-1227 _function_ `float3 outputTransform ( float3 inValue, float Y_MIN, float Y_MID, float Y_MAX, FColorSpace DISPLAY_PRI, FColorSpace LIMITING_PRI, int EOTF, int SURROUND, bool STRETCH_BLACK = true, bool D60_SIM = false, bool LEGAL_RANGE = false )`
- L1229-1377 _function_ `float3 invOutputTransform ( float3 inValue, float Y_MIN, float Y_MID, float Y_MAX, FColorSpace DISPLAY_PRI, FColorSpace LIMITING_PRI, int EOTF, int SURROUND, bool STRETCH_BLACK = true, bool D60_SIM = false, bool LEGAL_RANGE = false )`
- L1399-1431 _function_ `float compress(float dist, float lim, float thr, float pwr, bool invert)` — Calculate compressed distance
- L1433-1436 _function_ `float max_f3(float3 a)`
- L1438-1480 _function_ `float3 compressColor ( const float3 ACES, const bool invert = false )`
