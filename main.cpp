#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>
#include <sstream>

using namespace std;

// ---------- helpers ----------

// Keep letters and digits, lowercase everything.
string normalize(const string& s) {
    string out;
    for (char c : s)
        if (isalnum(static_cast<unsigned char>(c)))
            out += static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return out;
}

string reversed(const string& s) {
    return string(s.rbegin(), s.rend());
}

// Trim spaces, tabs, \r and \n from both ends.
string trim(const string& s) {
    const char* ws = " \t\r\n";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

bool hasWhitespace(const string& s) {
    return any_of(s.begin(), s.end(),
                  [](char c) { return isspace(static_cast<unsigned char>(c)); });
}

// Read one line from stdin. Returns false on EOF/error.
bool readLine(string& line) {
    return static_cast<bool>(getline(cin, line));
}

// ---------- dictionary ----------

set<string> dictionary;
bool dictionaryFromFile = false;

void loadBuiltinWords() {
    const char* words[] = {
        "dog", "god", "live", "evil", "stressed", "desserts", "parts", "strap",
        "repaid", "diaper", "stab", "bats", "drawer", "reward", "deliver",
        "reviled", "loop", "pool", "stop", "pots", "smart", "trams", "star",
        "rats", "tub", "but", "nap", "pan", "war", "raw", "tops", "spot",
        "regal", "lager", "flow", "wolf", "keep", "peek", "time", "emit",
        "racecar", "level", "madam", "civic", "radar", "rotor", "kayak",
        "refer", "noon"
    };
    for (const char* w : words) dictionary.insert(w);
}

bool loadDictionaryFile(const string& path) {
    ifstream in(path);
    if (!in) return false;
    string word;
    while (getline(in, word)) {
        word = trim(word);
        // Only accept pure-alphabetic entries (skips "don't", "Zürich", etc.)
        if (word.empty() ||
            !all_of(word.begin(), word.end(),
                    [](char c) { return isalpha(static_cast<unsigned char>(c)); }))
            continue;
        transform(word.begin(), word.end(), word.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        dictionary.insert(word);
    }
    return !dictionary.empty();
}

void initDictionary(int argc, char* argv[]) {
    if (argc > 1 && loadDictionaryFile(argv[1])) {
        dictionaryFromFile = true;
        return;
    }
    if (argc > 1)
        cerr << "[!] Could not read dictionary \"" << argv[1]
             << "\". Trying system dictionary.\n";

    if (loadDictionaryFile("/usr/share/dict/words") ||
        loadDictionaryFile("/usr/dict/words")) {
        dictionaryFromFile = true;
        return;
    }
    loadBuiltinWords();
}

// ---------- output ----------

void printBanner() {
    cout << "\n"
         << "===============================\n"
         << "Palindrome & Emordnilap Checker\n"
         << "===============================\n";
    if (dictionaryFromFile)
        cout << "(dictionary loaded: " << dictionary.size() << " words)\n";
    else
        cout << "(no dictionary file found: using a small built-in word list;\n"
             << " pass a word-list path as an argument for better results)\n";
    cout << "\n";
}

void printDivider() {
    cout << "--------------------------------------------------------\n";
}

void printResult(const string& input) {
    string norm = normalize(input);

    if (norm.empty()) {
        cout << "[!] Input contains no letters or digits.\n";
        return;
    }

    string rev = reversed(norm);
    bool palind = (norm == rev);

    cout << "\nInput   : \"" << input << "\"\n";
    cout << "Cleaned : \"" << norm << "\"\n";
    cout << "Reversed: \"" << rev << "\"\n";
    printDivider();

    if (palind) {
        cout << "PALINDROME\n";
        cout << "Reads the same forwards and backwards.\n";
    } else {
        cout << "Not a palindrome.\n";

        // Emordnilaps apply to single words only.
        if (hasWhitespace(input)) {
            cout << "(Emordnilap check skipped: it applies to single words.)\n";
        } else if (dictionary.count(norm) && dictionary.count(rev)) {
            cout << "\nEMORDNILAP!\n";
            cout << "\"" << norm << "\"  <>  \"" << rev << "\"\n";
            cout << "Both are valid words.\n";
        } else if (dictionary.count(rev)) {
            cout << "\nEMORDNILAP (reverse is a word, but \"" << norm
                 << "\" wasn't found in the dictionary).\n";
        } else {
            cout << "Not an emordnilap: \"" << rev
                 << "\" is not in the dictionary.\n";
        }
    }
    cout << "\n";
}

void showMenu() {
    cout << "Choose an option:\n"
         << "[1] Check a single word / phrase\n"
         << "[2] Check multiple words at once\n"
         << "[3] View famous examples\n"
         << "[4] About palindromes & emordnilaps\n"
         << "[0] Quit\n"
         << "\n> ";
}

// ---------- actions ----------

void checkSingle() {
    cout << "Enter word or phrase: ";
    string line;
    if (!readLine(line)) return;
    printResult(trim(line));
}

void checkMultiple() {
    cout << "\nEnter words separated by commas: ";
    string line;
    if (!readLine(line)) return;

    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        token = trim(token);
        if (token.empty()) continue;
        printDivider();
        printResult(token);
    }
}

void showExamples() {
    cout << "\n";
    printDivider();
    cout << "Famous Palindromes:\n"
         << "racecar\n"
         << "level\n"
         << "madam\n"
         << "civic\n"
         << "radar\n"
         << "rotor\n"
         << "kayak\n"
         << "refer\n"
         << "noon\n"
         << "A man a plan a canal Panama\n"
         << "Was it a car or a cat I saw\n\n";

    cout << "Famous Emordnilap Pairs:\n"
         << "dog      <>  god\n"
         << "live     <>  evil\n"
         << "stressed <>  desserts\n"
         << "parts    <>  strap\n"
         << "repaid   <>  diaper\n"
         << "stab     <>  bats\n"
         << "drawer   <>  reward\n"
         << "deliver  <>  reviled\n"
         << "loop     <>  pool\n"
         << "stop     <>  pots\n"
         << "smart    <>  trams\n";
    printDivider();
    cout << "\n";
}

void showAbout() {
    cout << "\n";
    printDivider();
    cout << "PALINDROME\n"
         << "A word, phrase, or sequence that reads the same\n"
         << "forwards and backwards (ignoring spaces/punctuation).\n"
         << "Example: \"racecar\"\n\n"

         << "EMORDNILAP  (\"palindromes\" spelled backwards!)\n"
         << "A word whose reverse spelling forms a *different*\n"
         << "valid word. Unlike palindromes, the two words have\n"
         << "distinct meanings.\n"
         << "Example: \"dog\" reversed is \"god\".\n\n"

         << "KEY DIFFERENCE\n"
         << "Palindrome : word == reverse(word)\n"
         << "Emordnilap : word != reverse(word), but reverse\n"
         << "is also a legitimate word.\n";
    printDivider();
    cout << "\n";
}

// ---------- main ----------

int main(int argc, char* argv[]) {
    initDictionary(argc, argv);
    printBanner();

    while (true) {
        showMenu();

        string line;
        if (!readLine(line)) {  // EOF: exit cleanly instead of looping forever
            cout << "\nGoodbye!\n\n";
            break;
        }

        // Parse the whole line as a single integer.
        string t = trim(line);
        int choice = -1;
        if (t.size() == 1 && isdigit(static_cast<unsigned char>(t[0])))
            choice = t[0] - '0';

        cout << "\n";

        if (choice == 0) {
            cout << "Goodbye!\n\n";
            break;
        }

        switch (choice) {
            case 1: checkSingle();   break;
            case 2: checkMultiple(); break;
            case 3: showExamples();  break;
            case 4: showAbout();     break;
            default:
                cout << "[!] Invalid option. Please enter 0-4.\n\n";
        }
    }

    return 0;
}