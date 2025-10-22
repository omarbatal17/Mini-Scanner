#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
using namespace std;

unordered_set<string> keywords = {
    "int", "if", "else", "return", "float", "double", "while", "for", "main"
};

bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' ||
           c == '=' || c == '<' || c == '>' || c == '!';
}

int main() {
    string code = R"(int main() {
    int x,y;
    // This is a single-line comment
    if (x == 42) {
        /* This is
           a block
           comment */
        x = x-3;
    } else {
        y = 3.1; // Another comment
    }
    return 0;
})";

    for (size_t i = 0; i < code.size();) {
        char c = code[i];

        // Skip whitespace
        if (isspace(c)) { i++; continue; }

        // Comments
        if (c == '/') {
            if (i + 1 < code.size() && code[i + 1] == '/') {
                string comment;
                i += 2;
                while (i < code.size() && code[i] != '\n') comment += code[i++];
                cout << "<COMMENT, //" << comment << ">" << endl;
                continue;
            }
            if (i + 1 < code.size() && code[i + 1] == '*') {
                string comment;
                i += 2;
                while (i + 1 < code.size() && !(code[i] == '*' && code[i + 1] == '/'))
                    comment += code[i++];
                i += 2;
                cout << "<COMMENT, /*" << comment << "*/>" << endl;
                continue;
            }
        }

        // Identifiers / Keywords
        if (isalpha(c) || c == '_') {
            string word;
            while (i < code.size() && (isalnum(code[i]) || code[i] == '_'))
                word += code[i++];
            if (keywords.count(word))
                cout << "<KEYWORD, " << word << ">" << endl;
            else
                cout << "<IDENTIFIER, " << word << ">" << endl;
            continue;
        }

        // Numbers
        if (isdigit(c)) {
            string number;
            while (i < code.size() && (isdigit(code[i]) || code[i] == '.'))
                number += code[i++];
            cout << "<NUMBER, " << number << ">" << endl;
            continue;
        }

        // Operators
        if (isOperatorChar(c)) {
            string op;
            op += c;
            if (i + 1 < code.size() && code[i + 1] == '=') { op += '='; i++; }
            cout << "<OPERATOR, " << op << ">" << endl;
            i++;
            continue;
        }

        // Symbols (punctuation)
        if (ispunct(c)) {
            cout << "<SPECIAL CHARACTER, " << c << ">" << endl;
            i++;
            continue;
        }

        i++; // fallback
    }

    return 0;
}
