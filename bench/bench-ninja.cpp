#include <benchmark/benchmark.h>
#include <completer/completer.hpp>

using namespace std;

class NinjaViewers : public benchmark::Fixture
{
public:
    Completer completer;

    NinjaViewers()
    {
        this->completer.load_from_file("files/ninja-viewers.txt");
        this->Unit(benchmark::kMicrosecond);
    }
};

BENCHMARK_F(NinjaViewers, TabGeneral)(benchmark::State &state)
{
    for (auto _ : state) {
        auto tab = this->completer.tab_sorted("a");
    }
}

BENCHMARK_F(NinjaViewers, TabSpecific)(benchmark::State &state)
{
    for (auto _ : state) {
        auto tab = this->completer.tab_sorted("bobby");
    }
}
