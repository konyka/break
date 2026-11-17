/* audio_fft: validation, impulses and pure tones, a direct DFT at every
 * size, the round trip, Parseval, linearity and the Hann window. */
#include "test_framework.h"

#include <audio/audio_fft.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

static const double kPi = 3.14159265358979323846;
static u32 g_seed = 0xC0FFEEu;

static double rnd(void) {
    g_seed = g_seed * 1664525u + 1013904223u;
    return (double)(g_seed >> 8) / 8388608.0 - 1.0;
}

#define ASSERT_FINITE_NEAR(a, b, eps) do { \
    const double actual_ = (double)(a); \
    const double expected_ = (double)(b); \
    ASSERT_TRUE(isfinite(actual_)); \
    ASSERT_TRUE(isfinite(expected_)); \
    ASSERT_TRUE(fabs(actual_ - expected_) <= (double)(eps)); \
} while (0)

static f64 g_x[AUDIO_FFT_MAX_SIZE], g_y[AUDIO_FFT_MAX_SIZE];
static f64 g_re[AUDIO_FFT_MAX_SIZE / 2u + 1u], g_im[AUDIO_FFT_MAX_SIZE / 2u + 1u];

TEST(create_accepts_only_powers_of_two_in_range)
{
    AudioFft *sentinel = NULL;
    ASSERT_EQ(audio_fft_create(8u, &sentinel), AUDIO_OK);
    AudioFft *fft = sentinel;
    const u32 bad[] = {0u, 1u, 2u, 3u, 6u, 12u, 1000u, AUDIO_FFT_MAX_SIZE + 1u,
                       AUDIO_FFT_MAX_SIZE * 2u, 0x80000000u};
    for (u32 i = 0; i < sizeof(bad) / sizeof(bad[0]); ++i) {
        ASSERT_EQ(audio_fft_create(bad[i], &fft), AUDIO_INVALID);
        ASSERT_TRUE(fft == sentinel);
    }
    ASSERT_EQ(audio_fft_create(8u, NULL), AUDIO_INVALID);
    for (u32 size = AUDIO_FFT_MIN_SIZE; size <= AUDIO_FFT_MAX_SIZE; size *= 2u) {
        ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
        ASSERT_EQ(audio_fft_size(fft), size);
        audio_fft_destroy(fft);
    }
    ASSERT_EQ(audio_fft_size(NULL), 0u);
    audio_fft_destroy(NULL);
    /* NULL arguments are no-ops */
    ASSERT_EQ(audio_fft_create(8u, &fft), AUDIO_OK);
    g_re[0] = 7.0;
    audio_fft_forward(NULL, g_x, g_re, g_im);
    audio_fft_forward(fft, NULL, g_re, g_im);
    audio_fft_forward(fft, g_x, NULL, g_im);
    audio_fft_forward(fft, g_x, g_re, NULL);
    audio_fft_inverse(NULL, g_re, g_im, g_x);
    audio_fft_inverse(fft, NULL, g_im, g_x);
    audio_fft_inverse(fft, g_re, NULL, g_x);
    audio_fft_inverse(fft, g_re, g_im, NULL);
    ASSERT_FINITE_NEAR(g_re[0], 7.0, 0.0);
    audio_fft_destroy(fft);
    audio_fft_destroy(sentinel);
}

TEST(an_impulse_and_a_tone_have_the_known_spectrum)
{
    const u32 size = 64u;
    AudioFft *fft = NULL;
    ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
    /* a delayed impulse: magnitude 1 everywhere, phase -2 pi k d / n */
    memset(g_x, 0, sizeof(f64) * size);
    g_x[3] = 1.0;
    audio_fft_forward(fft, g_x, g_re, g_im);
    for (u32 k = 0; k <= size / 2u; ++k) {
        ASSERT_FINITE_NEAR(g_re[k], cos(-2.0 * kPi * k * 3.0 / size), 1e-12);
        ASSERT_FINITE_NEAR(g_im[k], sin(-2.0 * kPi * k * 3.0 / size), 1e-12);
    }
    /* cos at bin 5 with amplitude 2: re[5] = size, everything else 0 */
    for (u32 t = 0; t < size; ++t) g_x[t] = 2.0 * cos(2.0 * kPi * 5.0 * t / size);
    audio_fft_forward(fft, g_x, g_re, g_im);
    for (u32 k = 0; k <= size / 2u; ++k) {
        ASSERT_FINITE_NEAR(g_re[k], k == 5u ? (double)size : 0.0, 1e-10);
        ASSERT_FINITE_NEAR(g_im[k], 0.0, 1e-10);
    }
    /* sin at the Nyquist bin is zero; the constant lands in bin 0 */
    for (u32 t = 0; t < size; ++t) g_x[t] = 1.5 + ((t & 1u) ? -0.5 : 0.5);
    audio_fft_forward(fft, g_x, g_re, g_im);
    ASSERT_FINITE_NEAR(g_re[0], 1.5 * size, 1e-10);
    ASSERT_FINITE_NEAR(g_re[size / 2u], 0.5 * size, 1e-10);
    ASSERT_FINITE_NEAR(g_im[0], 0.0, 0.0);
    ASSERT_FINITE_NEAR(g_im[size / 2u], 0.0, 0.0);
    audio_fft_destroy(fft);
}

