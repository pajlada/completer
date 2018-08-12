#include <completer/completer.hpp>
#include <iostream>

void
test_a(const SortedResult &b)
{
}

void
test_b(SortedResult b)
{
    auto it = b.next(false);
    while (it != b.end()) {
        std::cerr << "Value: " << it->key << '\n';
        it = b.next(false);
    }
}

void
test_c(SortedResult &b)
{
    auto it = b.next(false);
    while (it != b.end()) {
        std::cerr << "Value: " << it->key << '\n';
        it = b.next(false);
    }
}

int
main()
{
    Completer completer;

    completer.load_from_file("files/ninja-viewers.txt");

    std::vector<std::string> a = {
        "tes_assassin08", "tesco__express", "tesik_one",
        "testa_killz",    "testedooman535", "testheader",
        "testifyz",       "testkontodavid", "testyagate221"};

    auto b = completer.tab_sorted("tes");

    int i = 0;
    auto it = b.next(false);
    while (it != b.end()) {
        it = b.next(false);
    }

    test_a(b);

    it = b.next(false);
    while (it != b.end()) {
        it = b.next(false);
    }

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    test_b(completer.tab_sorted("tes"));
    auto xd = completer.tab_sorted("tes");
    test_c(xd);

    return 0;
}
