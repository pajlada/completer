#include <completer/completer.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

void
Completer::set_sort_mode(CompletionSortMode new_sort_mode)
{
    this->completion_sort_mode = new_sort_mode;
}

void
Completer::add_username(const char *username)
{
    this->all_completions.insert(username, CompletionType::Username);
    this->username_completions.insert(username, CompletionType::Username);
}

void
Completer::add_emote(const char *emote_code)
{
    this->all_completions.insert(emote_code, CompletionType::Emote);
}

bool
Completer::load_from_file(const char *path)
{
    ifstream xd(path);
    if (!xd.is_open()) {
        return false;
    }

    string line;

    while (getline(xd, line)) {
        if (line.size() == 0) {
            continue;
        }
        if (line[0] == '!') {
            this->add_emote(line.substr(1).c_str());
        } else {
            this->add_username(line.c_str());
        }
    }

    return true;
}

CompletionIteratorPair
Completer::tab(const char *prefix) const
{
    // if prefix is @, use username_completions only
    auto p = this->all_completions.equal_prefix_range(prefix);

    return {p.first, p.second};
}

SortedResult
Completer::tab_sorted(const char *prefix) const
{
    vector<Completion> completions;

    auto p = this->tab(prefix);

    for (; p.it != p.end; ++p.it) {
        completions.emplace_back(Completion{p.it.key(), p.it.value()});
    }

    switch (this->completion_sort_mode) {
        case CompletionSortMode::UsernamesFirst: {
            sort(completions.begin(), completions.end(),
                 [](const auto &a, const auto &b) {
                     return a.type < b.type ||
                            (a.type == b.type && a.key < b.key);
                 });
        } break;

        case CompletionSortMode::EmotesFirst: {
            sort(completions.begin(), completions.end(),
                 [](const auto &a, const auto &b) {
                     return a.type > b.type ||
                            (a.type == b.type && a.key < b.key);
                 });
        } break;

        case CompletionSortMode::TypeAgnostic: {
            sort(completions.begin(), completions.end(),
                 [](const auto &a, const auto &b) {
                     return a.key < b.key;  //
                 });
        } break;
    }

    return {this->updateIteration, move(completions)};
}

bool
SortedResult::isValid(Completer &completer)
{
    return completer.getUpdateIteration() == this->updateIteration;
}

vector<Completion>::iterator
SortedResult::next(bool wrap)
{
    if (this->first) {
        this->first = false;
        this->it = this->completions.begin();
        return this->it;
    }

    if (this->it == this->completions.end()) {
        // IT SHOULD NEVER REACH HERE FOR A WRAPPED ITERATOR. unless it's empty
        if (wrap) {
            this->it = this->completions.begin();
        }

        return this->it;
    }

    if (wrap) {
        auto ret = ++this->it;
        if (ret == this->completions.end()) {
            this->it = this->completions.begin();

            return this->it;
        }

        return ret;
    }

    return ++this->it;
}

vector<Completion>::iterator
SortedResult::previous(bool wrap)
{
    if (this->first) {
        this->first = false;
        if (wrap) {
            this->it = this->completions.end() - 1;
        } else {
            this->it = this->completions.begin();
        }

        return this->it;
    }

    if (this->it == this->completions.end()) {
        // IT SHOULD NEVER REACH HERE FOR A WRAPPED ITERATOR. unless it's empty
        if (wrap) {
            assert(false);
        }

        return this->it;
    }

    if (wrap) {
        if (this->it == this->completions.begin()) {
            this->it = this->completions.end() - 1;
            return this->it;
        }

        return --this->it;
    }

    return --this->it;
}

vector<Completion>::iterator
SortedResult::end()
{
    return this->completions.end();
}
