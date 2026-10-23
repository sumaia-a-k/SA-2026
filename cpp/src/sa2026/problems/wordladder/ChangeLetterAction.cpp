#include "sa2026/problems/wordladder/ChangeLetterAction.h"

#include <memory>

#include "sa2026/problems/wordladder/WordLadderState.h"

namespace sa2026::problems::wordladder {

ChangeLetterAction::ChangeLetterAction(const WordDictionary& dictionary) : dictionary(dictionary) {}

std::vector<core::StatePtr> ChangeLetterAction::apply(const core::StatePtr& s) const {
    std::string word = dynamic_cast<const WordLadderState&>(*s).getWord();
    std::vector<core::StatePtr> nextStates;

    // try every position, and every letter from 'a' to 'z' in that position
    for (std::size_t i = 0; i < word.size(); i++) {
        for (char letter = 'a'; letter <= 'z'; letter++) {
            if (letter == word[i]) {
                continue;  // same letter, not a change
            }
            // In C++ a string can be changed (in Java it can not),
            // so we copy the word and change one letter of the copy.
            std::string newWord = word;
            newWord[i] = letter;
            if (dictionary.contains(newWord)) {
                nextStates.push_back(std::make_shared<WordLadderState>(newWord));
            }
        }
    }
    return nextStates;
}

std::string ChangeLetterAction::getName() const {
    return "Change one letter";
}

}  // namespace sa2026::problems::wordladder
