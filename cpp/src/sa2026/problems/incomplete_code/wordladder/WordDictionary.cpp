#include "sa2026/problems/incomplete_code/wordladder/WordDictionary.h"

#include <cctype>

namespace sa2026::problems::incomplete_code::wordladder {

WordDictionary::WordDictionary(const std::vector<std::string>& words) {
    for (const std::string& word : words) {
        this->words.insert(toLowerCase(word));
    }
}

WordDictionary WordDictionary::threeLetterWords() {
    return WordDictionary({
            "ant", "ape", "arm", "art", "ask", "ate", "bad", "bag", "bat", "bed",
            "bee", "beg", "bet", "big", "bin", "bit", "box", "boy", "bud", "bug",
            "bun", "bus", "but", "buy", "cab", "can", "cap", "car", "cat", "cog",
            "cot", "cow", "cub", "cup", "cut", "dad", "day", "den", "dig", "dim",
            "dip", "dog", "dot", "dry", "dug", "ear", "eat", "egg", "elf", "end",
            "eye", "fan", "far", "fat", "fed", "fig", "fin", "fit", "fix", "fly",
            "fog", "fox", "fun", "fur", "gap", "gas", "gem", "get", "got", "gum",
            "had", "ham", "has", "hat", "hen", "hid", "him", "hip", "hit", "hop",
            "hot", "how", "hug", "hum", "hut", "ice", "ink", "jam", "jar", "jet",
            "jog", "joy", "jug", "key", "kid", "kit", "lab", "lap", "leg", "let",
            "lid", "lip", "lit", "log", "lot", "low", "mad", "man", "map", "mat",
            "men", "mix", "mom", "mop", "mud", "mug", "nap", "net", "new", "nod",
            "not", "now", "nut", "oak", "odd", "oil", "old", "owl", "pan", "pat",
            "pea", "peg", "pen", "pet", "pie", "pig", "pin", "pit", "pop", "pot",
            "pup", "put", "ram", "ran", "rat", "red", "rib", "rid", "rod", "row",
            "rub", "rug", "run", "sad", "sat", "saw", "sea", "see", "set", "sit",
            "six", "sky", "sun", "tag", "tan", "tap", "ten", "tie", "tin", "tip",
            "toe", "top", "toy", "tub", "tug", "two", "van", "vet", "wax", "web",
            "wet", "wig", "win", "yam", "yes", "yet", "zip", "zoo"});
}

bool WordDictionary::contains(const std::string& word) const {
    return words.count(word) > 0;  // count() is 1 if the word is in the set, else 0
}

std::string toLowerCase(const std::string& text) {
    std::string result = text;
    for (char& c : result) {  // "char&" = change the letter inside the string, not a copy
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

}  // namespace sa2026::problems::incomplete_code::wordladder
