
#include "unicode_scripts.h"

typedef struct script_transliteration_rule {
    script_language_t script_language;
    transliterator_index_t index;
} script_transliteration_rule_t;

script_transliteration_rule_t script_transliteration_rules[] = {
    {{SCRIPT_THAANA, ""}, {0, 2}},
    {{SCRIPT_TELUGU, ""}, {2, 1}},
    {{SCRIPT_CYRILLIC, "be"}, {3, 1}},
    {{SCRIPT_CYRILLIC, "bg"}, {4, 1}},
    {{SCRIPT_CYRILLIC, "ru"}, {5, 1}},
    {{SCRIPT_CYRILLIC, ""}, {6, 1}},
    {{SCRIPT_CYRILLIC, "uz"}, {7, 1}},
    {{SCRIPT_CYRILLIC, "kk"}, {8, 1}},
    {{SCRIPT_CYRILLIC, "sr"}, {9, 1}},
    {{SCRIPT_CYRILLIC, "mn"}, {10, 1}},
    {{SCRIPT_CYRILLIC, "mk"}, {11, 1}},
    {{SCRIPT_CYRILLIC, "uk"}, {12, 1}},
    {{SCRIPT_CYRILLIC, "ky"}, {13, 1}},
    {{SCRIPT_HANGUL, ""}, {14, 1}},
    {{SCRIPT_HAN, ""}, {15, 1}},
    {{SCRIPT_ARMENIAN, ""}, {16, 1}},
    {{SCRIPT_TAMIL, ""}, {17, 1}},
    {{SCRIPT_MALAYALAM, ""}, {18, 1}},
    {{SCRIPT_GUJARATI, ""}, {19, 1}},
    {{SCRIPT_LATIN, ""}, {20, 1}},
    {{SCRIPT_LATIN, "nb"}, {21, 2}},
    {{SCRIPT_LATIN, "de"}, {23, 1}},
    {{SCRIPT_LATIN, "sv"}, {24, 2}},
    {{SCRIPT_LATIN, "da"}, {26, 2}},
    {{SCRIPT_LATIN, "et"}, {28, 1}},
    {{SCRIPT_GEORGIAN, ""}, {29, 2}},
    {{SCRIPT_DEVANAGARI, ""}, {31, 1}},
    {{SCRIPT_THAI, ""}, {32, 1}},
    {{SCRIPT_GREEK, ""}, {33, 3}},
    {{SCRIPT_KATAKANA, ""}, {36, 2}},
    {{SCRIPT_ORIYA, ""}, {38, 1}},
    {{SCRIPT_HIRAGANA, ""}, {39, 1}},
    {{SCRIPT_ARABIC, "fa"}, {40, 1}},
    {{SCRIPT_ARABIC, ""}, {41, 2}},
    {{SCRIPT_ARABIC, "ps"}, {43, 1}},
    {{SCRIPT_CANADIAN_ABORIGINAL, ""}, {44, 1}},
    {{SCRIPT_BENGALI, ""}, {45, 1}},
    {{SCRIPT_GURMUKHI, ""}, {46, 1}},
    {{SCRIPT_KANNADA, ""}, {47, 1}},
    {{SCRIPT_COMMON, ""}, {48, 1}},
    {{SCRIPT_COMMON, "nb"}, {49, 2}},
    {{SCRIPT_COMMON, "de"}, {51, 1}},
    {{SCRIPT_COMMON, "sv"}, {52, 2}},
    {{SCRIPT_COMMON, "da"}, {54, 2}},
    {{SCRIPT_COMMON, "et"}, {56, 1}},
    {{SCRIPT_HEBREW, ""}, {57, 2}}
};

char *script_transliterators[] = {
    "thaana-latin",
    "maldivian-latin-bgn",
    "telugu-latin",
    "belarusian-latin-bgn",
    "bulgarian-latin-bgn",
    "russian-latin-bgn",
    "cyrillic-latin",
    "uzbek-latin-bgn",
    "kazakh-latin-bgn",
    "serbian-latin-bgn",
    "mongolian-latin-bgn",
    "macedonian-latin-bgn",
    "ukrainian-latin-bgn",
    "kirghiz-latin-bgn",
    "hangul-latin",
    "han-latin",
    "armenian-latin-bgn",
    "tamil-latin",
    "malayalam-latin",
    "gujarati-latin",
    "latin-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "german-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "german-ascii",
    "georgian-latin",
    "georgian-latin-bgn",
    "devanagari-latin",
    "thai-latin",
    "greek-latin",
    "greek-latin-bgn",
    "greek-latin-ungegn",
    "katakana-latin",
    "katakana-latin-bgn",
    "oriya-latin",
    "hiragana-latin",
    "persian-latin-bgn",
    "arabic-latin",
    "arabic-latin-bgn",
    "pashto-latin-bgn",
    "canadianaboriginal-latin",
    "bengali-latin",
    "gurmukhi-latin",
    "kannada-latin",
    "latin-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "german-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "scandinavian-ascii",
    "latin-ascii",
    "german-ascii",
    "hebrew-latin",
    "hebrew-latin-bgn"
};

char *transliterator_replace_strings(trie_t *trie, cstring_array *replacements, char *input) {
    phrase_array *phrases;
    char_array *str;
    char *current = input;
    bool is_original = true;
    
    size_t len = strlen(input);

    // We may go through several rounds of replacements
    while (1) {
        phrases = trie_search(trie, current);
        if (!phrases) {
            break;
        } else {
            str = char_array_new_size(len);
            phrase_t phrase;
            size_t start = 0;
            size_t end = 0;
            for (size_t i = 0; i < phrases->n; i++) {
                phrase = phrases->a[i];
                end = phrase.start;
                char_array_append_len(str, input + start, end - start);
                char_array_append(str, cstring_array_get_string(replacements, phrase.data));
                start = phrase.start + phrase.len;
            }

            char_array_append_len(str, input + end, len - end);
            char_array_terminate(str);

            if (!is_original) {
                free(current);
            }

            // Destroys the char array itself, but not the string it holds
            current = char_array_to_string(str);
            is_original = false;
        }
    }

    return current;
}

