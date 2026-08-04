#include <ui/font.h>
#include <ui/utf8.h>
#include <core/log.h>
#include <core/shader_io.h>
#include <math/math.h>
#include <rhi/rhi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

/* Codepoint ranges baked into the atlas (inclusive). ASCII printable +
 * Latin-1 supplement covers western European accented letters and symbols. */
typedef struct { u32 first, last; } GlyphRange;
static const GlyphRange FONT_RANGES[] = {
    { 0x20, 0x7E },  /* Basic Latin (printable ASCII) */
    { 0xA0, 0xFF },  /* Latin-1 supplement            */
};
#define FONT_RANGE_COUNT (sizeof(FONT_RANGES) / sizeof(FONT_RANGES[0]))

/* R389: sfnt offset table size — the smallest a font file can possibly be. */
#define FONT_TTF_MIN_BYTES 12L

static const GlyphInfo *font_lookup_glyph(const FontRenderer *fr, u32 cp) {
    if (cp < FONT_CPMAP_SIZE) {
        i16 gi = fr->cp_map[cp];
        if (gi >= 0) return &fr->glyphs[gi];
    }
    /* Fallback to '?' so unknown codepoints stay visible. */
    if ('?' < FONT_CPMAP_SIZE && fr->cp_map['?'] >= 0)
        return &fr->glyphs[fr->cp_map['?']];
    return NULL;
}

/* R436: pure pair-table lookup. Linear scan over at most FONT_MAX_KERN_PAIRS
 * entries (96 for the shipped font) — negligible against glyph raster cost. */
f32 font_kern_advance(const FontRenderer *fr, u32 cp_a, u32 cp_b) {
    if (cp_a >= FONT_CPMAP_SIZE || cp_b >= FONT_CPMAP_SIZE) return 0.0f;
    i16 a = fr->cp_map[cp_a];
    i16 b = fr->cp_map[cp_b];
    if (a < 0 || b < 0) return 0.0f;
    for (u32 i = 0; i < fr->kern_count; i++) {
        if (fr->kern_pairs[i].a_idx == (u8)a && fr->kern_pairs[i].b_idx == (u8)b)
            return (f32)fr->kern_pairs[i].kern * (1.0f / 64.0f);
    }
    return 0.0f;
}

/* ---- R442: minimal GPOS PairPos extractor ---------------------------------
 *
 * stb_truetype only reads the legacy 'kern' table (format 0); fonts that kern
 * exclusively through GPOS (very common in modern fonts) bake an empty pair
 * table. This is a self-contained byte parser for the GPOS 'kern' feature's
 * Pair Adjustment Positioning subtables (OpenType spec: GPOS header ->
 * FeatureList ('kern') -> LookupList -> LookupType 2 -> PairPos Format 1).
 * PairPos Format 2 (class-based) subtables are skipped — see the Format-2
 * note below.
 *
 * This parses untrusted input, so the rule is: no byte is dereferenced until
 * a range check against the GPOS table length has proven it in bounds. All
 * multi-byte reads are explicit big-endian; counts and offsets are u16/u32
 * from the file and never trusted. Any inconsistency truncates the result,
 * never the process. */

/* Overflow-safe: [off, off+len) lies inside [0, n). */
static bool gpos_range_ok(usize n, usize off, usize len) {
    return off <= n && len <= n - off;
}
/* Callers must have proven p+2/p+4 in bounds via gpos_range_ok. */
static u16 gpos_u16(const u8 *p) { return (u16)(((u16)p[0] << 8) | p[1]); }
static u32 gpos_u32(const u8 *p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
}
static u32 gpos_popcount(u16 v) {
    u32 c = 0;
    while (v) { c += v & 1u; v >>= 1; }
    return c;
}

/* Coverage table: glyph id at coverage index `idx` (coverage indices are what
 * PairPos Format 1 pair sets key on). Returns false when idx is past the
 * covered glyphs or the table is malformed/unsupported. Format 2 range walks
 * are O(ranges) per call but callers visit indices ascending, so a cursor is
 * threaded through *cur_r / *cur_base to keep the total walk linear. */
