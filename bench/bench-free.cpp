#include <benchmark/benchmark.h>
#include <completer/completer.hpp>

#include <chrono>

using namespace std;

static void
BM_AddExistingUsername(benchmark::State &state)
{
    for (auto _ : state) {
        Completer completer;
        completer.load_from_file("files/ninja-viewers.txt");
        auto start = chrono::high_resolution_clock::now();
        completer.add_username("0000000015");
        auto end = chrono::high_resolution_clock::now();

        auto elapsed_seconds =
            chrono::duration_cast<chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed_seconds.count());
    }
}
BENCHMARK(BM_AddExistingUsername)->UseManualTime()->Iterations(20);

static void
BM_AddNewUsername(benchmark::State &state)
{
    for (auto _ : state) {
        Completer completer;
        completer.load_from_file("files/ninja-viewers.txt");
        auto start = chrono::high_resolution_clock::now();
        completer.add_username("00000000000000000000000000000016");
        auto end = chrono::high_resolution_clock::now();

        auto elapsed_seconds =
            chrono::duration_cast<chrono::duration<double>>(end - start);

        state.SetIterationTime(elapsed_seconds.count());
    }
}
BENCHMARK(BM_AddNewUsername)->UseManualTime()->Iterations(20);
