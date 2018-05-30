## Image Filtering

A ```.npm``` image basic processor using native C++.

## Features

 - Negative filter;
 - Grayscale filter;
 
## Compiling

Compiling on Windows
----------------------
g++ main.cpp -o <name> -Wl,--stack,<size in bytes>

## Notes
 - Only 1366x768 images are supported (can be changed on source code);

## TODO

 - Add new filters;
 - Add resize;
 - Any image size support;
 - ...