static bool gpos_coverage_glyph(const u8 *g, usize gn, usize cov_off, u32 idx,
                                u32 *cur_r, u32 *cur_base, u16 *out) {
    if (!gpos_range_ok(gn, cov_off, 4)) return false;
    u16 fmt = gpos_u16(g + cov_off);
    if (fmt == 1) {
        u32 count = gpos_u16(g + cov_off + 2);
        if (idx >= count) return false;
        if (!gpos_range_ok(gn, cov_off + 4, (usize)count * 2)) return false;
        *out = gpos_u16(g + cov_off + 4 + (usize)idx * 2);
        return true;
    }
    if (fmt == 2) {
        u32 ranges = gpos_u16(g + cov_off + 2);
        if (!gpos_range_ok(gn, cov_off + 4, (usize)ranges * 6)) return false;
        /* Ranges are sorted and non-overlapping per spec, but a hostile file
         * could violate that; the walk still terminates and stays in bounds. */
        while (*cur_r < ranges) {
            const u8 *r = g + cov_off + 4 + (usize)(*cur_r) * 6;
            u32 start = gpos_u16(r), end = gpos_u16(r + 2);
            u32 cnt = end >= start ? end - start + 1 : 0;
            if (idx < *cur_base + cnt) {
                *out = (u16)(start + (idx - *cur_base));
                return true;
            }
            *cur_base += cnt;
            (*cur_r)++;
        }
        return false;
    }
    return false; /* unknown coverage format */
}

/* One PairPos Format 1 subtable: pair sets keyed by coverage index, each
 * record { secondGlyph, valueRecord1, valueRecord2 }. Only valueRecord1's
 * XAdvance is harvested (kerning is horizontal advance adjustment). */
static u32 gpos_pairpos_fmt1(const u8 *g, usize gn, usize st,
                             FontGposKern *out, u32 capacity, u32 count) {
    if (!gpos_range_ok(gn, st, 10)) return count;
    /* st+0 posFormat (==1, checked by caller), st+2 coverage, st+4/6 value
     * formats, st+8 pairSetCount. */
    usize cov_off = st + gpos_u16(g + st + 2);
    u16 vf1 = gpos_u16(g + st + 4);
    u16 vf2 = gpos_u16(g + st + 6);
    u32 psc = gpos_u16(g + st + 8);
    if (!gpos_range_ok(gn, st + 10, (usize)psc * 2)) return count;

    /* Value record stride: 2 bytes per set bit (x/y placement, x/y advance,
     * and the device/variation offset slots all occupy one field each).
     * XAdvance (bit 0x4) sits after XPlacement/YPlacement within record 1. */
    u32 rec = 2 + 2 * gpos_popcount(vf1) + 2 * gpos_popcount(vf2);
    bool has_xa = (vf1 & 0x4u) != 0;
    u32 xa_off = 2 + 2 * gpos_popcount((u16)(vf1 & 0x3u));

    u32 cur_r = 0, cur_base = 0; /* coverage format 2 cursor */
    for (u32 p = 0; p < psc && count < capacity; p++) {
        u16 g1;
        if (!gpos_coverage_glyph(g, gn, cov_off, p, &cur_r, &cur_base, &g1))
            break; /* fewer pair sets than covered glyphs: nothing more to do */
        usize ps = st + gpos_u16(g + st + 10 + (usize)p * 2);
        if (!gpos_range_ok(gn, ps, 2)) continue;
        u32 pvc = gpos_u16(g + ps);
        if (!gpos_range_ok(gn, ps + 2, (usize)pvc * rec)) continue;
        for (u32 q = 0; q < pvc && count < capacity; q++) {
            const u8 *rp = g + ps + 2 + (usize)q * rec;
            u16 g2 = gpos_u16(rp);
            i16 xa = has_xa ? (i16)gpos_u16(rp + xa_off) : 0;
            if (xa == 0) continue; /* only non-zero pairs are stored (R436) */
            out[count++] = (FontGposKern){ g1, g2, xa };
        }
    }
    return count;
}

