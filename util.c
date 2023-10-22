#include "util.h"

void get_executable_name(char *buffer, const char *path) {
  size_t name_index = 0;

  for (size_t i = 0; i < strlen(path); i++) {
    if (path[i] == '/')
      name_index = i;
  }
  name_index += 1;

  strncpy(buffer, path + name_index, 256);
}

void get_output_path(char *buffer, size_t buffer_size, const char *path) {
  char executable_name_buffer[256] = {0};
  get_executable_name(executable_name_buffer, path);

  strcat(buffer, "./output/");
  strncat(buffer, executable_name_buffer, buffer_size);
  strcat(buffer, ".ppm");
}
