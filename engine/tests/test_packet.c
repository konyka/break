/* ==========================================================================
 *  test_packet.c — Unit tests for the network packet serialization module.
 * ========================================================================== */

#include "test_framework.h"
#include <network/packet.h>
#include <math.h>
#include <float.h>
#include <string.h>

/* ----------------------------------------------------------------------- */

TEST(begin_finish_header)
{
    PacketBuffer buf;
    packet_begin(&buf, 5, PACKET_RELIABLE);
    packet_write_u32(&buf, 0xDEADBEEF);
    u32 total = packet_finish(&buf, 42, 7);

    /* Total = header(12) + payload(4) */
    ASSERT_EQ(total, 16u);

    /* Parse header from raw bytes */
    PacketHeader hdr;
    ASSERT_TRUE(packet_parse_header(buf.data, total, &hdr));
    ASSERT_EQ(hdr.sequence, 42u);
    ASSERT_EQ(hdr.ack, 7u);
    ASSERT_EQ(hdr.size, 4u);
    ASSERT_EQ(hdr.type, 5u);
    ASSERT_EQ(hdr.flags, (u8)PACKET_RELIABLE);
}

TEST(roundtrip_u8)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 1, 0);
    packet_write_u8(&wb, 0xAB);
    packet_write_u8(&wb, 0x00);
    packet_write_u8(&wb, 0xFF);
    u32 total = packet_finish(&wb, 1, 0);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u8(&rb), 0xAB);
    ASSERT_EQ(packet_read_u8(&rb), 0x00);
    ASSERT_EQ(packet_read_u8(&rb), 0xFF);
}

TEST(roundtrip_u16)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 2, 0);
    packet_write_u16(&wb, 0);
    packet_write_u16(&wb, 0x1234);
    packet_write_u16(&wb, 0xFFFF);
    u32 total = packet_finish(&wb, 10, 5);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u16(&rb), 0u);
    ASSERT_EQ(packet_read_u16(&rb), 0x1234);
    ASSERT_EQ(packet_read_u16(&rb), 0xFFFF);
}

TEST(roundtrip_u32)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 3, 0);
    packet_write_u32(&wb, 0u);
    packet_write_u32(&wb, 0xCAFEBABE);
    packet_write_u32(&wb, 0xFFFFFFFF);
    u32 total = packet_finish(&wb, 100, 99);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u32(&rb), 0u);
    ASSERT_EQ(packet_read_u32(&rb), 0xCAFEBABEu);
    ASSERT_EQ(packet_read_u32(&rb), 0xFFFFFFFFu);
}

TEST(roundtrip_f32)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 4, 0);
    packet_write_f32(&wb, 0.0f);
    packet_write_f32(&wb, 3.14159f);
    packet_write_f32(&wb, -1.0e10f);
    u32 total = packet_finish(&wb, 1, 0);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), 0.0f, 1e-12);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), 3.14159f, 1e-5);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), -1.0e10f, 1e3);
}

TEST(roundtrip_bytes)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 5, 0);
    u8 src[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x42};
    packet_write_bytes(&wb, src, sizeof(src));
    u32 total = packet_finish(&wb, 1, 0);

    u8 dst[6] = {0};
    packet_read_begin(&rb, wb.data, total);
    packet_read_bytes(&rb, dst, sizeof(dst));
    ASSERT_TRUE(memcmp(src, dst, sizeof(src)) == 0);
}

TEST(mixed_types)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 10, PACKET_ORDERED | PACKET_RELIABLE);
    packet_write_u8(&wb, 42);
    packet_write_f32(&wb, 2.71828f);
    packet_write_u16(&wb, 1000);
    packet_write_u32(&wb, 999999);
    u32 total = packet_finish(&wb, 7, 3);

    PacketHeader hdr;
    ASSERT_TRUE(packet_parse_header(wb.data, total, &hdr));
    ASSERT_EQ(hdr.type, 10u);
    ASSERT_EQ(hdr.flags, (u8)(PACKET_ORDERED | PACKET_RELIABLE));

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u8(&rb), 42);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), 2.71828f, 1e-4);
    ASSERT_EQ(packet_read_u16(&rb), 1000);
    ASSERT_EQ(packet_read_u32(&rb), 999999u);
}

