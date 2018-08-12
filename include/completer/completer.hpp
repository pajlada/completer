#pragma once

#include "tsl/htrie_map.h"

#include <mutex>
#include <vector>

enum class CompletionType {
    Username,
    Emote,
};

struct Completion {
    std::string key;
    CompletionType type;
};

using CompletionMap = tsl::htrie_map<char, CompletionType>;
using CompletionMapConstIterator = CompletionMap::const_prefix_iterator;

struct CompletionIteratorPair {
    CompletionMapConstIterator it;
    CompletionMapConstIterator end;
};

enum class CompletionSortMode {
    // Mix emotes and usernames
    TypeAgnostic,

    // Sort usernames before emotes
    UsernamesFirst,

    // Sort emotes before usernames
    EmotesFirst,
};

class SortedResult;

class Completer
{
    CompletionMap all_completions;
    CompletionMap username_completions;
    CompletionSortMode completion_sort_mode = CompletionSortMode::TypeAgnostic;

    uint32_t updateIteration;
    mutable std::mutex updateIterationMutex;

public:
    void set_sort_mode(CompletionSortMode new_sort_mode);

    uint32_t
    getUpdateIteration() const
    {
        std::lock_guard<std::mutex> lock(this->updateIterationMutex);

        return this->updateIteration;
    }

    void add_username(const char *username);
    void add_emote(const char *emote_code);

    bool load_from_file(const char *path);

    CompletionIteratorPair tab(const char *prefix) const;
    SortedResult tab_sorted(const char *prefix) const;
};

class SortedResult
{
    bool first = true;
    uint32_t updateIteration;

    std::vector<Completion> completions;

    std::vector<Completion>::iterator it;

    SortedResult(uint32_t updateIteration_,
                 std::vector<Completion> &&completions_)
        : updateIteration(updateIteration_)
        , completions(std::move(completions_))
    {
        this->it = this->completions.end();
    }

    friend class Completer;

public:
    SortedResult(SortedResult &&) = default;
    SortedResult &operator=(SortedResult &&) = default;

    // SortedResult(const SortedResult &) = delete;
    // SortedResult &operator=(const SortedResult &) = delete;
    bool isValid(Completer &completer);

    std::vector<Completion>::size_type
    size() const
    {
        return this->completions.size();
    }

    std::vector<Completion>::iterator next(bool wrap);
    std::vector<Completion>::iterator previous(bool wrap);
    std::vector<Completion>::iterator end();
};
