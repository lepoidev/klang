# This is a script to help install LLVM 11.0.1

TARGET_ARCH="x86_64"

LLVM_MAJ_VER=11
LLVM_REPO="$HOME/llvm-project"
LLVM_SOURCE_ROOT="$LLVM_REPO/llvm"
LLVM_BUILD_DIR="$HOME/llvm-$LLVM_MAJ_VER-$TARGET_ARCH"
LLVM_INS_DIR="$HOME/llvm-install-$TARGET_ARCH"
LLVM_DIR="$LLVM_INS_DIR/lib/cmake/llvm"

if [ -d "$LLVM_REPO" ]; then
    cd "$HOME"
    git clone https://github.com/llvm/llvm-project
    cd "$LLVM_REPO"
    git checkout llvmorg-11.0.1
fi

mkdir -p "$LLVM_BUILD_DIR"
cd "$LLVM_BUILD_DIR"

LLVM_OPTS="-DLLVM_BUILD_TOOLS=OFF -DLLVM_BUILD_TESTS=OFF -DLLVM_INCLUDE_TESTS=OFF -DLLVM_BUILD_EXAMPLES=OFF -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_OPTIMIZED_TABLEGEN=ON"

cmake "$LLVM_SOURCE_ROOT" -DCMAKE_OSX_ARCHITECTURES=$TARGET_ARCH -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=$LLVM_INS_DIR $LLVM_OPTS

cmake --build .

cmake --build . --target install


echo "Please add the follwing environment variables"
echo "export LLVM_INS_DIR=$LLVM_INS_DIR"
echo "export LLVM_DIR=$LLVM_DIR"
echo "export PATH=\$LLVM_INS_DIR/bin:\$PATH"