u32 font_gpos_kern_extract(const u8 *ttf, usize ttf_size,
                           FontGposKern *out, u32 capacity) {
    if (!ttf || !out || capacity == 0) return 0;
    u32 count = 0;

    /* sfnt offset table + directory: locate 'GPOS' (stbtt__find_table is
     * stb-internal, hence this walk). TTC files are not handled — the bake
     * path rejects them before here via stbtt_GetFontOffsetForIndex. */
    if (!gpos_range_ok(ttf_size, 0, 12)) return 0;
    u32 num_tables = gpos_u16(ttf + 4);
    if (!gpos_range_ok(ttf_size, 12, (usize)num_tables * 16)) return 0;
    usize gpos_off = 0, gpos_len = 0;
    bool found = false;
    for (u32 i = 0; i < num_tables; i++) {
        const u8 *r = ttf + 12 + (usize)i * 16;
        if (memcmp(r, "GPOS", 4) == 0) {
            gpos_off = gpos_u32(r + 8);
            gpos_len = gpos_u32(r + 12);
            found = gpos_range_ok(ttf_size, gpos_off, gpos_len);
            break;
        }
    }
    if (!found) return 0;
    const u8 *g = ttf + gpos_off;
    const usize gn = gpos_len; /* every check below is against the table end */

    /* GPOS header: version(4), scriptList, featureList, lookupList offsets.
     * Version 1.1 appends a featureVariations offset we do not need. */
    if (!gpos_range_ok(gn, 0, 10)) return 0;
    usize fl = gpos_u16(g + 6);
    usize ll = gpos_u16(g + 8);

    /* FeatureList: collect lookup indices of every 'kern' feature. All
     * scripts/langsystems are taken together — kerning pairs are glyph-level
     * and the bake only ever queries glyphs it has, so a superset is safe
     * (e.g. LiberationSans has one Latin lookup and one Hebrew lookup). */
    if (!gpos_range_ok(gn, fl, 2)) return 0;
    u32 fcount = gpos_u16(g + fl);
    if (!gpos_range_ok(gn, fl + 2, (usize)fcount * 6)) return 0;
    u16 lookup_idx[64]; /* dedupe: the same lookup can serve many features */
    u32 n_lookups = 0;
    for (u32 i = 0; i < fcount; i++) {
        const u8 *rec = g + fl + 2 + (usize)i * 6;
        if (memcmp(rec, "kern", 4) != 0) continue;
        usize ft = fl + gpos_u16(rec + 4);
        if (!gpos_range_ok(gn, ft, 4)) continue;
        u32 lc = gpos_u16(g + ft + 2);
        if (!gpos_range_ok(gn, ft + 4, (usize)lc * 2)) continue;
        for (u32 j = 0; j < lc; j++) {
            u16 li = gpos_u16(g + ft + 4 + (usize)j * 2);
            bool seen = false;
            for (u32 k = 0; k < n_lookups; k++)
                if (lookup_idx[k] == li) { seen = true; break; }
            if (!seen && n_lookups < 64) lookup_idx[n_lookups++] = li;
        }
    }
    if (n_lookups == 0) return 0;

    /* LookupList: walk the collected lookups, harvest PairPos subtables. */
    if (!gpos_range_ok(gn, ll, 2)) return 0;
    u32 lcount = gpos_u16(g + ll);
    if (!gpos_range_ok(gn, ll + 2, (usize)lcount * 2)) return 0;
    for (u32 i = 0; i < n_lookups && count < capacity; i++) {
        if (lookup_idx[i] >= lcount) continue;
        usize lo = ll + gpos_u16(g + ll + 2 + (usize)lookup_idx[i] * 2);
        if (!gpos_range_ok(gn, lo, 6)) continue;
        if (gpos_u16(g + lo) != 2) continue; /* LookupType 2 = Pair Adjustment */
        u32 stc = gpos_u16(g + lo + 4);
        if (!gpos_range_ok(gn, lo + 6, (usize)stc * 2)) continue;
        for (u32 s = 0; s < stc && count < capacity; s++) {
            usize st = lo + gpos_u16(g + lo + 6 + (usize)s * 2);
            if (!gpos_range_ok(gn, st, 2)) continue;
            u16 fmt = gpos_u16(g + st);
            if (fmt == 1) {
                count = gpos_pairpos_fmt1(g, gn, st, out, capacity, count);
            }
            /* R442: PairPos Format 2 (class-based) is skipped. LiberationSans
             * — the shipped font and cross-validation oracle — kerns entirely
             * through Format 1, so Format 2 is untestable here, and an
             * untested binary parser is worse than a documented gap: fonts
             * whose kerning lives only in Format 2 simply get no GPOS
             * fallback, exactly the pre-R442 behavior. */
        }
    }
    return count;
}

extern RHIDevice *g_current_device;

typedef struct {
    f32 x, y;
    f32 u, v;
    f32 r, g, b, a;
} FontVertex;

