#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define build directory
BUILD_DIR="build"

# Step 1: Create a build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir $BUILD_DIR
fi

# Step 2: Navigate to the build directory
cd $BUILD_DIR

# Step 3: Run CMake to configure the build system
echo "Configuring the build with CMake..."
cmake ..

# Step 4: Build the project
echo "Building the project..."
make -j$(nproc)

# Step 5: Run the compiler if the build was successful
echo "Running the toy compiler..."
./toy-compiler

cd ..

echo "Build and execution complete!"