TEST(overflow_protection)
{
    PacketBuffer buf;
    packet_begin(&buf, 0, 0);

    /* Fill up to near the limit */
    for (u32 i = 0; i < PACKET_MAX_SIZE / 4; i++) {
        packet_write_u32(&buf, i);
    }

    /* write_pos should be at or near PACKET_MAX_SIZE + header offset */
    u32 pos_before = buf.write_pos;
    packet_write_u32(&buf, 0xDEAD);
    /* Should have been rejected (no space), write_pos unchanged */
    ASSERT_EQ(buf.write_pos, pos_before);
}

TEST(write_bytes_size_overflow_rejected)
{
    /* R298: a size that makes `write_pos + size` wrap u32 to a small value must
     * be rejected. The old additive check `write_pos + size <= PACKET_MAX_SIZE`
     * accepted it and then memcpy'd ~4GB past the 1400-byte buffer (OOB read of
     * src + OOB write of data[]). The fix compares against remaining capacity,
     * so the write is refused and the cursor stays put. This test crashes
     * against the pre-fix code and passes with the fix. */
    PacketBuffer wb;
    packet_begin(&wb, 7, 0);
    u32 before = wb.write_pos;                 /* PACKET_HEADER_SIZE */
    u32 wrap_size = (u32)(0u - wb.write_pos);  /* write_pos + wrap_size == 0 (mod 2^32) */
    static const char one_byte[1] = {0};
    packet_write_bytes(&wb, one_byte, wrap_size);
    ASSERT_EQ(wb.write_pos, before);           /* rejected: no advance, no OOB memcpy */

    /* A read whose size wraps must likewise fail the bound rather than OOB-read
     * buf->data. Exercised safely via the fixed-size read path exhausting the
     * payload (packet_read_bytes with a wrapped size is unsafe to call because
     * its failure path memsets `size` bytes of the caller's buffer). */
    PacketBuffer rb;
    packet_write_u32(&wb, 0xCAFEBABEu);
    u32 total = packet_finish(&wb, 1, 0);
    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u32(&rb), 0xCAFEBABEu);
    u32 rp = rb.read_pos;
    ASSERT_EQ(packet_read_u32(&rb), 0u);       /* no bytes left → rejected */
    ASSERT_EQ(rb.read_pos, rp);                /* cursor unchanged on rejection */
}

TEST(parse_header_too_small)
{
    u8 tiny[5] = {0};
    PacketHeader hdr;
    ASSERT_FALSE(packet_parse_header(tiny, sizeof(tiny), &hdr));
}

TEST(parse_header_null)
{
    PacketHeader hdr;
    ASSERT_FALSE(packet_parse_header(NULL, 12, &hdr));
}

TEST(empty_payload)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 0, 0);
    u32 total = packet_finish(&wb, 1, 0);
    ASSERT_EQ(total, (u32)PACKET_HEADER_SIZE);

    PacketHeader hdr;
    ASSERT_TRUE(packet_parse_header(wb.data, total, &hdr));
    ASSERT_EQ(hdr.size, 0u);

    /* Reading from empty payload should return zero values */
    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u32(&rb), 0u);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), 0.0f, 1e-12);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(read_beyond_buffer)
{
    PacketBuffer buf;
    packet_begin(&buf, 1, 0);
    packet_write_u8(&buf, 0x42);
    u32 total = packet_finish(&buf, 1, 0);

    PacketBuffer rb;
    packet_read_begin(&rb, buf.data, total);

    /* Read one byte, then try to read more - should return 0 */
    ASSERT_EQ(packet_read_u8(&rb), 0x42);
    ASSERT_EQ(packet_read_u8(&rb), 0);
    ASSERT_EQ(packet_read_u32(&rb), 0u);
}