bool font_renderer_init(FontRenderer *fr, RHIDevice *dev, const char *ttf_path, f32 font_size) {
    memset(fr, 0, sizeof(*fr));
    fr->device = dev;
    fr->font_size = font_size;

    FILE *f = fopen(ttf_path, "rb");
    if (!f) {
        LOG_WARN("Font: cannot open %s", ttf_path);
        return false;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return false; }
    long sz = ftell(f);
    /* R389: `sz < 0` let a zero-byte file through: malloc(0) returns a minimal
     * block and stbtt then reads the sfnt tag straight out of bounds (ASan:
     * 1-byte READ in stbtt__isfont, reached before any RHI call). An empty or
     * truncated font file on disk is enough to trigger it.
     *
     * FONT_TTF_MIN_BYTES is the sfnt offset table: sfntVersion(4) +
     * numTables(2) + searchRange(2) + entrySelector(2) + rangeShift(2). Nothing
     * smaller can be a font.
     *
     * This bounds the empty/truncated case only. stb_truetype does not bounds
     * check the input beyond it — a font declaring a bogus numTables still walks
     * its table directory past EOF — so font files must remain trusted assets.
     * See docs/Round11_Performance_Plan.md (R389) for why that is left alone. */
    if (sz < FONT_TTF_MIN_BYTES) {
        LOG_WARN("Font: %s is too small to be a font (%ld bytes)", ttf_path, sz);
        fclose(f);
        return false;
    }
    if ((u64)sz > (u64)FONT_TTF_MAX_BYTES) {
        LOG_WARN("Font: %s too large (%ld bytes)", ttf_path, sz);
        fclose(f);
        return false;
    }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return false; }
    u8 *ttf_buf = malloc((usize)sz);
    if (!ttf_buf) { fclose(f); return false; }
    if (fread(ttf_buf, 1, (usize)sz, f) != (usize)sz) {
        /* R143: Check fread return — truncated TTF could cause stbtt UB */
        free(ttf_buf); fclose(f); return false;
    }
    fclose(f);

    /* R389: stbtt_GetFontOffsetForIndex returns -1 for "not a font", and that was
     * fed straight into stbtt_InitFont. Its `fontstart` parameter is
     * stbtt_uint32, so -1 became 0xFFFFFFFF and stbtt__find_table read at
     * `data + 0xFFFFFFFF + 4` — a wild pointer, hard SEGV (ASan: READ at
     * data+0x100000003). Any file that is not a font triggers it: a mistyped
     * path, a stray text file, a corrupted or truncated asset. Reject the
     * sentinel before parsing. */
    int font_offset = stbtt_GetFontOffsetForIndex(ttf_buf, 0);
    if (font_offset < 0 || (long)font_offset >= sz) {
        LOG_WARN("Font: %s is not a font file", ttf_path);
        free(ttf_buf);
        return false;
    }

    stbtt_fontinfo fi;
    if (!stbtt_InitFont(&fi, ttf_buf, font_offset)) {
        LOG_WARN("Font: stbtt_InitFont failed");
        free(ttf_buf);
        return false;
    }

    f32 scale = stbtt_ScaleForPixelHeight(&fi, font_size);

    int iascent, idescent, ilinegap;
    stbtt_GetFontVMetrics(&fi, &iascent, &idescent, &ilinegap);
    fr->ascent = (f32)iascent * scale;
    fr->descent = (f32)idescent * scale;
    fr->line_gap = (f32)ilinegap * scale;

    u8 *atlas = calloc(FONT_ATLAS_SIZE * FONT_ATLAS_SIZE, 1);
    if (!atlas) { free(ttf_buf); return false; }

    for (u32 i = 0; i < FONT_CPMAP_SIZE; i++) fr->cp_map[i] = -1;
    fr->glyph_count = 0;

    /* Reserve a small opaque white patch at the top-left for solid-fill quads.
     * Sample its center so linear filtering never picks transparent neighbors. */
    const u32 WHITE_PATCH = 4;
    for (u32 wy = 0; wy < WHITE_PATCH; wy++)
        for (u32 wx = 0; wx < WHITE_PATCH; wx++)
            atlas[wy * FONT_ATLAS_SIZE + wx] = 255;
    fr->white_u = 2.0f / (f32)FONT_ATLAS_SIZE;
    fr->white_v = 2.0f / (f32)FONT_ATLAS_SIZE;

    u32 px = WHITE_PATCH + 1;
    u32 py = 1;
    u32 row_height = 0;

    for (u32 ri = 0; ri < FONT_RANGE_COUNT; ri++) {
        for (u32 cp = FONT_RANGES[ri].first; cp <= FONT_RANGES[ri].last; cp++) {
            if (fr->glyph_count >= FONT_MAX_GLYPHS) break;

            int advance, lsb;
            stbtt_GetCodepointHMetrics(&fi, (int)cp, &advance, &lsb);

            /* R439: bake a signed distance field instead of a coverage bitmap
             * — the atlas stays single-channel and layout (advance) is
             * unchanged, but magnification no longer pixelates.
             * stbtt_GetCodepointSDF returns NULL for outline-less glyphs
             * (space etc.) leaving gw/gh at 0; on success its x0/y0 already
             * include FONT_SDF_PADDING, so quad geometry below just works. */
            int x0 = 0, y0 = 0, gw = 0, gh = 0;
            unsigned char *sdf = stbtt_GetCodepointSDF(&fi, scale, (int)cp,
                FONT_SDF_PADDING, FONT_SDF_ONEDGE, FONT_SDF_DIST_SCALE,
                &gw, &gh, &x0, &y0);

            if (px + (u32)gw + 1 >= FONT_ATLAS_SIZE) {
                px = 1;
                py += row_height + 1;
                row_height = 0;
            }
            if (py + (u32)gh + 1 >= FONT_ATLAS_SIZE) {
                LOG_WARN("Font: atlas overflow at codepoint U+%04X", cp);
                stbtt_FreeSDF(sdf, NULL);
                break;
            }

            if (sdf) {
                for (int row = 0; row < gh; row++)
                    memcpy(atlas + (usize)(py + (u32)row) * FONT_ATLAS_SIZE + px,
                           sdf + (usize)row * (usize)gw, (usize)gw);
                stbtt_FreeSDF(sdf, NULL);
            }

            u32 gi = fr->glyph_count++;
            fr->glyphs[gi].codepoint = cp;
            fr->glyphs[gi].advance = (f32)advance * scale;
            fr->glyphs[gi].x_off = (f32)x0;
            fr->glyphs[gi].y_off = (f32)y0;
            fr->glyphs[gi].width = (f32)gw;
            fr->glyphs[gi].height = (f32)gh;
            fr->glyphs[gi].uv.x0 = (f32)px / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.y0 = (f32)py / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.x1 = (f32)(px + gw) / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.y1 = (f32)(py + gh) / (f32)FONT_ATLAS_SIZE;
            if (cp < FONT_CPMAP_SIZE) fr->cp_map[cp] = (i16)gi;

            px += (u32)gw + 1;
            if ((u32)gh + 1 > row_height) row_height = (u32)gh + 1;
        }
    }

    /* R436: harvest kerning pairs while the stbtt handle is still alive (it
     * borrows ttf_buf, so this must precede the free below). stb_truetype only
     * reads the legacy 'kern' table (format 0); fonts that kern exclusively
     * through GPOS yield an empty table and layout falls back to pure advance
     * accumulation — identical to pre-R436 behavior.
     *
     * Only non-zero pairs are stored. Capacity policy is first-come-first-
     * served: pairs are visited in codepoint order, so if the table fills, the
     * dropped pairs are the high-codepoint ones rather than the largest — with
     * 512 slots versus 96 pairs in the shipped font this is not a practical
     * concern, and it keeps baking O(glyphs^2) with no sorting. */
    fr->kern_count = 0;
    for (u32 i = 0; i < fr->glyph_count && fr->kern_count < FONT_MAX_KERN_PAIRS; i++) {
        for (u32 j = 0; j < fr->glyph_count && fr->kern_count < FONT_MAX_KERN_PAIRS; j++) {
            int k = stbtt_GetCodepointKernAdvance(&fi,
                (int)fr->glyphs[i].codepoint, (int)fr->glyphs[j].codepoint);
            if (k == 0) continue;
            f32 kf = (f32)k * scale * 64.0f; /* fixed-point 1/64 px */
            i32 k64 = (i32)(kf >= 0.0f ? kf + 0.5f : kf - 0.5f);
            if (k64 == 0) continue;         /* rounds away to nothing */
            if (k64 > 32767) k64 = 32767;   /* i16 storage clamp */
            if (k64 < -32768) k64 = -32768;
            fr->kern_pairs[fr->kern_count++] =
                (FontKernPair){ (u8)i, (u8)j, (i16)k64 };
        }
    }

    /* R442: the legacy harvest above comes out empty for GPOS-only fonts.
     * Fall back to the GPOS PairPos extractor, filling the same sparse table
     * with the same fixed-point scaling, so font_kern_advance and everything
     * downstream stay untouched. GPOS pairs are glyph-id keyed, so a reverse
     * map (ttf glyph id -> baked glyph index) bridges them into the baked
     * ranges; pairs involving unbaked glyphs are dropped. */
    if (fr->kern_count == 0) {
        #define FONT_GPOS_EXTRACT_CAP 4096 /* recon: 2015 pairs in LiberationSans */
        FontGposKern *gp = malloc(sizeof(FontGposKern) * FONT_GPOS_EXTRACT_CAP);
        if (gp) {
            u32 gn = font_gpos_kern_extract(ttf_buf, (usize)sz, gp,
                                            FONT_GPOS_EXTRACT_CAP);
            i32 gid[FONT_MAX_GLYPHS];
            for (u32 i = 0; i < fr->glyph_count; i++)
                gid[i] = stbtt_FindGlyphIndex(&fi, (int)fr->glyphs[i].codepoint);
            for (u32 p = 0; p < gn && fr->kern_count < FONT_MAX_KERN_PAIRS; p++) {
                i32 ia = -1, ib = -1;
                for (u32 i = 0; i < fr->glyph_count; i++) {
                    if (gid[i] == gp[p].glyph_a) ia = (i32)i;
                    if (gid[i] == gp[p].glyph_b) ib = (i32)i;
                }
                if (ia < 0 || ib < 0) continue;
                f32 kf = (f32)gp[p].x_advance * scale * 64.0f;
                i32 k64 = (i32)(kf >= 0.0f ? kf + 0.5f : kf - 0.5f);
                if (k64 == 0) continue;
                if (k64 > 32767) k64 = 32767;
                if (k64 < -32768) k64 = -32768;
                fr->kern_pairs[fr->kern_count++] =
                    (FontKernPair){ (u8)ia, (u8)ib, (i16)k64 };
            }
            free(gp);
            if (gn > 0)
                LOG_INFO("Font: legacy kern table empty, baked %u GPOS pairs",
                         fr->kern_count);
        }
    }

    free(ttf_buf);

    RHITextureDesc tdesc;
    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = FONT_ATLAS_SIZE;
    tdesc.height = FONT_ATLAS_SIZE;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1;

    u32 atlas_rgba_size = FONT_ATLAS_SIZE * FONT_ATLAS_SIZE * 4;
    u8 *atlas_rgba = malloc(atlas_rgba_size);
    if (!atlas_rgba) { free(atlas); return false; }
    for (u32 i = 0; i < FONT_ATLAS_SIZE * FONT_ATLAS_SIZE; i++) {
        atlas_rgba[i * 4 + 0] = 255;
        atlas_rgba[i * 4 + 1] = 255;
        atlas_rgba[i * 4 + 2] = 255;
        atlas_rgba[i * 4 + 3] = atlas[i];
    }
    free(atlas);
    tdesc.data = atlas_rgba;

    fr->atlas_tex = rhi_texture_create(dev, &tdesc);
    free(atlas_rgba);
    if (!rhi_handle_valid(fr->atlas_tex)) {
        LOG_WARN("Font: atlas texture creation failed");
        /* R386: every bail below this point must release what init already
         * created — callers treat `false` as "nothing to shut down". */
        font_renderer_shutdown(fr);
        return false;
    }

    RHISamplerDesc sdesc;
    memset(&sdesc, 0, sizeof(sdesc));
    sdesc.min_filter = RHI_FILTER_LINEAR;
    sdesc.mag_filter = RHI_FILTER_LINEAR;
    sdesc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_v = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
    fr->sampler = rhi_sampler_create(dev, &sdesc);
    if (!rhi_handle_valid(fr->sampler)) {
        LOG_WARN("Font: sampler creation failed");
        font_renderer_shutdown(fr);
        return false;
    }

    const char *vert_path =
