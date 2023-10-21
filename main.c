#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR(message)                                                         \
  do {                                                                         \
    fprintf(stderr, "[ERROR] %s\n", message);                                  \
    exit(1);                                                                   \
  } while (0)

typedef struct {
  uint8_t *data;
  size_t width, height;
} Canvas;

Canvas create_canvas(size_t width, size_t height) {
  uint8_t *data = (uint8_t *)calloc(width * height, sizeof(uint8_t));
  Canvas out;
  out.data = data;
  out.width = width;
  out.height = height;
  return out;
}

size_t canvas_index(const Canvas *canvas, size_t x, size_t y) {
  if (x >= canvas->width || y >= canvas->height)
    ERROR("index out of bounds");
  return y * canvas->width + x;
}

void free_canvas(Canvas *canvas) { free(canvas->data); }

uint8_t get_canvas_value(const Canvas *canvas, size_t x, size_t y) {
  return canvas->data[canvas_index(canvas, x, y)];
}

void set_canvas_value(Canvas *canvas, size_t x, size_t y, uint8_t intensity) {
  canvas->data[canvas_index(canvas, x, y)] = intensity;
}

void increment_canvas_value(Canvas *canvas, size_t x, size_t y) {
  canvas->data[canvas_index(canvas, x, y)]++;
}

uint8_t max_canvas_value(const Canvas *canvas) {
  uint8_t max = 0;
  for (size_t y = 0; y < canvas->height; y++) {
    for (size_t x = 0; x < canvas->width; x++) {
      uint8_t value = get_canvas_value(canvas, x, y);
      if (value > max) {
        max = value;
      }
    }
  }
  return max;
}

void process_file(const char *path, Canvas *canvas) {
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    ERROR("could not open file");
  }

  uint8_t pair[2];
  while (fread(pair, 1, 2, fp) == 2) {
    size_t x = pair[0];
    size_t y = pair[1];
    increment_canvas_value(canvas, x, y);
  }

  fclose(fp);

  for (size_t y = 0; y < canvas->height; y++) {
    for (size_t x = 0; x < canvas->width; x++) {
      float normalized_value =
          (float)get_canvas_value(canvas, x, y) / max_canvas_value(canvas);
      uint8_t intensity_value = normalized_value * 255;
      set_canvas_value(canvas, x, y, intensity_value);
    }
  }
}

void write_ppm_file(const Canvas *canvas, const char *path) {
  FILE *fp = fopen(path, "wt");
  if (fp == NULL) {
    ERROR("could not open file");
  }

  fprintf(fp, "P2\n%zu %zu\n255\n", canvas->width, canvas->height);
  for (size_t y = 0; y < canvas->height; y++) {
    for (size_t x = 0; x < canvas->width; x++) {
      fprintf(fp, "%d ", get_canvas_value(canvas, x, y));
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

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

int main(int argc, char *argv[]) {
  Canvas canvas = create_canvas(256, 256);

  if (argc < 2) {
    ERROR("missing parameter: executable file path");
  }

  char *path = argv[1];
  process_file(path, &canvas);

  char output_path_buffer[1024] = {0};
  get_output_path(output_path_buffer, 1024, path);
  write_ppm_file(&canvas, output_path_buffer);

  free_canvas(&canvas);
  return 0;
}
