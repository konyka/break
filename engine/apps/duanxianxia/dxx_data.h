/**
 * @file dxx_data.h
 * @brief duanxianxia clone: static snapshot data (M14b).
 *
 * Index quotes: 5 of 12 rows are REAL values fetched from sina
 * (hq.sinajs.cn) on 2026-08-12 ~14:20 CST (上证指数/深证成指/创业板指/
 * 上证50/沪深300; the two sh* rows had their change computed from the
 * previous close). The HK/futures/CSI2000/FTSE-A50 rows came back empty
 * from the endpoint, so they hold plausible static approximations —
 * marked "约值" below. See docs/apps/duanxianxia.md.
 */
#ifndef DXX_DATA_H
#define DXX_DATA_H

#include <stdint.h>

/** @brief One index quote row (name + last + change%). */
typedef struct dxx_index_quote_t {
  const char* name;    /**< static string */
  double value;        /**< last price / index value */
  double change_pct;   /**< signed percent, e.g. +0.21 */
} dxx_index_quote_t;

#define DXX_INDEX_COUNT 12

/** @brief The 12 indices of the header strip, in site order. */
extern const dxx_index_quote_t DXX_INDICES[DXX_INDEX_COUNT];

/** @brief Footer disclaimer line (verbatim from the site). */
extern const char* const DXX_FOOTER_DISCLAIMER;
/** @brief Footer ICP/contact line (verbatim from the site). */
extern const char* const DXX_FOOTER_ICP;

/* ---------------- M14c: live feeds (SIMULATED) + zt pool snapshot ---- */

/** @brief One live-feed line: "HH:MM" + text. */
typedef struct dxx_live_item_t {
  const char* time; /**< "HH:MM" static */
  const char* text; /**< static */
} dxx_live_item_t;

#define DXX_LIVE_EMOTION_COUNT 20
#define DXX_LIVE_ZT_COUNT 12
#define DXX_LIVE_YIDONG_COUNT 8

/** @brief 情绪直播 / 涨停直播 / 异动 lines (SIMULATED content). */
extern const dxx_live_item_t DXX_LIVE_EMOTION[DXX_LIVE_EMOTION_COUNT];
extern const dxx_live_item_t DXX_LIVE_ZT[DXX_LIVE_ZT_COUNT];
extern const dxx_live_item_t DXX_LIVE_YIDONG[DXX_LIVE_YIDONG_COUNT];

/** @brief 股票池 card row (SIMULATED): code/name/speed/turnover. */
typedef struct dxx_watch_row_t {
  const char* code;
  const char* name;
  double speed_pct;   /**< 涨速 %, signed */
  double turnover_pct;/**< 换手 % */
} dxx_watch_row_t;

#define DXX_WATCH_COUNT 10
extern const dxx_watch_row_t DXX_WATCH[DXX_WATCH_COUNT];

/** @brief 成交额 card numbers (SIMULATED). */
extern const char* const DXX_AMOUNT_MAIN;   /**< e.g. "1.85万亿" */
extern const char* const DXX_AMOUNT_SUB;    /**< e.g. "较昨日 +12.3%" */

/* ---------------- 涨停股票池（晋级天梯）snapshot 2026-08-04 ------------ */

/** @brief Market tag of a stock (badge letter/color). */
typedef enum dxx_market_t {
  DXX_MKT_SH = 0, /**< 沪 */
  DXX_MKT_SZ,     /**< 深 */
  DXX_MKT_CY,     /**< 创 */
  DXX_MKT_KC,     /**< 科 */
  DXX_MKT_BJ      /**< 北 */
} dxx_market_t;

/** @brief Promotion outcome of a stock in the pool. */
typedef enum dxx_stock_state_t {
  DXX_ST_SUCCESS = 0, /**< 成 (promoted: red bold) */
  DXX_ST_FAIL,        /**< 败 (green) */
  DXX_ST_BROKEN       /**< 炸 (opened limit: orange) */
} dxx_stock_state_t;

/** @brief One stock entry (static snapshot row). */
typedef struct dxx_stock_t {
  dxx_market_t market;
  const char* name;      /**< static */
  dxx_stock_state_t state;
  double change_pct;     /**< signed percent */
  const char* theme;     /**< static; NULL = 无题材 */
} dxx_stock_t;

/** @brief One promotion-ladder row (e.g. 2进3). */
typedef struct dxx_pool_row_t {
  const char* progress; /**< "2进3" */
  const char* rate;     /**< "7/12=58%" verbatim */
  const dxx_stock_t* stocks;
  int stock_count;
} dxx_pool_row_t;

#define DXX_POOL_ROW_COUNT 6
/** @brief The six ladder rows: 6进7/4进5/3进4/2进3/1进2/首板. */
extern const dxx_pool_row_t DXX_POOL_ROWS[DXX_POOL_ROW_COUNT];

/* ---------------- M15: 情绪直播 stats + charts (SIMULATED) ------------ */

/** @brief One stat button of the qxlive panel (values are a SIMULATED
 * snapshot, see dxx_data.c). series = index into DXX_SERIES or -1. */
typedef struct dxx_stat_t {
  const char* label;     /**< e.g. "情绪指标" */
  const char* value;     /**< e.g. "62"; NULL = no value (量能) */
  uint32_t bg;           /**< button background */
  uint32_t fg;           /**< label text color */
  uint32_t value_color;  /**< value text color (white buttons: red/green) */
  int series;            /**< DXX_SERIES index, -1 = no curve */
} dxx_stat_t;

#define DXX_STAT_COUNT 12
extern const dxx_stat_t DXX_STATS[DXX_STAT_COUNT];

/** @brief One intraday curve (SIMULATED): 5-minute samples 09:30-15:00. */
typedef struct dxx_series_t {
  const char* name;
  const float* points;
  int count;
  float ymin;
  float ymax;
} dxx_series_t;

#define DXX_SERIES_COUNT 3
/** @brief 0=情绪指标 1=涨停家数 2=跌停家数 (SIMULATED curves). */
extern const dxx_series_t DXX_SERIES[DXX_SERIES_COUNT];

#define DXX_DIST_COUNT 11
/** @brief 涨幅分布 buckets (SIMULATED), echarts 风格横向条形：
 * 跌幅档 5 + 平盘 + 涨幅档 5（家数，非负）。标签见 DXX_DIST_LABELS。 */
extern const float DXX_DIST[DXX_DIST_COUNT];
/** @brief Bucket labels top->bottom: 跌停档 -> 平盘 -> 涨停档. */
extern const char* const DXX_DIST_LABELS[DXX_DIST_COUNT];

#endif /* DXX_DATA_H */
