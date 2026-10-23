#pragma once

#include <string>
#include <unordered_set>
#include <vector>

namespace sa2026::problems::wordladder {

/*
 * The list of allowed words. Every word in the ladder must be in the dictionary.
 *
 * We use an unordered_set (like HashSet in Java), so contains() is fast
 * (it does not check the words one by one).
 */
class WordDictionary {
public:
    // Java uses "String...". Here we pass a vector: WordDictionary({"cat", "dog"})
    explicit WordDictionary(const std::vector<std::string>& words);

    // a small dictionary of 3-letter words, good for class examples
    static WordDictionary threeLetterWords();

    bool contains(const std::string& word) const;

private:
    std::unordered_set<std::string> words;
};

// C++ strings have no toLowerCase() like Java, so we write it ourselves
std::string toLowerCase(const std::string& text);

}  // namespace sa2026::problems::wordladder
