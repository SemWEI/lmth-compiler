#!/bin/bash

# Exit on any error
set -e

# Define LLVM version or branch (optional, e.g., "release/16.x")
LLVM_BRANCH="main"

# Install necessary dependencies
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake python3 python3-pip git

# Clone the LLVM project repository
echo "Cloning LLVM repository..."
if [ ! -d "llvm-project" ]; then
    git clone https://github.com/llvm/llvm-project.git
fi

# Change to the llvm-project directory
cd llvm-project

# Checkout to the specified branch or tag (optional)
git checkout $LLVM_BRANCH

# Create and navigate to the build directory
echo "Creating build directory..."
mkdir -p build
cd build

# Configure the build with CMake
echo "Configuring build with CMake..."
cmake -G "Unix Makefiles" \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
      -DCMAKE_BUILD_TYPE=Release \
      ../llvm

# Build LLVM
echo "Building LLVM..."
make -j$(nproc)

# Install LLVM
echo "Installing LLVM..."
sudo make install

# Optionally, add LLVM to the PATH
echo "Adding LLVM to PATH (optional)..."
echo 'export PATH=/usr/local/bin:$PATH' >> ~/.bashrc

# Reload shell configuration
source ~/.bashrc

# Verify installation
echo "Verifying LLVM installation..."
clang --version
llvm-config --version

echo "LLVM setup complete!"
