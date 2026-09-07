#ifndef PLATFORM_DISPLAY_MEDIA_H
#define PLATFORM_DISPLAY_MEDIA_H

#include <platform/platform.h>

bool platform_display_parse_edid(const unsigned char *data, usize length,
                                 u32 *capabilities, bool *gamut_known,
                                 bool *hdr_known);

#endif
