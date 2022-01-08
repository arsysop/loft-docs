# loft-docs
LOFT Documentation

## Vector tests

### Building

```
cd examples/vectorTests
cmake -G "<generator>" -S "" -B "build"   # run "cmake -G" for list of generators
cmake --build build
```

### Running tests

```
cd build
ctest
```