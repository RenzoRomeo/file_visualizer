#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR(message)                                                         \
  do {                                                                         \
    fprintf(stderr, "[ERROR] %s\n", message);                                  \
    exit(1);                                                                   \
  } while (0)

void get_executable_name(char *buffer, const char *path);

void get_output_path(char *buffer, size_t buffer_size, const char *path);

#endif