#ifdef ENGINE_VULKAN
        "shaders/font_vk.vert";
#else
        "shaders/font.vert";
#endif
    const char *frag_path =
#ifdef ENGINE_VULKAN
        "shaders/font_vk.frag";
#else
        "shaders/font.frag";
#endif

    usize vs_len = 0, fs_len = 0;
    char *vs_src = shader_read_file(vert_path, &vs_len);
    char *fs_src = shader_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("Font: shaders not found (%s / %s)", vert_path, frag_path);
        free(vs_src); free(fs_src);
        font_renderer_shutdown(fr);
        return false;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Font: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        font_renderer_shutdown(fr);
        return false;
    }

    RHIPipelineDesc pdesc;
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs;
    pdesc.frag = fs;
    pdesc.vertex_stride = 32;
    pdesc.uses_textures = true;
    pdesc.depth_write_disable = true;
    pdesc.disable_culling = true;
    pdesc.alpha_blend = true;
    pdesc.font_vertex = true;
    fr->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(fr->pipeline)) {
        LOG_WARN("Font: pipeline creation failed");
        font_renderer_shutdown(fr);
        return false;
    }

    fr->quad_capacity = 4096;
    fr->quad_data = malloc(fr->quad_capacity * 6 * sizeof(FontVertex));
    if (!fr->quad_data) {
        LOG_WARN("Font: quad data allocation failed");
        font_renderer_shutdown(fr);
        return false;
    }
    fr->quad_count = 0;

    RHIBufferDesc bdesc;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = fr->quad_capacity * 6 * sizeof(FontVertex);
    fr->vbo[0] = rhi_buffer_create(dev, &bdesc);
    fr->vbo[1] = rhi_buffer_create(dev, &bdesc);
    if (!rhi_handle_valid(fr->vbo[0]) || !rhi_handle_valid(fr->vbo[1])) {
        LOG_WARN("Font: VBO creation failed");
        font_renderer_shutdown(fr);
        return false;
    }

    LOG_INFO("Font: initialized (%.0fpx, atlas %ux%u, %u glyphs)", font_size,
        FONT_ATLAS_SIZE, FONT_ATLAS_SIZE, fr->glyph_count);
    return true;
}

