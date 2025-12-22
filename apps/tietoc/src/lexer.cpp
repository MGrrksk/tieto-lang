#include <lexer.hpp>
#include <stdexcept>
#include <cstring>

void Lexer::configure(const char* source) {
    if (isTokenizing()) throw std::runtime_error("Lexer::configure(): Lexer is already configured. Call this method after tokenization is finished.");
    // Set all properties to starting values
    start = curr = src = source;
    line = column = 1;
}
Token Lexer::nextToken() {
    if (!isTokenizing()) throw std::runtime_error("Lexer::nextToken(): Lexer is not configured for tokenization. Call `configure(source)` method first.");
    // Move to the start of the next token
    skipWhitespace();
    start = curr;
    // Handle end of file
    if (isEOF()) {
        src = nullptr;
        return token(TT_EOF);
    }
    // Define token type based on the first character
    switch (next()) {
        case '(': return token(TT_LPAREN);
        case ')': return token(TT_RPAREN);
        case '[': return token(TT_LBRACK);
        case ']': return token(TT_RBRACK);
        case '{': return token(TT_LBRACE);
        case '}': return token(TT_RBRACE);
        case ',': return token(TT_COMMA);
        case '.':
            // If there is `.` in front of `.`, then it is `..` or `..=`.
            if (nextIs('.')) {
                // If there is `=` in front of `..`, then it is `..=`.
                if (nextIs('=')) return token(TT_DBLDOTEQ);
                else return token(TT_DBLDOT);
            } else return token(TT_DOT);
        case ';': return token(TT_SEMICOLON);
        case ':': return token(TT_COLON);
        case '?': return token(TT_QUESTION);
        case '+': return token(TT_PLUS);
        case '-': return token(TT_MINUS);
        case '*':
            // If there is `*` in front of `*`, then it is `**`.
            if (nextIs('*')) return token(TT_DBLSTAR);
            else return token(TT_STAR);
        case '/':
            // If there is `/` in front of `/`, then it is `//`.
            if (nextIs('/')) return token(TT_DBLSLASH);
            else return token(TT_SLASH);
        case '%': return token(TT_PERCENT);
        case '=':
            // If there is `=` in front of `=`, then it is `==`, and if there is `>` after it, it is `=>`.
            if (nextIs('=')) return token(TT_DBLEQUAL);
            else if (nextIs('>')) return token(TT_ARROW);
            else return token(TT_EQUAL);
        case '!':
            // If there is `=` in front of `!`, then it is `!=`, otherwise it is an error.
            if (nextIs('=')) return token(TT_NEQUAL);
            else return token(TT_ERRCHAR);
        case '>':
            // If there is `=` in front of `>`, then it is `>=`.
            if (nextIs('=')) return token(TT_GTEQUAL);
            else return token(TT_GREATER);
        case '<':
            // If there is `<` in front of `=`, then it is `<=`.
            if (nextIs('=')) return token(TT_LTEQUAL);
            else return token(TT_LESS);
        case '|':
            // If there is `>` in front of `|`, then it is `|>`, otherwise it is an error.
            if (nextIs('>')) return token(TT_STREAM);
            else return token(TT_ERRCHAR);
        case '"': {
            // Properties `line` and `column` are buffered to handle multi-line string literals.
            unsigned int tempLine = line, tempCol = column;
            while (!isEOF() && *curr != '"') {
                // Handling for multi-line string literals.
                if (*curr == '\n') {
                    line++;
                    column = 1;
                }
                next();
            }
            // If EOF was encountered before closing `"`, it is an error.
            if (isEOF()) return {TT_ERRSTR, start, static_cast<unsigned int>(curr - start), tempLine, tempCol};
            // Closing `"`.
            next();
            return {TT_STRING, start, static_cast<unsigned int>(curr - start), tempLine, tempCol};
        }
        case '\n': {
            // This is done so that token's `line` and `column` fields point to first line's end instead of second line's beginning.
            Token temp = token(TT_NEWLINE);
            line++;
            column = 1;
            return temp;
        }
        default:
            if (isalpha(*start) || *start == '_') {
                // Read whole token
                while (!isEOF() && (isalnum(*curr) || *curr == '_')) next();
                // Check if this is a keyword.
                // First the starting letter is checked, then length, and only then comparison is performed.
                switch (*start) {
                    case 'a': if (curr - start == 3 && memcmp(start + 1, "nd", 2) == 0) return token(TT_AND); break;
                    case 'c': if (curr - start == 5 && memcmp(start + 1, "onst", 4) == 0) return token(TT_CONST); break;
                    case 'e': if (curr - start == 4 && memcmp(start + 1, "lse", 3) == 0) return token(TT_ELSE); break;
                    case 'f':
                        if (curr - start == 5 && memcmp(start + 1, "alse", 4) == 0) return token(TT_FALSE);
                        if (curr - start == 2 && *(start + 1) == 'n') return token(TT_FN);
                        break;
                    case 'i': if (curr - start == 2 && *(start + 1) == 'f') return token(TT_IF); break;
                    case 'n':
                        if (curr - start == 3 && memcmp(start + 1, "ot", 2) == 0) return token(TT_NOT);
                        if (curr - start == 4 && memcmp(start + 1, "ull", 3) == 0) return token(TT_NULL);
                        break;
                    case 'o': if (curr - start == 2 && *(start + 1) == 'r') return token(TT_OR); break;
                    case 'r': if (curr - start == 6 && memcmp(start + 1, "eturn", 5) == 0) return token(TT_RETURN); break;
                    case 't': if (curr - start == 4 && memcmp(start + 1, "rue", 3) == 0) return token(TT_TRUE); break;
                    case 'v': if (curr - start == 3 && memcmp(start + 1, "ar", 2) == 0) return token(TT_VAR); break;
                    case 'w': if (curr - start == 5 && memcmp(start + 1, "hile", 4) == 0) return token(TT_WHILE); break;
                }
                // If no keyword matches, it is an identifier.
                return token(TT_ID);
            } else if (isdigit(*start)) {
                while (!isEOF() && isdigit(*curr)) next();
                // If after an integer literal there is a dot and another digit, then it is a float literal.
                if (*curr == '.' && isdigit(*(curr+1))) {
                    next();
                    while (!isEOF() && isdigit(*curr)) next();
                    return token(TT_FLOAT);
                } else return token(TT_INT);
            } else return token(TT_ERRCHAR); // If none ofthe patterns matches, character is unrecognized.
    }
}
bool Lexer::isTokenizing() {
    return src != nullptr;
}

void Lexer::skipWhitespace() {
    while (!isEOF()) {
        switch (*curr) {
            case ' ':
            case '\t':
                next(); break;
            case '\r':
                // `next()` would increment `column`, and CR does not count to line's length.
                curr++; break;
            case '#':
                // `#` starts a comment, newline ends it.
                while (!isEOF() && *curr != '\n') next();
                break;
            default: return;
        }
    }
}
char Lexer::next() {
    column++;
    return *curr++;
}
bool Lexer::nextIs(char c) {
    if (*curr == c) {
        next();
        return true;
    }
    return false;
}
Token Lexer::token(TokenType type) {
    return {type, start, static_cast<unsigned int>(curr - start), line, column - static_cast<unsigned int>(curr - start)};
}
bool Lexer::isEOF() {
    return *curr == '\0';
}