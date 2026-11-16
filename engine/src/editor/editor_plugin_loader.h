#pragma once
/* Loads the plugins of an editor plugin manifest through break_plugin and
 * keeps them until destroy. This is the one editor file that calls
 * break_plugin_*; it lives in the opt-in break_editor_plugin_loader library
 * (CMake BREAK_EDITOR_PLUGINS, default OFF), so the default editor still does
 * not link break_system. Threading: editor shell thread. */

#include <editor/editor_plugin_host.h>
#include <editor/editor_plugin_manifest.h>

typedef struct BreakEditorPluginLoader BreakEditorPluginLoader;

/* Borrows host, which must outlive the loader. NULL host or allocation
 * failure gives NULL. */
BreakEditorPluginLoader *break_editor_plugin_loader_create(BreakEditorPluginHost *host);

/* Loads every manifest entry in order (break_editor_plugin_manifest_load_all
 * with break_plugin_load as the callback). Entries that fail, and entries past
 * BREAK_EDITOR_PLUGIN_MANIFEST_MAX plugins held by this loader (the manager's
 * capacity), count as failed. False only for NULL arguments. */
bool break_editor_plugin_loader_load_manifest(BreakEditorPluginLoader *loader,
                                              const BreakEditorPluginManifest *manifest,
                                              BreakEditorPluginManifestReport *report);

/* Number of plugins currently loaded. 0 for NULL. */
u32 break_editor_plugin_loader_count(const BreakEditorPluginLoader *loader);

/* Removes every plugin's commands, unloads the plugins newest first and
 * frees the loader. NULL is a no-op. */
void break_editor_plugin_loader_destroy(BreakEditorPluginLoader *loader);