void font_renderer_shutdown(FontRenderer *fr) {
    if (!fr) return;
    /* R386: mirrors R383's terrain_shutdown — quad_data does not need a device,
     * so a device-less FontRenderer must not skip straight past the free. */
    if (fr->device) {
        if (rhi_handle_valid(fr->vbo[0])) rhi_buffer_destroy(fr->device, fr->vbo[0]);
        if (rhi_handle_valid(fr->vbo[1])) rhi_buffer_destroy(fr->device, fr->vbo[1]);
        if (rhi_handle_valid(fr->sampler)) rhi_sampler_destroy(fr->device, fr->sampler);
        if (rhi_handle_valid(fr->atlas_tex)) rhi_texture_destroy(fr->device, fr->atlas_tex);
        if (rhi_handle_valid(fr->pipeline)) rhi_pipeline_destroy(fr->device, fr->pipeline);
    }
    free(fr->quad_data);
    memset(fr, 0, sizeof(*fr));
}

void font_renderer_begin(FontRenderer *fr) {
    fr->quad_count = 0;
}

void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                         f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    /* R244: A minimized/zero-size window yields screen_w/h == 0; the pixel->NDC
     * divides below would then emit ±Inf/NaN vertices into the draw buffer. */
    if (screen_w <= 0.0f || screen_h <= 0.0f) return;
    f32 cursor_x = x;
    f32 cursor_y = y + fr->ascent;
    f32 inv_sh = 2.0f / screen_h;
    f32 inv_sw = 2.0f / screen_w;

    const char *s = text;
    u32 prev_cp = 0; /* R436: effective codepoint of the previous glyph, 0 = none */
    while (*s) {
        u32 cp;
        s += utf8_decode(s, &cp);
        if (cp == '\n') {
            cursor_x = x;
            cursor_y += fr->ascent - fr->descent + fr->line_gap;
            prev_cp = 0; /* R436: kerning never crosses a line break */
            continue;
        }

        const GlyphInfo *gi = font_lookup_glyph(fr, cp);
        if (!gi) { prev_cp = 0; continue; }
        /* R436: kern against the previous glyph before advancing. gi->codepoint
         * is the effective codepoint, so '?' fallback pairs kern correctly. */
        cursor_x += font_kern_advance(fr, prev_cp, gi->codepoint);
        prev_cp = gi->codepoint;
        if (gi->width <= 0 || gi->height <= 0) {
            cursor_x += gi->advance;
            continue;
        }

        f32 qx = cursor_x + gi->x_off;
        f32 qy = cursor_y + gi->y_off;
        f32 qw = gi->width;
        f32 qh = gi->height;

        f32 x0 = qx * inv_sw - 1.0f;
        f32 y0 = 1.0f - qy * inv_sh;
        f32 x1 = (qx + qw) * inv_sw - 1.0f;
        f32 y1 = 1.0f - (qy + qh) * inv_sh;

        if (fr->quad_count >= fr->quad_capacity) break;
        usize base = (usize)fr->quad_count * 6 * sizeof(FontVertex);
        FontVertex *dst = (FontVertex *)(fr->quad_data + base);
        dst[0] = (FontVertex){x0, y0, gi->uv.x0, gi->uv.y0, r, g, b, a};
        dst[1] = (FontVertex){x1, y0, gi->uv.x1, gi->uv.y0, r, g, b, a};
        dst[2] = (FontVertex){x0, y1, gi->uv.x0, gi->uv.y1, r, g, b, a};
        dst[3] = (FontVertex){x1, y0, gi->uv.x1, gi->uv.y0, r, g, b, a};
        dst[4] = (FontVertex){x1, y1, gi->uv.x1, gi->uv.y1, r, g, b, a};
        dst[5] = (FontVertex){x0, y1, gi->uv.x0, gi->uv.y1, r, g, b, a};
        fr->quad_count++;
        cursor_x += gi->advance;
    }
}

