#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int is_directory(const char *path) {
    struct stat fileStat;
    if (stat(path, &fileStat) == -1) {
        perror("Error getting file information");
        exit(1);
    }
    return S_ISDIR(fileStat.st_mode);
}

int ends_with_bmp(const char *filename) {
    size_t length = strlen(filename);
    return (length >= 4 && strcmp(filename + length - 4, ".bmp") == 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];

    if (is_directory(path)) {
        printf("%s is a directory.\n", path);
    } else {
        if (ends_with_bmp(path)) {
            printf("%s is a BMP file.\n", path);
        } else {
            printf("%s is not a directory or does not end with .bmp.\n", path);
        }
    }

    return 0;
}
