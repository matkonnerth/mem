#include <benchmark/benchmark.h>
#include <ArenaAllocator.h>
#include <string.h>

void createObjects_Calloc(size_t size, size_t objSize)
{
    for(size_t cnt = 0; cnt < size; cnt++)
    {
        void *mem = calloc(1, objSize);
        benchmark::DoNotOptimize(mem);
    }
    //we know that mem is lost in this solution
    //freeing memory here up would also take time, so in praxis BlockAlloc performs even better
}

void createObjects_BlockAlloc(size_t size, size_t objSize)
{
    mem::ArenaAllocator a(102400);
    for (size_t cnt = 0; cnt < size; cnt++)
    {
        void *mem = a.alloc(objSize);
        benchmark::DoNotOptimize(mem);
    }
}

static void BM_BlockAllocator(benchmark::State &state)
{
    
    // Perform setup here
    for (auto _ : state)
    {
        createObjects_BlockAlloc(state.range(0), 16);
    }
}

static void BM_Calloc(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        createObjects_Calloc(state.range(0), 16);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Calloc)->Range(100, 1000*1000);
BENCHMARK(BM_BlockAllocator)->Range(100, 1000 * 1000);
// Run the benchmark
BENCHMARK_MAIN();