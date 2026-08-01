/* verify_pak.c — Verify packer output is VFS-compatible
 *
 * Mounts a .pak file via VFS, reads each entry, and compares
 * against the original file on disk. */
#include <asset/vfs.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERIFY_CHUNK_BYTES (64u * 1024u)

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#else
    #include <dirent.h>
    #include <sys/stat.h>
#endif

static int verify_file(VFS *vfs, const char *pak_name,
                       const char *disk_path) {
    VFSFile *f = vfs_open(vfs, pak_name);
    if (!f) {
        fprintf(stderr, "FAIL: cannot open '%s' from pak\n", pak_name);
        return 0;
    }

    usize pak_size = vfs_size(f);

    /* Read from disk for comparison */
    FILE *fp = fopen(disk_path, "rb");
    if (!fp) {
        fprintf(stderr, "FAIL: cannot open '%s' on disk\n", disk_path);
        vfs_close(f);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long disk_size = ftell(fp);
    if (disk_size < 0) {
        fprintf(stderr, "FAIL: ftell error for '%s'\n", disk_path);
        fclose(fp);
        vfs_close(f);
        return 0;
    }
    fseek(fp, 0, SEEK_SET);

    if ((usize)disk_size != pak_size) {
        fprintf(stderr, "FAIL: size mismatch for '%s' (pak=%zu, disk=%ld)\n",
                pak_name, pak_size, disk_size);
        fclose(fp);
        vfs_close(f);
        return 0;
    }

    u8 *disk_buf = malloc(VERIFY_CHUNK_BYTES);
    u8 *pak_buf = malloc(VERIFY_CHUNK_BYTES);
    if (!disk_buf || !pak_buf) {
        fprintf(stderr, "FAIL: chunk buffer malloc failed for '%s'\n", pak_name);
        free(disk_buf);
        free(pak_buf);
        fclose(fp);
        vfs_close(f);
        return 0;
    }

    int match = 1;
    usize remaining = pak_size;
    while (remaining > 0) {
        usize chunk = remaining < VERIFY_CHUNK_BYTES ? remaining : VERIFY_CHUNK_BYTES;
        if (fread(disk_buf, 1, chunk, fp) != chunk) {
            fprintf(stderr, "FAIL: short read on disk for '%s'\n", disk_path);
            match = 0;
            break;
        }
        usize nread = vfs_read(f, pak_buf, chunk);
        if (nread != chunk) {
            fprintf(stderr, "FAIL: short read for '%s' (%zu/%zu)\n",
                    pak_name, nread, chunk);
            match = 0;
            break;
        }
        if (memcmp(disk_buf, pak_buf, chunk) != 0) {
            fprintf(stderr, "FAIL: content mismatch for '%s'\n", pak_name);
            match = 0;
            break;
        }
        remaining -= chunk;
    }

    if (match) printf("OK: '%s' (%zu bytes) matches\n", pak_name, pak_size);

    free(disk_buf);
    free(pak_buf);
    fclose(fp);
    vfs_close(f);
    return match;
}

/* R428: mirror packer.c's recursive scan_dir. The old code only scanned
 * top-level files of src_dir, but the packer recurses and stores names like
 * "sub/file" — nested entries were never verified yet the tool printed
 * success. Returns 1 when every file under base_dir/rel_prefix matches. */
static int verify_dir(VFS *vfs, const char *base_dir, const char *rel_prefix) {
    int all_ok = 1;
#ifdef _WIN32
    char pattern[1024];
    if (rel_prefix[0])
        snprintf(pattern, sizeof(pattern), "%s/%s/*", base_dir, rel_prefix);
    else
        snprintf(pattern, sizeof(pattern), "%s/*", base_dir);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(pattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "FAIL: cannot scan '%s/%s'\n", base_dir, rel_prefix);
        return 0;
    }
    do {
        if (fd.cFileName[0] == '.') continue;

        char rel[1024];
        if (rel_prefix[0])
            snprintf(rel, sizeof(rel), "%s/%s", rel_prefix, fd.cFileName);
        else
            snprintf(rel, sizeof(rel), "%s", fd.cFileName);

        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", base_dir, rel);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!verify_dir(vfs, base_dir, rel))
                all_ok = 0;
        } else {
            if (!verify_file(vfs, rel, full))
                all_ok = 0;
        }
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);
#else
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", base_dir, rel_prefix);

    DIR *d = opendir(path);
    if (!d) {
        fprintf(stderr, "FAIL: cannot scan '%s'\n", path);
        return 0;
    }
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        /* R428: check snprintf returns — fail loudly on truncation instead of
         * silently skipping (also silences -Wformat-truncation). */
        char rel[1024];
        int ret;
        if (rel_prefix[0])
            ret = snprintf(rel, sizeof(rel), "%s/%s", rel_prefix, ent->d_name);
        else
            ret = snprintf(rel, sizeof(rel), "%s", ent->d_name);
        if (ret < 0 || (size_t)ret >= sizeof(rel)) {
            fprintf(stderr, "FAIL: path too long under '%s'\n", base_dir);
            all_ok = 0;
            continue;
        }

        char full[1024];
        ret = snprintf(full, sizeof(full), "%s/%s", base_dir, rel);
        if (ret < 0 || (size_t)ret >= sizeof(full)) {
            fprintf(stderr, "FAIL: path too long under '%s'\n", base_dir);
            all_ok = 0;
            continue;
        }

        struct stat st;
        if (stat(full, &st) != 0) continue;
        if (S_ISDIR(st.st_mode)) {
            if (!verify_dir(vfs, base_dir, rel))
                all_ok = 0;
        } else if (S_ISREG(st.st_mode)) {
            if (!verify_file(vfs, rel, full))
                all_ok = 0;
        }
    }
    closedir(d);
#endif
    return all_ok;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file.pak> <source_dir>\n", argv[0]);
        return 1;
    }

    const char *pak_path  = argv[1];
    const char *src_dir   = argv[2];

    VFS *vfs = vfs_create();
    if (!vfs_mount_pak(vfs, pak_path)) {
        fprintf(stderr, "FAIL: cannot mount pak '%s'\n", pak_path);
        vfs_destroy(vfs);
        return 1;
    }

    int all_ok = verify_dir(vfs, src_dir, "");

    vfs_destroy(vfs);

    if (all_ok) {
        printf("\nAll files verified successfully!\n");
        return 0;
    } else {
        printf("\nVerification FAILED!\n");
        return 1;
    }
}