TEST(write_null_buffer)
{
    /* These should not crash */
    packet_write_u8(NULL, 0);
    packet_write_u16(NULL, 0);
    packet_write_u32(NULL, 0);
    packet_write_f32(NULL, 0.0f);
    packet_write_bytes(NULL, "test", 4);
    ASSERT_EQ(packet_finish(NULL, 0, 0), 0u);
}

TEST(read_null_buffer)
{
    /* These should not crash and return 0 */
    ASSERT_EQ(packet_read_u8(NULL), 0);
    ASSERT_EQ(packet_read_u16(NULL), 0);
    ASSERT_EQ(packet_read_u32(NULL), 0u);
    ASSERT_FLOAT_EQ(packet_read_f32(NULL), 0.0f, 1e-12);

    /* Read bytes with NULL buffer should not crash */
    u8 dst[4];
    packet_read_bytes(NULL, dst, sizeof(dst));
}

TEST(read_truncated_packet)
{
    PacketBuffer wb;
    packet_begin(&wb, 1, 0);
    packet_write_u32(&wb, 0xDEADBEEF);
    packet_write_u32(&wb, 0xCAFEBABE);
    (void)packet_finish(&wb, 1, 0);

    /* Read with truncated data - only enough for header + 1 u32 */
    PacketBuffer rb;
    packet_read_begin(&rb, wb.data, PACKET_HEADER_SIZE + 4);
    ASSERT_EQ(packet_read_u32(&rb), 0xDEADBEEF);
    /* Second u32 should be 0 because we only have 4 bytes of payload */
    ASSERT_EQ(packet_read_u32(&rb), 0u);
}

TEST(write_bytes_null_data)
{
    /* Write bytes with NULL source data - should not crash */
    PacketBuffer buf;
    packet_begin(&buf, 1, 0);
    packet_write_bytes(&buf, NULL, 4);
    /* Just verify no crash */
    ASSERT_TRUE(true);
}

TEST(roundtrip_max_values)
{
    PacketBuffer wb, rb;
    packet_begin(&wb, 1, 0);
    packet_write_u8(&wb, UINT8_MAX);
    packet_write_u16(&wb, UINT16_MAX);
    packet_write_u32(&wb, UINT32_MAX);
    packet_write_f32(&wb, FLT_MAX);
    u32 total = packet_finish(&wb, 1, 0);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u8(&rb), UINT8_MAX);
    ASSERT_EQ(packet_read_u16(&rb), UINT16_MAX);
    ASSERT_EQ(packet_read_u32(&rb), UINT32_MAX);
    ASSERT_FLOAT_EQ(packet_read_f32(&rb), FLT_MAX, 1e30);
}

TEST(packet_all_flags)
{
    PacketBuffer wb, rb;
    /* Test with all flag bits set */
    u8 all_flags = 0xFF;
    packet_begin(&wb, 1, all_flags);
    packet_write_u32(&wb, 0x12345678);
    u32 total = packet_finish(&wb, 1, 0);

    PacketHeader hdr;
    ASSERT_TRUE(packet_parse_header(wb.data, total, &hdr));
    ASSERT_EQ(hdr.flags, all_flags);

    packet_read_begin(&rb, wb.data, total);
    ASSERT_EQ(packet_read_u32(&rb), 0x12345678u);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(begin_finish_header);
    RUN_TEST(roundtrip_u8);
    RUN_TEST(roundtrip_u16);
    RUN_TEST(roundtrip_u32);
    RUN_TEST(roundtrip_f32);
    RUN_TEST(roundtrip_bytes);
    RUN_TEST(mixed_types);
    RUN_TEST(overflow_protection);
    RUN_TEST(write_bytes_size_overflow_rejected);
    RUN_TEST(parse_header_too_small);
    RUN_TEST(parse_header_null);
    RUN_TEST(empty_payload);
    /* Edge cases */
    RUN_TEST(read_beyond_buffer);
    RUN_TEST(write_null_buffer);
    RUN_TEST(read_null_buffer);
    RUN_TEST(read_truncated_packet);
    RUN_TEST(write_bytes_null_data);
    RUN_TEST(roundtrip_max_values);
    RUN_TEST(packet_all_flags);
TEST_MAIN_END()
