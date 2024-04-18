#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to calculate hash value for a string
int calculate_hash(const string& s) {
    int hash = 0;
    for (char c : s) {
        if (c != ' ') {
            hash += c;
        }
    }
    return hash;
}

// Function to remove newline characters from a string
void remove_newlines(string& s) {
    string result;
    for (char c : s) {
        if (c != '\n') {
            result += c;
        }
    }
    s = result;
}

// Function to implement Rabin-Karp algorithm
void rabin_karp(const string& text, const string& pattern) {
    if (text.empty() || pattern.empty()) {
        cout << "Error: Text or pattern is empty." << endl;
        return;
    }

    string text_without_spaces, pattern_without_spaces;
    for (char c : text) {
        if (c != ' ') {
            text_without_spaces += c;
        }
    }
    for (char c : pattern) {
        if (c != ' ') {
            pattern_without_spaces += c;
        }
    }

    int text_len = text_without_spaces.length();
    int pattern_len = pattern_without_spaces.length();

    if (pattern_len > text_len) {
        cout << "Pattern length is greater than text length." << endl;
        return;
    }

    int pattern_hash = calculate_hash(pattern_without_spaces);
    int text_hash = calculate_hash(text_without_spaces.substr(0, pattern_len));

    bool pattern_found = false;

    for (int i = 0; i <= text_len - pattern_len; i++) {
        if (text_hash == pattern_hash) {
            // If hash matches, check character by character
            if (text_without_spaces.substr(i, pattern_len) == pattern_without_spaces) {
                cout << "Pattern found at index: " << i << endl;
                pattern_found = true;
            }
        }
        // Calculate hash for the next window of text
        if (i < text_len - pattern_len) {
            text_hash = text_hash - text_without_spaces[i] + text_without_spaces[i + pattern_len];
        }
    }

    if (!pattern_found) {
        cout << "Pattern \"" << pattern << "\" does not exist in the given text." << endl;
    }
}

int main() {
    string text_file_name = "sampletext.txt";
    string pattern_file_name = "sample_pattern.txt";

    // Read text from file
    ifstream text_file(text_file_name);
    if (!text_file.is_open()) {
        cout << "Error: Text file not found." << endl;
        return 1;
    }
    string text;
    getline(text_file, text);
    remove_newlines(text);

    // Read pattern from file
    ifstream pattern_file(pattern_file_name);
    if (!pattern_file.is_open()) {
        cout << "Error: Pattern file not found." << endl;
        return 1;
    }
    string pattern;
    getline(pattern_file, pattern);
    remove_newlines(pattern);

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "Indices where pattern occurs:" << endl;
    rabin_karp(text, pattern);

    return 0;
}
