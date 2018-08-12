#include "gtest/gtest.h"

#include <completer/completer.hpp>

using namespace std;

void
ASSERT_MATCH_EQ(const vector<string> &a, SortedResult &&b)
{
    ASSERT_EQ(a.size(), b.size());
    int i = 0;
    auto it = b.next(false);
    while (it != b.end()) {
        ASSERT_EQ(a[i], it->key);
        it = b.next(false);
        i++;
    }
}

TEST(Completer, NinjaViewers)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/ninja-viewers.txt"));

    vector<string> correctMatch = {
        "tes_assassin08", "tesco__express", "tesik_one",
        "testa_killz",    "testedooman535", "testheader",
        "testifyz",       "testkontodavid", "testyagate221"};

    auto p = completer.tab_sorted("tes");

    ASSERT_MATCH_EQ(correctMatch, move(p));
}

TEST(Completer, Full)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    vector<string> correctMatch;

    correctMatch = {"forsen",      "forsenE", "forsenL",
                    "forsenOMEGA", "forsenW", "forsen_lost_this_xd",
                    "forsen_quote"};

    {
        auto completions = completer.tab_sorted("forsen");
        ASSERT_MATCH_EQ(correctMatch, move(completions));
    }

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    correctMatch = {
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    ASSERT_MATCH_EQ(correctMatch, completer.tab_sorted("forsen"));

    completer.set_sort_mode(CompletionSortMode::EmotesFirst);

    correctMatch = {
        "forsenE",      "forsenL", "forsenOMEGA",
        "forsenW",      "forsen",  "forsen_lost_this_xd",
        "forsen_quote",
    };

    ASSERT_MATCH_EQ(correctMatch, completer.tab_sorted("forsen"));

    correctMatch = {"forsen",      "forsenE", "forsenL",
                    "forsenOMEGA", "forsenW", "forsen_lost_this_xd",
                    "forsen_quote"};

    completer.set_sort_mode(CompletionSortMode::TypeAgnostic);

    ASSERT_MATCH_EQ(correctMatch, completer.tab_sorted("forsen"));
}

TEST(Completer, FullInterrupted)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    auto correctMatch = vector<string>{
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    auto sortedResult = completer.tab_sorted("forsen");
    ASSERT_EQ(correctMatch[0], sortedResult.next(false)->key);
}

TEST(Completer, FullNoWrap)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    auto correctMatch = vector<string>{
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    auto sortedResult = completer.tab_sorted("forsen");
    ASSERT_EQ(correctMatch[0], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[1], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[2], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[3], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[4], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[5], sortedResult.next(false)->key);
    ASSERT_EQ(correctMatch[6], sortedResult.next(false)->key);
    ASSERT_EQ(sortedResult.end(), sortedResult.next(false));
}

TEST(Completer, FullNextWrap)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    auto correctMatch = vector<string>{
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    {
        auto sortedResult = completer.tab_sorted("forsen");
        for (int i = 0; i < 500; ++i) {
            ASSERT_NE(sortedResult.end(), sortedResult.next(true));
        }
    }

    {
        auto sortedResult = completer.tab_sorted("forsen");
        ASSERT_EQ(correctMatch[0], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[6], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[0], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[6], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[0], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[6], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[0], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.next(true)->key);
        ASSERT_EQ(correctMatch[6], sortedResult.next(true)->key);
    }
}

TEST(Completer, FullPreviousWrap)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    auto correctMatch = vector<string>{
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    {
        auto sortedResult = completer.tab_sorted("forsen");
        for (int i = 0; i < 500; ++i) {
            ASSERT_NE(sortedResult.end(), sortedResult.previous(true));
        }
    }

    {
        auto sortedResult = completer.tab_sorted("forsen");
        ASSERT_EQ(correctMatch[6], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[0], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[6], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[5], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[4], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[3], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[2], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[1], sortedResult.previous(true)->key);
        ASSERT_EQ(correctMatch[0], sortedResult.previous(true)->key);
    }
}

TEST(Completer, FullNextPreviousWrapMixed)
{
    Completer completer;

    EXPECT_TRUE(completer.load_from_file("files/full.txt"));

    completer.set_sort_mode(CompletionSortMode::UsernamesFirst);

    auto correctMatch = vector<string>{
        "forsen",  "forsen_lost_this_xd", "forsen_quote", "forsenE",
        "forsenL", "forsenOMEGA",         "forsenW",
    };

    auto sortedResult = completer.tab_sorted("forsen");
    // forsenW
    ASSERT_EQ(correctMatch[6], sortedResult.previous(true)->key);
    // forsenOMEGA
    ASSERT_EQ(correctMatch[5], sortedResult.previous(true)->key);
    // forsenL
    ASSERT_EQ(correctMatch[4], sortedResult.previous(true)->key);
    // forsenOMEGA
    ASSERT_EQ(correctMatch[5], sortedResult.next(true)->key);
    ASSERT_EQ(correctMatch[6], sortedResult.next(true)->key);
    ASSERT_EQ(correctMatch[0], sortedResult.next(true)->key);
    ASSERT_EQ(correctMatch[1], sortedResult.next(true)->key);
    ASSERT_EQ(correctMatch[2], sortedResult.next(true)->key);
    ASSERT_EQ(correctMatch[1], sortedResult.previous(true)->key);
    ASSERT_EQ(correctMatch[0], sortedResult.previous(true)->key);
    ASSERT_EQ(correctMatch[6], sortedResult.previous(true)->key);
}
