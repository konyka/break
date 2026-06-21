/* verify_pak.c — Verify packer output is VFS-compatible
 *
 * Mounts a .pak file via VFS, reads each entry, and compares
 * against the original file on disk. */
#include <asset/vfs.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fseek(fp, 0, SEEK_SET);

    if ((usize)disk_size != pak_size) {
        fprintf(stderr, "FAIL: size mismatch for '%s' (pak=%zu, disk=%ld)\n",
                pak_name, pak_size, disk_size);
        fclose(fp);
        vfs_close(f);
        return 0;
    }

    /* Compare content */
    u8 *disk_buf = malloc(disk_size);
    fread(disk_buf, 1, disk_size, fp);
    fclose(fp);

    u8 *pak_buf = malloc(pak_size);
    usize nread = vfs_read(f, pak_buf, pak_size);
    if (nread != pak_size) {
        fprintf(stderr, "FAIL: short read for '%s' (%zu/%zu)\n",
                pak_name, nread, pak_size);
        free(disk_buf);
        free(pak_buf);
        vfs_close(f);
        return 0;
    }

    int match = memcmp(disk_buf, pak_buf, pak_size) == 0;
    if (!match) {
        fprintf(stderr, "FAIL: content mismatch for '%s'\n", pak_name);
    } else {
        printf("OK: '%s' (%zu bytes) matches\n", pak_name, pak_size);
    }

    free(disk_buf);
    free(pak_buf);
    vfs_close(f);
    return match;
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

    int all_ok = 1;

#ifdef _WIN32
    char pattern[1024];
    snprintf(pattern, sizeof(pattern), "%s/*", src_dir);
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(pattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "FAIL: cannot scan '%s'\n", src_dir);
        vfs_destroy(vfs);
        return 1;
    }
    do {
        if (fd.cFileName[0] == '.') continue;
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", src_dir, fd.cFileName);
        if (!verify_file(vfs, fd.cFileName, full))
            all_ok = 0;
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);
#else
    DIR *d = opendir(src_dir);
    if (!d) {
        fprintf(stderr, "FAIL: cannot scan '%s'\n", src_dir);
        vfs_destroy(vfs);
        return 1;
    }
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", src_dir, ent->d_name);

        struct stat st;
        if (stat(full, &st) != 0 || !S_ISREG(st.st_mode)) continue;

        if (!verify_file(vfs, ent->d_name, full))
            all_ok = 0;
    }
    closedir(d);
#endif

    vfs_destroy(vfs);

    if (all_ok) {
        printf("\nAll files verified successfully!\n");
        return 0;
    } else {
        printf("\nVerification FAILED!\n");
        return 1;
    }
}
