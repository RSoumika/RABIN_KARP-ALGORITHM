def rabin_karp(text, pattern, prime):
    pattern_len = len(pattern)
    text_len = len(text)
    pattern_hash = 0
    text_hash = 0
    h = 1

    # Calculate h = ALPHABET_SIZE^(pattern_len-1) % prime
    for _ in range(pattern_len - 1):
        h = (h * ALPHABET_SIZE) % prime

    # Calculate initial hash values for pattern and first window of text
    for i in range(pattern_len):
        pattern_hash = (ALPHABET_SIZE * pattern_hash + ord(pattern[i])) % prime
        text_hash = (ALPHABET_SIZE * text_hash + ord(text[i])) % prime

    for i in range(text_len - pattern_len + 1):
        if pattern_hash == text_hash:
            # If hash matches, check character by character
            if text[i:i+pattern_len] == pattern:
                print(f"Pattern found at index: {i}")

        # Calculate hash for the next window of text
        if i < text_len - pattern_len:
            text_hash = (ALPHABET_SIZE * (text_hash - ord(text[i]) * h) + ord(text[i + pattern_len])) % prime

            # Handle negative hash values
            if text_hash < 0:
                text_hash = (text_hash + prime)

ALPHABET_SIZE = 256
prime = 101  # Prime number for hashing

# Read text from file
try:
    with open("sampletext.txt", "r") as file:
        text = file.read().strip()
except FileNotFoundError:
    print("Error: Text file not found.")
    exit(1)

# Read pattern from file
try:
    with open("sample_pattern.txt", "r") as file:
        pattern = file.read().strip()
except FileNotFoundError:
    print("Error: Pattern file not found.")
    exit(1)

print("Text:", text)
print("Pattern:", pattern)
print("Indices where pattern occurs:")
rabin_karp(text, pattern, prime)
