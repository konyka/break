#ifndef PLATFORM_DISPLAY_MEDIA_H
#define PLATFORM_DISPLAY_MEDIA_H

#include <platform/platform.h>

bool platform_display_parse_edid(const unsigned char *data, usize length,
                                 u32 *capabilities, bool *gamut_known,
                                 bool *hdr_known);

#if defined(__linux__)
/* Reads the EDID of the DRM connector `connector` (a Wayland xdg_output name
 * such as "eDP-1") from <drm_root>/card<N>-<connector>/edid and parses it with
 * platform_display_parse_edid. `drm_root` is normally "/sys/class/drm".
 * At most the base block plus the parser's extension limit is read. The
 * file path comes from the matching directory entry, never from `connector`.
 * False, with every output cleared, for NULL arguments, an empty connector
 * name, no matching connector, an empty file (disconnected) or an EDID the
 * parser rejects.
 * Cold path: opens a directory and a file. */
bool platform_display_read_connector_edid(const char *drm_root, const char *connector,
                                          u32 *capabilities, bool *gamut_known,
                                          bool *hdr_known);

/* The wide-gamut and HDR facts that hold on every one of the `count` outputs:
 * *capabilities gets PLATFORM_MEDIA_CAP_COLOR_P3/REC2020/HDR and *known gets
 * PLATFORM_MEDIA_KNOWN_COLOR_GAMUT/HDR only when every output's EDID states
 * them. One output without a usable EDID clears both, so nothing is claimed
 * for a window that may be shown on it. sRGB is not reported: the caller
 * keeps its own baseline. NULL `names` or zero `count` clears both; a NULL
 * output pointer is skipped. */
void platform_display_outputs_media(const char *drm_root, const char *const *names,
                                    u32 count, u32 *capabilities, u32 *known);
#endif

#endif
