#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint8_t *data;
  size_t width, height;
} Canvas;

Canvas create_canvas(size_t width, size_t height);

size_t canvas_index(const Canvas *canvas, size_t x, size_t y);

void free_canvas(Canvas *canvas);

uint8_t get_canvas_value(const Canvas *canvas, size_t x, size_t y);

void set_canvas_value(Canvas *canvas, size_t x, size_t y, uint8_t intensity);

void increment_canvas_value(Canvas *canvas, size_t x, size_t y);

uint8_t max_canvas_value(const Canvas *canvas);

#endif
