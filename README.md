# Palindrome & Emordnilap Checker

A lightweight, interactive C++ command-line application that analyzes words and phrases for palindromic and emordnilap properties. 

Beyond standard palindrome detection (words or phrases that read the same forward and backward), this tool checks for **emordnilaps**—words that spell a *different* valid word when reversed (e.g., `stressed` $\leftrightarrow$ `desserts`, `live` $\leftrightarrow$ `evil`).

---

## Features

- **Palindrome Analysis:** Cleans input (strips spaces, punctuation, and casing) and determines if a word or phrase reads the same backward.
- **Emordnilap Detection:** Checks single words against a dictionary to verify if their reverse is also a valid word.
- **Dynamic Dictionary Support:**
  - Loads custom word lists passed as command-line arguments.
  - Automatically falls back to system dictionary files (e.g., `/usr/share/dict/words` or `/usr/dict/words`).
  - Includes a built-in fallback word list for zero-dependency execution on any system.
- **Batch Processing:** Evaluate multiple words at once via comma-separated inputs.
- **Interactive CLI & Examples:** Easy-to-use menu with educational definitions and built-in famous examples.

---

## Terms Defined

| Term | Definition | Example |
| :--- | :--- | :--- |
| **Palindrome** | A word, phrase, or sequence that reads the same forward and backward. | `racecar`, `A man a plan a canal Panama` |
| **Emordnilap** | A word whose reverse spelling forms a *different* valid word. | `dog` $\leftrightarrow$ `god`, `drawer` $\leftrightarrow$ `reward` |

---

## Build and Run

### Prerequisites

- A C++ compiler supporting C++11 or later (`g++`, `clang++`, or MSVC).

### Compilation

Compile the program using standard GCC/Clang options:

```bash
g++ -std=c++11 -O2 main.cpp -o checker
```

### Usage

1. **Default Run (System/Built-in Dictionary):**
   ```bash
   ./checker
   ```

2. **Custom Dictionary Run:**
   Pass a custom plain-text word list (one word per line) as an argument:
   ```bash
   ./checker /path/to/wordlist.txt
   ```

---

## Interactive Menu Options

When launched, the program presents an interactive CLI menu:

- **`[1]` Check a single word / phrase:** Analyze standard inputs or long phrases.
- **`[2]` Check multiple words at once:** Provide a comma-separated list (e.g., `dog, live, racecar, hello`).
- **`[3]` View famous examples:** Displays classic palindromes and emordnilap pairs.
- **`[4]` About palindromes & emordnilaps:** Educational breakdown of concepts.
- **`[0]` Quit:** Exit the application.

---

## License

This project is open-source and available under the [MIT License](LICENSE).