void font_renderer_draw_rect(FontRenderer *fr, f32 x, f32 y, f32 w, f32 h,
                             f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    if (w <= 0.0f || h <= 0.0f) return;
    if (screen_w <= 0.0f || screen_h <= 0.0f) return; /* R244: avoid ±Inf/NaN */
    if (fr->quad_count >= fr->quad_capacity) return;

    f32 inv_sw = 2.0f / screen_w;
    f32 inv_sh = 2.0f / screen_h;
    f32 x0 = x * inv_sw - 1.0f;
    f32 y0 = 1.0f - y * inv_sh;
    f32 x1 = (x + w) * inv_sw - 1.0f;
    f32 y1 = 1.0f - (y + h) * inv_sh;

    f32 u = fr->white_u, vv = fr->white_v;

    usize base = (usize)fr->quad_count * 6 * sizeof(FontVertex);
    FontVertex *dst = (FontVertex *)(fr->quad_data + base);
    dst[0] = (FontVertex){x0, y0, u, vv, r, g, b, a};
    dst[1] = (FontVertex){x1, y0, u, vv, r, g, b, a};
    dst[2] = (FontVertex){x0, y1, u, vv, r, g, b, a};
    dst[3] = (FontVertex){x1, y0, u, vv, r, g, b, a};
    dst[4] = (FontVertex){x1, y1, u, vv, r, g, b, a};
    dst[5] = (FontVertex){x0, y1, u, vv, r, g, b, a};
    fr->quad_count++;
}

