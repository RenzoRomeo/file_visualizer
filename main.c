#include <math.h>

#include "canvas.h"
#include "util.h"

void process_file(const char *path, Canvas *canvas) {
  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    ERROR("could not open file.");
  }

  uint8_t pair[2];
  while (fread(pair, 1, 2, fp) == 2) {
    size_t x = pair[0];
    size_t y = pair[1];
    increment_canvas_value(canvas, x, y, 20);
  }

  fclose(fp);
}

void write_ppm_file(const Canvas *canvas, const char *path) {
  FILE *fp = fopen(path, "wt");
  if (fp == NULL) {
    ERROR("could not open file.");
  }

  fprintf(fp, "P2\n%zu %zu\n255\n", canvas->width, canvas->height);
  for (size_t y = 0; y < canvas->height; y++) {
    for (size_t x = 0; x < canvas->width; x++) {
      fprintf(fp, "%d ", (uint8_t)fmin(get_canvas_value(canvas, x, y), 256));
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  Canvas canvas = create_canvas(256, 256);

  if (argc < 2) {
    ERROR("missing parameter: executable file path.");
  }

  char *path = argv[1];
  process_file(path, &canvas);

  char output_path_buffer[1024] = {0};
  get_output_path(output_path_buffer, 1024, path);

  upscale_canvas(&canvas, 10);

  write_ppm_file(&canvas, output_path_buffer);

  free_canvas(&canvas);
  return 0;
}
