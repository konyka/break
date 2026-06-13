/*
 * Binary packet serialization with little-endian wire format.
 *
 * Header layout (12 bytes):
 *   [sequence:4 LE][ack:4 LE][size:2 LE][type:1][flags:1]
 *
 * All multi-byte fields are explicitly encoded as little-endian, so the wire
 * format is identical regardless of host byte order.
 */

#include "packet.h"

#include <string.h>

/* ---- internal LE encoders/decoders ---- */

static void le_write_u16(u8 *dst, u16 v)
{
    dst[0] = (u8)(v & 0xFFu);
    dst[1] = (u8)((v >> 8) & 0xFFu);
}

static void le_write_u32(u8 *dst, u32 v)
{
    dst[0] = (u8)(v & 0xFFu);
    dst[1] = (u8)((v >> 8) & 0xFFu);
    dst[2] = (u8)((v >> 16) & 0xFFu);
    dst[3] = (u8)((v >> 24) & 0xFFu);
}

static u16 le_read_u16(const u8 *src)
{
    return (u16)((u16)src[0] | ((u16)src[1] << 8));
}

static u32 le_read_u32(const u8 *src)
{
    return (u32)src[0]
         | ((u32)src[1] << 8)
         | ((u32)src[2] << 16)
         | ((u32)src[3] << 24);
}

/* Bounds-check write of `n` bytes; returns true if write fits. */
static bool packet_can_write(const PacketBuffer *buf, u32 n)
{
    if (!buf) return false;
    return (buf->write_pos + n) <= PACKET_MAX_SIZE;
}

static bool packet_can_read(const PacketBuffer *buf, u32 n)
{
    if (!buf) return false;
    return (buf->read_pos + n) <= PACKET_MAX_SIZE;
}

/* ---- Serialization ---- */

void packet_begin(PacketBuffer *buf, u8 type, u8 flags)
{
    if (!buf) return;
    memset(buf, 0, sizeof(*buf));
    /* Reserve header space (sequence/ack/size patched in packet_finish). */
    buf->write_pos = PACKET_HEADER_SIZE;
    buf->read_pos  = 0;
    /* type and flags live at fixed header offsets — write them now. */
    buf->data[10] = type;
    buf->data[11] = flags;
}

void packet_write_u8(PacketBuffer *buf, u8 val)
{
    if (!packet_can_write(buf, 1)) return;
    buf->data[buf->write_pos] = val;
    buf->write_pos += 1;
}

void packet_write_u16(PacketBuffer *buf, u16 val)
{
    if (!packet_can_write(buf, 2)) return;
    le_write_u16(&buf->data[buf->write_pos], val);
    buf->write_pos += 2;
}

void packet_write_u32(PacketBuffer *buf, u32 val)
{
    if (!packet_can_write(buf, 4)) return;
    le_write_u32(&buf->data[buf->write_pos], val);
    buf->write_pos += 4;
}

void packet_write_f32(PacketBuffer *buf, f32 val)
{
    /* IEEE-754 single-precision, transmitted byte-identical via aliasing copy. */
    u32 bits;
    if (!packet_can_write(buf, 4)) return;
    memcpy(&bits, &val, sizeof(bits));
    le_write_u32(&buf->data[buf->write_pos], bits);
    buf->write_pos += 4;
}

void packet_write_bytes(PacketBuffer *buf, const void *data, u32 size)
{
    if (!buf || !data || size == 0) return;
    if (!packet_can_write(buf, size)) return;
    memcpy(&buf->data[buf->write_pos], data, size);
    buf->write_pos += size;
}

u32 packet_finish(PacketBuffer *buf, u32 sequence, u32 ack)
{
    if (!buf) return 0;
    if (buf->write_pos < PACKET_HEADER_SIZE) {
        /* packet_begin was never called — patch in a default header. */
        memset(buf->data, 0, PACKET_HEADER_SIZE);
        buf->write_pos = PACKET_HEADER_SIZE;
    }

    u16 payload_size = (u16)(buf->write_pos - PACKET_HEADER_SIZE);

    le_write_u32(&buf->data[0], sequence);
    le_write_u32(&buf->data[4], ack);
    le_write_u16(&buf->data[8], payload_size);
    /* data[10] = type, data[11] = flags already set by packet_begin. */

    return buf->write_pos;
}

/* ---- Deserialization ---- */

bool packet_parse_header(const void *data, u32 size, PacketHeader *out_header)
{
    if (!data || !out_header || size < PACKET_HEADER_SIZE) return false;
    const u8 *p = (const u8 *)data;
    out_header->sequence = le_read_u32(&p[0]);
    out_header->ack      = le_read_u32(&p[4]);
    out_header->size     = le_read_u16(&p[8]);
    out_header->type     = p[10];
    out_header->flags    = p[11];
    return true;
}

void packet_read_begin(PacketBuffer *buf, const void *data, u32 size)
{
    if (!buf) return;
    memset(buf, 0, sizeof(*buf));
    if (!data || size == 0) {
        buf->write_pos = 0;
        buf->read_pos  = PACKET_HEADER_SIZE;
        return;
    }
    u32 copy = size > PACKET_MAX_SIZE ? PACKET_MAX_SIZE : size;
    memcpy(buf->data, data, copy);
    buf->write_pos = copy;
    /* Skip header — readers start at payload. */
    buf->read_pos  = PACKET_HEADER_SIZE;
}

u8 packet_read_u8(PacketBuffer *buf)
{
    if (!packet_can_read(buf, 1)) return 0;
    u8 v = buf->data[buf->read_pos];
    buf->read_pos += 1;
    return v;
}

u16 packet_read_u16(PacketBuffer *buf)
{
    if (!packet_can_read(buf, 2)) return 0;
    u16 v = le_read_u16(&buf->data[buf->read_pos]);
    buf->read_pos += 2;
    return v;
}

u32 packet_read_u32(PacketBuffer *buf)
{
    if (!packet_can_read(buf, 4)) return 0;
    u32 v = le_read_u32(&buf->data[buf->read_pos]);
    buf->read_pos += 4;
    return v;
}

f32 packet_read_f32(PacketBuffer *buf)
{
    f32 out = 0.0f;
    u32 bits;
    if (!packet_can_read(buf, 4)) return 0.0f;
    bits = le_read_u32(&buf->data[buf->read_pos]);
    buf->read_pos += 4;
    memcpy(&out, &bits, sizeof(out));
    return out;
}

void packet_read_bytes(PacketBuffer *buf, void *out, u32 size)
{
    if (!buf || !out || size == 0) return;
    if (!packet_can_read(buf, size)) {
        memset(out, 0, size);
        return;
    }
    memcpy(out, &buf->data[buf->read_pos], size);
    buf->read_pos += size;
}
