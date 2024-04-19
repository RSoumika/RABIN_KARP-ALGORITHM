#include <stdio.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256

// Rabin-Karp algorithm implementation
void rabin_karp(const char *text, const char *pattern, int prime) {
    int pattern_len = strlen(pattern);
    int text_len = strlen(text);
    int pattern_hash = 0;
    int text_hash = 0;
    int h = 1;
    int i, j;
    int pattern_found = 0; // Flag to track if pattern is found

    // Calculate h = ALPHABET_SIZE^(pattern_len - 1) % prime
    for (i = 0; i < pattern_len - 1; i++)
        h = (h * ALPHABET_SIZE) % prime;

    // Calculate initial hash values for pattern and first window of text
    for (i = 0; i < pattern_len; i++) {
        pattern_hash = (ALPHABET_SIZE * pattern_hash + pattern[i]) % prime;
        text_hash = (ALPHABET_SIZE * text_hash + text[i]) % prime;
    }

    // Search for the pattern in the text
    for (i = 0; i <= text_len - pattern_len; i++) {
        if (pattern_hash == text_hash) {
            // If hash matches, check character by character
            for (j = 0; j < pattern_len; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == pattern_len) {
                printf("Pattern found at index: %d\n", i);
                pattern_found = 1; // Set flag to true if pattern is found
            }
        }

        // Calculate hash for the next window of text
        if (i < text_len - pattern_len) {
            text_hash = (ALPHABET_SIZE * (text_hash - text[i] * h) + text[i + pattern_len]) % prime;

            // Handle negative hash values
            if (text_hash < 0) {
                text_hash += prime;
            }
        }
    }

    // If the pattern was not found, print a message
    if (!pattern_found) {
        printf("Pattern not found in the text\n");
    }
}

int main() {
    char text[1000];
    char pattern[1000];
    int prime = INT_MAX; // Prime number for hashing
    FILE *text_file, *pattern_file;

    // Read text from file
    text_file = fopen("sampletext.txt", "r");
    if (!text_file) {
        printf("Error: Text file not found.\n");
        return 1;
    }
    if (fgets(text, sizeof(text), text_file) == NULL) {
        printf("Error: Text file is empty or could not be read.\n");
        fclose(text_file);
        return 1;
    }
    fclose(text_file);
    // Remove newline character from the end of the text
    text[strcspn(text, "\n")] = '\0'; 

    // Read pattern from file
    pattern_file = fopen("sample_pattern.txt", "r");
    if (!pattern_file) {
        printf("Error: Pattern file not found.\n");
        return 1;
    }
    if (fgets(pattern, sizeof(pattern), pattern_file) == NULL) {
        printf("Error: Pattern file is empty or could not be read.\n");
        fclose(pattern_file);
        return 1;
    }
    fclose(pattern_file);
    // Remove newline character from the end of the pattern
    pattern[strcspn(pattern, "\n")] = '\0';

    // Check if the text and pattern files were empty
    if (strlen(text) == 0) {
        printf("Text file is empty.\n");
        return 1;
    }

    if (strlen(pattern) == 0) {
        printf("Pattern file is empty.\n");
        return 1;
    }

    printf("Searching for the pattern in the text...\n");
    // Search for the pattern in the text using the Rabin-Karp algorithm
    rabin_karp(text, pattern, prime);

    return 0;
}
