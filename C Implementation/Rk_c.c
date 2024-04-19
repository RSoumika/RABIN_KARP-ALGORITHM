#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 // Maximum length of input strings

// Function to calculate hash value for a substring
int calculateHash(char *str, int start, int end) {
    int hash = 0;
    for (int i = start; i <= end; i++) {
        hash += str[i];
    }
    return hash;
}

// Function to implement Rabin-Karp algorithm
void rabinKarp(char *text, char *pattern) {
    if (text[0] == '\0' || pattern[0] == '\0') {
        printf("Error: Text or pattern is empty.\n");
        return;
    }

    int textLen = strlen(text);
    int patternLen = strlen(pattern);

    if (patternLen > textLen) {
        printf("Pattern length is greater than text length.\n");
        return;
    }

    int patternHash = calculateHash(pattern, 0, patternLen - 1);
    int textHash = calculateHash(text, 0, patternLen - 1);

    int patternFound = 0;

    for (int i = 0; i <= textLen - patternLen; i++) {
        if (textHash == patternHash) {
            // If hash matches, check character by character
            int j;
            for (j = 0; j < patternLen; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == patternLen) {
                printf("Pattern found at index: %d\n", i);
                patternFound = 1;
            }
        }
        // Calculate hash for the next window of text
        if (i < textLen - patternLen) {
            textHash = textHash - text[i] + text[i + patternLen];
        }
    }

    if (!patternFound) {
        printf("Pattern \"%s\" does not exist in the given text.\n", pattern);
    }
}

int main() {
    char text[MAX_LEN];
    char pattern[MAX_LEN];

    printf("Enter the text: ");
    fgets(text, MAX_LEN, stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character

    printf("Enter the pattern to search: ");
    fgets(pattern, MAX_LEN, stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove the newline character

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    printf("Indices where pattern occurs:\n");
    rabinKarp(text, pattern);

    return 0;
}