TEST(every_size_matches_a_direct_dft)
{
    for (u32 size = AUDIO_FFT_MIN_SIZE; size <= 1024u; size *= 2u) {
        AudioFft *fft = NULL;
        ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
        for (u32 t = 0; t < size; ++t) g_x[t] = rnd();
        memcpy(g_y, g_x, sizeof(f64) * size);
        audio_fft_forward(fft, g_x, g_re, g_im);
        ASSERT_EQ(memcmp(g_x, g_y, sizeof(f64) * size), 0);
        for (u32 k = 0; k <= size / 2u; ++k) {
            double re = 0.0, im = 0.0;
            for (u32 t = 0; t < size; ++t) {
                double a = -2.0 * kPi * (double)((u64)k * t % size) / size;
                re += g_x[t] * cos(a);
                im += g_x[t] * sin(a);
            }
            ASSERT_FINITE_NEAR(g_re[k], re, 1e-9 * size);
            ASSERT_FINITE_NEAR(g_im[k], im, 1e-9 * size);
        }
        audio_fft_destroy(fft);
    }
}

TEST(large_sizes_match_a_direct_dft_at_selected_bins)
{
    for (u32 size = 2048u; size <= AUDIO_FFT_MAX_SIZE; size *= 2u) {
        AudioFft *fft = NULL;
        ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
        for (u32 t = 0; t < size; ++t) g_x[t] = rnd();
        memcpy(g_y, g_x, sizeof(f64) * size);
        audio_fft_forward(fft, g_x, g_re, g_im);
        ASSERT_EQ(memcmp(g_x, g_y, sizeof(f64) * size), 0);
        const u32 bins[] = {0u, 1u, size / 4u - 1u, size / 4u,
                            size / 4u + 1u, size / 2u - 1u, size / 2u};
        for (u32 b = 0; b < sizeof(bins) / sizeof(bins[0]); ++b) {
            const u32 k = bins[b];
            double re = 0.0, im = 0.0;
            for (u32 t = 0; t < size; ++t) {
                const double a = -2.0 * kPi * (double)((u64)k * t % size) / size;
                re += g_x[t] * cos(a);
                im += g_x[t] * sin(a);
            }
            ASSERT_FINITE_NEAR(g_re[k], re, 1e-9 * size);
            ASSERT_FINITE_NEAR(g_im[k], im, 1e-9 * size);
        }
        audio_fft_destroy(fft);
    }
}

TEST(independently_constructed_spectra_have_the_known_inverse)
{
    AudioFft *fft = NULL;
    ASSERT_EQ(audio_fft_create(4u, &fft), AUDIO_OK);
    g_re[0] = 1.5; g_re[1] = -0.5; g_re[2] = 0.5;
    g_im[0] = 123.0; g_im[1] = 1.5; g_im[2] = -45.0;
    audio_fft_inverse(fft, g_re, g_im, g_y);
    const double expected4[] = {0.25, -0.5, 0.75, 1.0};
    for (u32 t = 0; t < 4u; ++t) ASSERT_FINITE_NEAR(g_y[t], expected4[t], 1e-12);
    audio_fft_destroy(fft);

    const u32 size = 16u;
    const u32 half = size / 2u;
    ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
    g_re[0] = 0.75; g_im[0] = 123.0;
    g_re[half] = -0.25; g_im[half] = -45.0;
    for (u32 k = 1u; k < half; ++k) {
        g_re[k] = 0.03 * (double)(k + 1u);
        g_im[k] = -0.02 * (double)(2u * k - 1u);
    }
    for (u32 t = 0; t < size; ++t) {
        double sum = g_re[0] + ((t & 1u) ? -g_re[half] : g_re[half]);
        for (u32 k = 1u; k < half; ++k) {
            const double a = 2.0 * kPi * (double)((u64)k * t % size) / size;
            sum += 2.0 * (g_re[k] * cos(a) - g_im[k] * sin(a));
        }
        g_x[t] = sum / size;
    }
    audio_fft_inverse(fft, g_re, g_im, g_y);
    for (u32 t = 0; t < size; ++t) ASSERT_FINITE_NEAR(g_y[t], g_x[t], 1e-12);
    audio_fft_destroy(fft);
}

