#!/bin/sh

set xe

mkdir -p build
mkdir -p output

gcc main.c canvas.c util.c -O3 -o ./build/file_visualizer
