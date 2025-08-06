# C++ Algorithms Project - Build Instructions

This project provides multiple ways to build and run C++ examples with support for external libraries like Google Test and Google Benchmark.

## Quick Start

### Method 1: Direct Compilation (Recommended for single files)

```bash
# Build and run in one command
./quick_build.sh leetcode/1_two_sum.cpp -r

# Just build
./quick_build.sh leetcode/1_two_sum.cpp

# Clean build with release mode
./quick_build.sh fibonacci.cpp --release -r
```

### Method 2: CMake Build System (Recommended for complex builds)

```bash
# Build all targets
./quick_build.sh --cmake

# Clean build
./quick_build.sh -c --cmake

# Build specific file with CMake
./quick_build.sh leetcode/857_min_cost_to_hire.cpp --cmake -r
```

### Method 3: Manual Build (Traditional way)

```bash
# Navigate to any folder
cd leetcode

# Compile and run
g++ -std=c++17 -I../common 1_two_sum.cpp -o 1_two_sum
./1_two_sum
```

## Using External Libraries

### Google Test
Files with `#include <gtest/gtest.h>` or `TEST(` macros are automatically detected:

```bash
# This will automatically link gtest
./quick_build.sh leetcode/857_min_cost_to_hire.cpp -r
```

### Google Benchmark
Files with `#include <benchmark/benchmark.h>` or `BENCHMARK(` macros:

```bash
# This will automatically link benchmark
./quick_build.sh your_benchmark.cpp -r
```

## Utility Scripts

### quick_build.sh Options
- `-r, --run`: Run executable after building
- `-c, --clean`: Clean build (remove build directory)
- `--release`: Build in Release mode (default: Debug)
- `--cmake`: Use CMake build system
- `-h, --help`: Show help

### run.sh
Quick utility to run executables in current directory:

```bash
cd leetcode
../run.sh           # Lists available executables
../run.sh a.out     # Runs specific executable
```

## Examples

### Simple Algorithm
```bash
./quick_build.sh leetcode/3_longest_substring.cpp -r
```

### With Google Test
```bash
./quick_build.sh leetcode/3075_maximize_happiness.cpp -r
```

### Using CMake for All
```bash
./quick_build.sh --cmake --release
cd leetcode
../run.sh
```

## Project Structure Benefits

- **Modular**: Each folder contains related algorithms
- **Flexible**: Choose between direct compilation or CMake
- **Auto-detection**: Libraries are automatically linked based on includes
- **Common utilities**: Shared headers in `/common` folder
- **In-place compilation**: Executables are created alongside source files

## Adding New Examples

1. Create your `.cpp` file in appropriate folder
2. Include necessary headers:
   ```cpp
   #include "timer.h"        // For timing utilities
   #include "constants.h"    // For common constants
   ```
3. For tests, include:
   ```cpp
   #include <gtest/gtest.h>
   ```
4. Build with: `./quick_build.sh your_file.cpp -r`

The build system will automatically detect dependencies and link appropriate libraries!
