# Getting Started
## Dependencies
### ANTLR4
The `antlr` repository will be cloned by `cmake` into the `build` directory.
### LLVM
The `llvm` repo will need to be cloned and configured manually. Please follow [the LLVM setup script](scripts/llvm_get.sh) to setup `llvm`
## Building and Testing
### Build Compiler and Testers
```
cmake .
```
### Test Parser and Compiler
```
cd build
ctest . --output-on-failure
```