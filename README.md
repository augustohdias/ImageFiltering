# Image Filtering

Native C++ ```.npm``` basic image processor.

# Features

 - Negative filter;
 - Grayscale filter;
 
# Compiling/Executing

## Compiling on Windows

```
g++ main.cpp -o <name> -Wl,--stack,<size in bytes>
```

## Executing on Linux

```
g++ main.cpp -o <name>
ulimit -s unlimited
./<name>
```

# Notes

 - Only 1366x768 images are supported (can be changed on source code);

# TODO

 - Add new filters;
 - Add resize;
 - Add multi-size support;
 - ...
