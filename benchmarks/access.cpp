#include <ArenaAllocator.h>
#include <benchmark/benchmark.h>
#include <string.h>

struct MyStruct
{
    int a;
    int b;
};

static void BM_Unaligned(benchmark::State &state)
{
    mem::ArenaAllocator a;
    a.alloc(100+state.range(0));
    auto mem = a.alloc(sizeof(MyStruct));
    auto s = new (mem) MyStruct();

    // Perform setup here
    for (auto _ : state)
    {
        s->a = 10;
        s->b = s->a;
        benchmark::DoNotOptimize(s);
    }
}

static void BM_Aligned(benchmark::State &state)
{
    auto s = new MyStruct();
    s->a = 10;
    s->b = 20;
    // Perform setup here
    for (auto _ : state)
    {
        s->a = 10;
        s->b = s->a;
        benchmark::DoNotOptimize(s);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Unaligned)->DenseRange(0,32,1);
BENCHMARK(BM_Aligned);
// Run the benchmark
BENCHMARK_MAIN();