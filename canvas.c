#include "canvas.h"
#include "util.h"

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
