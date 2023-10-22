# File content visualizer

Small tool written in C that displays the contents of a file by taking each pair of consecutive bytes and interpreting them as coordinates on a 256x256 canvas. The intensity of each pixel is determined by the amount of times that specific pair of bytes appears in the file.

Inspired by this talk from Christopher Domas: https://www.youtube.com/watch?v=4bM3Gut1hIk

## Building

```bash
chmod +x ./build.sh && ./build.sh
```

## Usage

```bash
file_visualizer <file path>
```

The output will be saved inside the "output" directory as a PGM image (https://en.wikipedia.org/wiki/Netpbm) with the name of the file.

## Example output

### "ls" executable (/bin/ls)
![Sin título](https://github.com/RenzoRomeo/file_visualizer/assets/46039237/d9196d6b-0050-456f-a414-b3ee05eee3e9)

