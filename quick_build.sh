#!/bin/bash

# Quick build script for C++ Algorithms project
# Usage: ./quick_build.sh [file.cpp] [options]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
BUILD_TYPE="Debug"
CLEAN_BUILD=false
RUN_AFTER_BUILD=false
CMAKE_BUILD=false

print_usage() {
    echo "Usage: $0 [file.cpp] [options]"
    echo ""
    echo "Options:"
    echo "  -r, --run           Run the executable after building"
    echo "  -c, --clean         Clean build (remove build directory first)"
    echo "  --release           Build in Release mode (default: Debug)"
    echo "  --cmake             Use CMake build system instead of direct g++"
    echo "  -h, --help          Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 leetcode/1_two_sum.cpp -r    # Build and run"
    echo "  $0 -c --cmake                   # Clean CMake build all"
    echo "  $0 --cmake --release            # CMake Release build"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -r|--run)
            RUN_AFTER_BUILD=true
            shift
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        --release)
            BUILD_TYPE="Release"
            shift
            ;;
        --cmake)
            CMAKE_BUILD=true
            shift
            ;;
        -h|--help)
            print_usage
            exit 0
            ;;
        *.cpp)
            CPP_FILE="$1"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            print_usage
            exit 1
            ;;
    esac
done

# Get script directory (project root)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

if [ "$CMAKE_BUILD" = true ]; then
    echo -e "${BLUE}Using CMake build system${NC}"

    BUILD_DIR="build"

    if [ "$CLEAN_BUILD" = true ]; then
        echo -e "${YELLOW}Cleaning build directory...${NC}"
        rm -rf "$BUILD_DIR"
    fi

    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    echo -e "${BLUE}Configuring with CMake...${NC}"
    cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

    if [ -n "$CPP_FILE" ]; then
        # Build specific target
        rel_path="${CPP_FILE#./}"
        target_name="${rel_path//\//_}"
        target_name="${target_name%.cpp}"

        echo -e "${BLUE}Building target: $target_name${NC}"
        cmake --build . --target "$target_name"

        if [ "$RUN_AFTER_BUILD" = true ]; then
            exe_path="../$(dirname "$CPP_FILE")/$(basename "$CPP_FILE" .cpp).out"
            if [ -f "$exe_path" ]; then
                echo -e "${GREEN}Running: $exe_path${NC}"
                cd ..
                "$exe_path"
            else
                echo -e "${RED}Executable not found: $exe_path${NC}"
                exit 1
            fi
        fi
    else
        # Build all targets
        echo -e "${BLUE}Building all targets...${NC}"
        cmake --build .
    fi

elif [ -n "$CPP_FILE" ]; then
    # Direct g++ compilation
    if [ ! -f "$CPP_FILE" ]; then
        echo -e "${RED}Error: File '$CPP_FILE' not found${NC}"
        exit 1
    fi

    # Get file info
    FILE_DIR="$(dirname "$CPP_FILE")"
    FILE_NAME="$(basename "$CPP_FILE" .cpp)"
    EXECUTABLE="$FILE_DIR/$FILE_NAME.out"

    echo -e "${BLUE}Building: $CPP_FILE${NC}"

    # Determine compiler flags based on file content
    EXTRA_FLAGS=""
    EXTRA_INCLUDES=""

    # Check for Homebrew installation paths
    GTEST_PREFIX="/opt/homebrew"
    BENCHMARK_PREFIX="/opt/homebrew"

    if grep -q "gtest\|TEST(\|testing::" "$CPP_FILE"; then
        echo -e "${YELLOW}Detected Google Test usage${NC}"
        EXTRA_INCLUDES="-I${GTEST_PREFIX}/include"
        EXTRA_FLAGS="-L${GTEST_PREFIX}/lib -lgtest -lgtest_main -lpthread"
    elif grep -q "benchmark\|BENCHMARK(" "$CPP_FILE"; then
        echo -e "${YELLOW}Detected Google Benchmark usage${NC}"
        EXTRA_INCLUDES="-I${BENCHMARK_PREFIX}/include"
        EXTRA_FLAGS="-L${BENCHMARK_PREFIX}/lib -lbenchmark -lpthread"
    fi

    # Compile
    g++ -fcolor-diagnostics -fansi-escape-codes -g -std=c++17 \
        -I"$SCRIPT_DIR/common" \
        $EXTRA_INCLUDES \
        "$CPP_FILE" \
        -o "$EXECUTABLE" \
        $EXTRA_FLAGS

    echo -e "${GREEN}Build successful: $EXECUTABLE${NC}"

    if [ "$RUN_AFTER_BUILD" = true ]; then
        echo -e "${GREEN}Running: $EXECUTABLE${NC}"
        cd "$FILE_DIR"
        "./$FILE_NAME.out"
    fi

else
    echo -e "${RED}Error: No C++ file specified and --cmake not used${NC}"
    print_usage
    exit 1
fi
