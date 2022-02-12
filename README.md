# loft-docs
![docs](https://user-images.githubusercontent.com/15957500/153713074-a2d3aa95-8581-4f77-a1f3-725ae51eba71.png)

![Build Status](https://github.com/arsysop/loft-docs/workflows/CI/badge.svg)

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