f32 font_renderer_text_width(const FontRenderer *fr, const char *text) {
    f32 w = 0.0f, line_w = 0.0f;
    u32 prev_cp = 0; /* R436: effective codepoint of the previous glyph, 0 = none */
    const char *s = text;
    while (*s) {
        u32 cp;
        s += utf8_decode(s, &cp);
        if (cp == '\n') {
            if (line_w > w) w = line_w;
            line_w = 0.0f;
            prev_cp = 0; /* R436: kerning never crosses a line break */
            continue;
        }
        const GlyphInfo *gi = font_lookup_glyph(fr, cp);
        if (!gi) { prev_cp = 0; continue; }
        /* R436: keep in lockstep with font_renderer_draw — same kern, same
         * effective codepoint — or UI alignment drifts from what is rendered. */
        line_w += font_kern_advance(fr, prev_cp, gi->codepoint);
        prev_cp = gi->codepoint;
        line_w += gi->advance;
    }
    return line_w > w ? line_w : w;
}

f32 font_renderer_line_height(const FontRenderer *fr) {
    return fr->ascent - fr->descent + fr->line_gap;
}

void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h) {
    (void)screen_w; (void)screen_h;
    if (fr->quad_count == 0) return;

    usize data_size = (usize)fr->quad_count * 6 * sizeof(FontVertex);
    /* R184: dual-slot — avoid host write racing prior frame's VS read. */
    RHIBuffer slot = fr->vbo[rhi_frame_index(fr->device) & 1u];
    rhi_buffer_update(fr->device, slot, fr->quad_data, data_size);

    rhi_cmd_bind_pipeline(cmd, fr->pipeline);
    rhi_cmd_bind_texture(cmd, fr->atlas_tex, fr->sampler, 0);
    rhi_cmd_set_uniform_vec4(cmd, 0, 1.0f, 1.0f, 1.0f, 1.0f);
    rhi_cmd_bind_vertex_buffer(cmd, slot, 0);
    rhi_cmd_draw(cmd, fr->quad_count * 6, 1);
}
