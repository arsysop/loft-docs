# loft-docs
LOFT Documentation

![Build Status](https://github.com/arsysop/loft-docs/workflows/CI/badge.svg)

## Vector tests

### Building

```
cd examples/vectorTests
cmake -G "<generator>" -S "" -B "build"
cmake --build build
```

### Running tests

```
cd build
ctest
```