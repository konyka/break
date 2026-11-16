#include <editor/editor_plugin_loader.h>

#include <system/break_plugin.h>

#include <stdlib.h>

struct BreakEditorPluginLoader {
    BreakEditorPluginHost *host;
    BreakPluginManager *manager;
    u32 count;
    u32 owners[BREAK_EDITOR_PLUGIN_MANIFEST_MAX];
};

BreakEditorPluginLoader *break_editor_plugin_loader_create(BreakEditorPluginHost *host)
{
    if (!host) return NULL;
    BreakEditorPluginLoader *loader = (BreakEditorPluginLoader *)calloc(1u, sizeof(*loader));
    if (!loader) return NULL;
    loader->host = host;
    /* Capacity MANIFEST_MAX: the manager itself refuses a load past the
     * owners[] array, so the loader needs no bound check of its own. */
    loader->manager = break_plugin_create(BREAK_EDITOR_PLUGIN_MANIFEST_MAX,
                                          (void *)break_editor_plugin_host_api(host));
    if (!loader->manager) {
        free(loader);
        return NULL;
    }
    return loader;
}

static bool loader_load_entry(void *user, const BreakEditorPluginManifestEntry *entry)
{
    BreakEditorPluginLoader *loader = (BreakEditorPluginLoader *)user;
    BreakPluginHandle handle;
    return break_plugin_load(loader->manager, entry->path, entry->build_id, entry->sha256,
                             &handle) == BREAK_PLUGIN_OK;
}

bool break_editor_plugin_loader_load_manifest(BreakEditorPluginLoader *loader,
                                              const BreakEditorPluginManifest *manifest,
                                              BreakEditorPluginManifestReport *report)
{
    if (!loader) return false;
    if (!break_editor_plugin_manifest_load_all(manifest, loader->host, loader_load_entry, loader,
                                               report)) {
        return false;
    }
    for (u32 i = 0u; i < BREAK_EDITOR_PLUGIN_MANIFEST_MAX; ++i) {
        if (report->owners[i] == 0u) continue;
        loader->owners[loader->count++] = report->owners[i];
    }
    return true;
}

u32 break_editor_plugin_loader_count(const BreakEditorPluginLoader *loader)
{
    return loader ? loader->count : 0u;
}

void break_editor_plugin_loader_destroy(BreakEditorPluginLoader *loader)
{
    if (!loader) return;
    for (u32 i = 0u; i < loader->count; ++i) {
        (void)break_editor_plugin_host_release(loader->host, loader->owners[i]);
    }
    /* The loader never acquires a handle, so destroy cannot be refused; it
     * unloads the plugins newest first. */
    (void)break_plugin_destroy(loader->manager);
    free(loader);
}