TEST(the_inverse_restores_the_signal_and_energy_is_kept)
{
    const u32 sizes[4] = {4u, 256u, 4096u, AUDIO_FFT_MAX_SIZE};
    for (u32 s = 0; s < 4u; ++s) {
        const u32 size = sizes[s];
        AudioFft *fft = NULL;
        ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
        double energy = 0.0;
        for (u32 t = 0; t < size; ++t) {
            g_x[t] = rnd();
            energy += g_x[t] * g_x[t];
        }
        audio_fft_forward(fft, g_x, g_re, g_im);
        /* Parseval over the full spectrum: inner bins count twice */
        double spectral = 0.0;
        for (u32 k = 0; k <= size / 2u; ++k) {
            double m = g_re[k] * g_re[k] + g_im[k] * g_im[k];
            spectral += (k == 0u || k == size / 2u) ? m : 2.0 * m;
        }
        ASSERT_FINITE_NEAR(spectral / size, energy, 1e-9 * energy);
        /* im of the DC and Nyquist bins is ignored by the inverse */
        g_im[0] = 123.0;
        g_im[size / 2u] = -45.0;
        audio_fft_inverse(fft, g_re, g_im, g_y);
        double worst = 0.0;
        for (u32 t = 0; t < size; ++t) {
            double d = fabs(g_y[t] - g_x[t]);
            if (d > worst) worst = d;
        }
        ASSERT_TRUE(worst < 1e-12);
        audio_fft_destroy(fft);
    }
}

TEST(the_transform_is_linear_and_a_shift_is_a_phase)
{
    const u32 size = 128u;
    static f64 a[128], b[128], ra[65], ia[65], rb[65], ib[65];
    AudioFft *fft = NULL;
    ASSERT_EQ(audio_fft_create(size, &fft), AUDIO_OK);
    for (u32 t = 0; t < size; ++t) {
        a[t] = rnd();
        b[t] = rnd();
        g_x[t] = 2.0 * a[t] - 3.0 * b[t];
    }
    audio_fft_forward(fft, a, ra, ia);
    audio_fft_forward(fft, b, rb, ib);
    audio_fft_forward(fft, g_x, g_re, g_im);
    for (u32 k = 0; k <= size / 2u; ++k) {
        ASSERT_FINITE_NEAR(g_re[k], 2.0 * ra[k] - 3.0 * rb[k], 1e-11);
        ASSERT_FINITE_NEAR(g_im[k], 2.0 * ia[k] - 3.0 * ib[k], 1e-11);
    }
    /* a circular shift by 1 multiplies bin k by exp(-2 pi i k / n) */
    for (u32 t = 0; t < size; ++t) g_x[t] = a[(t + size - 1u) % size];
    audio_fft_forward(fft, g_x, g_re, g_im);
    for (u32 k = 0; k <= size / 2u; ++k) {
        double c = cos(-2.0 * kPi * k / size), s = sin(-2.0 * kPi * k / size);
        ASSERT_FINITE_NEAR(g_re[k], ra[k] * c - ia[k] * s, 1e-11);
        ASSERT_FINITE_NEAR(g_im[k], ra[k] * s + ia[k] * c, 1e-11);
    }
    audio_fft_destroy(fft);
}

TEST(the_hann_window_overlaps_to_one)
{
    f64 w[16];
    ASSERT_TRUE(audio_fft_hann(w, 16u));
    ASSERT_FINITE_NEAR(w[0], 0.0, 0.0);
    ASSERT_FINITE_NEAR(w[8], 1.0, 1e-15);
    ASSERT_FINITE_NEAR(w[4], 0.5, 1e-15);
    for (u32 t = 0; t < 8u; ++t) {
        ASSERT_FINITE_NEAR(w[t] + w[t + 8u], 1.0, 1e-15);
        ASSERT_FINITE_NEAR(w[t + 1u], w[15u - t], 1e-15);
    }
    ASSERT_TRUE(!audio_fft_hann(NULL, 16u));
    ASSERT_TRUE(!audio_fft_hann(w, 0u));
    w[0] = 9.0;
    ASSERT_TRUE(!audio_fft_hann(w, 7u));
    ASSERT_FINITE_NEAR(w[0], 9.0, 0.0);
    ASSERT_TRUE(audio_fft_hann(w, 2u));
    ASSERT_FINITE_NEAR(w[0], 0.0, 0.0);
    ASSERT_FINITE_NEAR(w[1], 1.0, 1e-15);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_accepts_only_powers_of_two_in_range);
    RUN_TEST(an_impulse_and_a_tone_have_the_known_spectrum);
    RUN_TEST(every_size_matches_a_direct_dft);
    RUN_TEST(large_sizes_match_a_direct_dft_at_selected_bins);
    RUN_TEST(independently_constructed_spectra_have_the_known_inverse);
    RUN_TEST(the_inverse_restores_the_signal_and_energy_is_kept);
    RUN_TEST(the_transform_is_linear_and_a_shift_is_a_phase);
    RUN_TEST(the_hann_window_overlaps_to_one);
TEST_MAIN_END()
