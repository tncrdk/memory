#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm> // For std::fill


namespace memory_benchmark {

void memory_bandwidth_benchmark(size_t array_size_mb) {
    // Allocate a large array
    size_t array_size_bytes = array_size_mb * 1024 * 1024;
    std::vector<char> data(array_size_bytes);

    // Initialize the array to ensure it's in main memory, not just allocated
    std::fill(data.begin(), data.end(), 0);

    long long read_sum = 0;
    long long write_sum = 0;

    // --- Write Benchmark ---
    std::cout << "Benchmarking Memory Write Bandwidth (" << array_size_mb << " MB)..." << std::endl;
    auto start_write = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < array_size_bytes; ++i) {
        data[i] = static_cast<char>(i % 256);
    }
    auto end_write = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_write = end_write - start_write;
    double write_bandwidth_gbps = static_cast<double>(array_size_bytes) / (1024.0 * 1024.0 * 1024.0) / duration_write.count();
    std::cout << "Write time: " << duration_write.count() << " seconds, Bandwidth: " << write_bandwidth_gbps << " GB/s" << std::endl;

    // --- Read Benchmark ---
    std::cout << "\nBenchmarking Memory Read Bandwidth (" << array_size_mb << " MB)..." << std::endl;
    auto start_read = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < array_size_bytes; ++i) {
        read_sum += data[i]; // Read and accumulate to prevent optimization
    }
    auto end_read = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_read = end_read - start_read;
    double read_bandwidth_gbps = static_cast<double>(array_size_bytes) / (1024.0 * 1024.0 * 1024.0) / duration_read.count();
    std::cout << "Read time: " << duration_read.count() << " seconds, Bandwidth: " << read_bandwidth_gbps << " GB/s" << std::endl;
    
    // To ensure read_sum is not optimized away if compiler is too smart
    volatile long long temp_sum = read_sum;
}

void run() {
    size_t test_size_mb = 512; // Adjust to be larger than your CPU's cache sizes
    memory_bandwidth_benchmark(test_size_mb);
}

} // namespace memory_benchmark
