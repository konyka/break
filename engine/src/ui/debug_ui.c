#include <ui/debug_ui.h>
#include <rhi/rhi.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void debug_ui_init(DebugUI *ui) {
    memset(ui, 0, sizeof(DebugUI));
    ui->visible = true;
}

void debug_ui_init_renderer(DebugUI *ui, RHIDevice *dev) {
    ui->device = dev;
    ui->initialized = font_renderer_init(&ui->font, dev, "assets/LiberationSans-Regular.ttf", 18.0f);
    if (!ui->initialized) {
        LOG_WARN("DebugUI: font renderer init failed, falling back to LOG_INFO");
    }
}

void debug_ui_begin(DebugUI *ui) {
    ui->line_count = 0;
}

void debug_ui_text(DebugUI *ui, const char *fmt, ...) {
    if (ui->line_count >= 32) return;
    va_list args;
    va_start(args, fmt);
    vsnprintf(ui->lines[ui->line_count], sizeof(ui->lines[0]), fmt, args);
    va_end(args);
    ui->line_count++;
}

void debug_ui_end(DebugUI *ui) {
    (void)ui;
}

void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    if (!ui->visible || ui->line_count == 0) return;

    if (!ui->initialized) {
        for (u32 i = 0; i < ui->line_count; i++) {
            LOG_INFO("[UI] %s", ui->lines[i]);
        }
        return;
    }

    font_renderer_begin(&ui->font);
    f32 y = 4.0f;
    for (u32 i = 0; i < ui->line_count; i++) {
        font_renderer_draw(&ui->font, ui->lines[i], 4.0f, y,
            (f32)screen_w, (f32)screen_h, 1.0f, 1.0f, 1.0f, 1.0f);
        y += ui->font.ascent - ui->font.descent + ui->font.line_gap + 2.0f;
    }
    font_renderer_end(&ui->font, cmd, (f32)screen_w, (f32)screen_h);
}

void debug_ui_toggle(DebugUI *ui) {
    ui->visible = !ui->visible;
}

void debug_ui_shutdown(DebugUI *ui) {
    if (ui->initialized) {
        font_renderer_shutdown(&ui->font);
        ui->initialized = false;
    }
}
