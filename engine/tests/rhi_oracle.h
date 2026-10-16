/* engine/tests/rhi_oracle.h */
#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <stdbool.h>

#define RHI_ORACLE_GW 20u
#define RHI_ORACLE_GH 15u
#define RHI_ORACLE_MAE_MAX 8.0
#define RHI_ORACLE_MAXD_MAX 56u

typedef struct { f64 mae; u32 maxd; } RHIOracleResult;

/* RGBA8 帧 box-降采样到 GW x GH RGB 网格（grid 大小 RHI_ORACLE_GW*RHI_ORACLE_GH*3）。
 * w < GW 或 h < GH 的退化空 box 回退为最近源像素（真实帧恒 >= 网格，不会触发）。 */
void rhi_oracle_downsample(const u8 *rgba, u32 w, u32 h, u8 *grid);
bool rhi_oracle_write_ppm(const char *path, const u8 *grid);
/* 0 = 已比较（填充 out）；1 = 格式/尺寸不符；-1 = 参考缺失。 */
int  rhi_oracle_compare_ppm(const char *path, const u8 *grid, RHIOracleResult *out);
/* 完整判定：降采样 + GOLDEN_UPDATE=1 再生 + 容差判定 + reject_blank 防空图。 */
bool rhi_oracle_compare_frame(const u8 *shot_rgba, u32 w, u32 h,
                              const char *path, bool reject_blank);
/* R577 包装：frame_end 之后、present 之前捕获 presented 帧 RGBA8。 */
bool rhi_oracle_capture_presented(RHIDevice *dev, u32 w, u32 h, u8 *out_rgba);
