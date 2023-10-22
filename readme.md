# File content visualizer

Small tool written in C that displays the contents of a file by taking each pair of consecutive bytes and interpreting them as coordinates on a 256x256 canvas. The intensity of each pixel is determined by the amount of times that specific pair of bytes appears in the file.

## Building

```bash
chmod +x ./build.sh && ./build.sh
```

## Usage

```bash
file_visualizer <file path>
```

The output will be saved inside the "output" directory as a PGM image (https://en.wikipedia.org/wiki/Netpbm) with the name of the file.

## Example outputs

### "ls" executable (/bin/ls)
![Sin título](https://github.com/RenzoRomeo/file_visualizer/assets/46039237/d57feac4-4d31-440e-abe1-66df0273d2dd)


### "grep" executable (/bin/grep)
![Sin título](https://github.com/RenzoRomeo/file_visualizer/assets/46039237/e2b8c6c1-f7fd-4b23-b59a-8d7fe71cbe1f)
