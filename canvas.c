#include "canvas.h"
#include "util.h"
#include <stddef.h>
#include <stdint.h>

Canvas create_canvas(size_t width, size_t height) {
  size_t *data = (size_t *)calloc(width * height, sizeof(size_t));
  Canvas out;
  out.data = data;
  out.width = width;
  out.height = height;
  return out;
}

size_t canvas_index(const Canvas *canvas, size_t x, size_t y) {
  if (x >= canvas->width || y >= canvas->height)
    ERROR("index out of bounds.");
  return y * canvas->width + x;
}

void free_canvas(Canvas *canvas) { free(canvas->data); }

uint8_t get_canvas_value(const Canvas *canvas, size_t x, size_t y) {
  return canvas->data[canvas_index(canvas, x, y)];
}

void set_canvas_value(Canvas *canvas, size_t x, size_t y, uint8_t intensity) {
  canvas->data[canvas_index(canvas, x, y)] = intensity;
}

void increment_canvas_value(Canvas *canvas, size_t x, size_t y,
                            size_t increment) {
  canvas->data[canvas_index(canvas, x, y)] += increment;
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

void upscale_canvas(Canvas *canvas, size_t factor) {
  size_t new_width = canvas->width * factor;
  size_t new_height = canvas->height * factor;
  Canvas new_canvas = create_canvas(new_width, new_height);

  for (size_t y = 0; y < canvas->height; y++) {
    for (size_t x = 0; x < canvas->width; x++) {
      size_t intensity = get_canvas_value(canvas, x, y);
      for (size_t u = 0; u < factor; u++) {
        for (size_t v = 0; v < factor; v++) {
          set_canvas_value(&new_canvas, x * factor + u, y * factor + v,
                           intensity);
        }
      }
    }
  }

  free_canvas(canvas);

  canvas->width = new_width;
  canvas->height = new_height;
  canvas->data = new_canvas.data;
}
