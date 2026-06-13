#ifndef PACKET_H
#define PACKET_H

#include "../core/types.h"

#define PACKET_MAX_SIZE     1400  /* MTU-safe payload */
#define PACKET_HEADER_SIZE  12

typedef enum {
    PACKET_UNRELIABLE = 0,
    PACKET_RELIABLE   = 1,
    PACKET_ORDERED    = 2
} PacketFlags;

typedef struct {
    u32 sequence;   /* sequence number */
    u32 ack;        /* acknowledged sequence */
    u16 size;       /* payload size (excluding header) */
    u8  type;       /* user-defined packet type */
    u8  flags;      /* PacketFlags bitmask */
} PacketHeader;

typedef struct {
    u8  data[PACKET_MAX_SIZE];
    u32 write_pos;
    u32 read_pos;
} PacketBuffer;

/* ---- Serialization (write) ---- */
void packet_begin(PacketBuffer *buf, u8 type, u8 flags);
void packet_write_u8 (PacketBuffer *buf, u8  val);
void packet_write_u16(PacketBuffer *buf, u16 val);
void packet_write_u32(PacketBuffer *buf, u32 val);
void packet_write_f32(PacketBuffer *buf, f32 val);
void packet_write_bytes(PacketBuffer *buf, const void *data, u32 size);
/* Patches header (sequence/ack/size) and returns total byte count. */
u32  packet_finish(PacketBuffer *buf, u32 sequence, u32 ack);

/* ---- Deserialization (read) ---- */
bool packet_parse_header(const void *data, u32 size, PacketHeader *out_header);
void packet_read_begin(PacketBuffer *buf, const void *data, u32 size);
u8   packet_read_u8 (PacketBuffer *buf);
u16  packet_read_u16(PacketBuffer *buf);
u32  packet_read_u32(PacketBuffer *buf);
f32  packet_read_f32(PacketBuffer *buf);
void packet_read_bytes(PacketBuffer *buf, void *out, u32 size);

#endif /* PACKET_H */
