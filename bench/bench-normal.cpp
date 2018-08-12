#include <benchmark/benchmark.h>
#include <completer/completer.hpp>

using namespace std;

class Normal : public benchmark::Fixture
{
public:
    Completer completer;

    Normal()
    {
        this->completer.load_from_file("files/full.txt");
    }
};

BENCHMARK_F(Normal, TabRandom)(benchmark::State &state)
{
    for (auto _ : state) {
        auto tab = this->completer.tab_sorted("f");
    }
}
