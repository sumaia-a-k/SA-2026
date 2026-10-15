package sa2026.problems.incomplete_code.wordladder;

import java.util.HashSet;
import java.util.Set;

/**
 * The list of allowed words. Every word in the ladder must be in the dictionary.
 *
 * We use a HashSet, so contains() is fast (it does not check the words one by one).
 */
public class WordDictionary {

    private final Set<String> words = new HashSet<>();

    public WordDictionary(String... words) {
        for (String word : words) {
            this.words.add(word.toLowerCase());
        }
    }

    // a small dictionary of 3-letter words, good for class examples
    public static WordDictionary threeLetterWords() {
        return new WordDictionary(
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
                "wet", "wig", "win", "yam", "yes", "yet", "zip", "zoo");
    }

    public boolean contains(String word) {
        return words.contains(word);
    }
}
