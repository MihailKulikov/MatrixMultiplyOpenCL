#include <stdio.h>
#include <malloc.h>

long loadCLKernel(const char* path, char **buf) {
    FILE *file_pointer;
    size_t file_size;
    long off_end;
    int ret;

    file_pointer = fopen(path, "r");
    if (NULL == file_pointer) {
        return -1L;
    }

    ret = fseek(file_pointer, 0L, SEEK_END);
    if (0 != ret) {
        return -1L;
    }

    if (0 > (off_end = ftell(file_pointer))) {
        return -1L;
    }
    file_size = (size_t) off_end;

    *buf = (char *) malloc(file_size + 1);
    if (NULL == *buf) {
        return -1L;
    }

    rewind(file_pointer);

    size_t read_elements_count = fread(*buf, sizeof(char), file_size, file_pointer);

    if (EOF == fclose(file_pointer)) {
        free(*buf);
        return -1L;
    }

    (*buf)[read_elements_count] = '\0';

    return (long) read_elements_count;
}