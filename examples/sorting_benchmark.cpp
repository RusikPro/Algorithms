# Example: Google Benchmark with sorting algorithms
#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <random>

// Generate random vector
std::vector<int> generateRandomVector(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    for (auto& x : vec) {
        x = dis(gen);
    }
    return vec;
}

// Bubble sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Quick sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Benchmark functions
static void BM_BubbleSort(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto vec = generateRandomVector(state.range(0));
        state.ResumeTiming();

        bubbleSort(vec);
    }
}

static void BM_QuickSort(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto vec = generateRandomVector(state.range(0));
        state.ResumeTiming();

        quickSort(vec, 0, vec.size() - 1);
    }
}

static void BM_STLSort(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto vec = generateRandomVector(state.range(0));
        state.ResumeTiming();

        std::sort(vec.begin(), vec.end());
    }
}

// Register benchmarks
BENCHMARK(BM_BubbleSort)->Range(8, 1024);
BENCHMARK(BM_QuickSort)->Range(8, 8192);
BENCHMARK(BM_STLSort)->Range(8, 8192);

BENCHMARK_MAIN();
