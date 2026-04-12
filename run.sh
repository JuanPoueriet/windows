#!/bin/bash
set -e

# Define the build directory
BUILD_DIR="build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Run cmake
cmake ..

# Compile the application
make -j$(nproc)

# Execute the application
echo "Starting ChromeTabsQt..."
./ChromeTabsQt
