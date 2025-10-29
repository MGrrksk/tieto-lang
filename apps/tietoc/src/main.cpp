#include <lexer.hpp>
#include <common/utils.hpp>
#include <cstdio>

int main() {
	// Load file's content
	// TODO: take path from CLI args
	char* source = readFile("test.tiet");

	// Configure tools
	Lexer lexer{};
	lexer.configure(source);

	// Tokenize file
	Token token;
	do {
		token = lexer.nextToken();
		printf("%i (%i:%i) `%.*s`%i\n", token.type, token.line, token.column, token.length, token.lexeme, token.length);
	} while (token.type != TT_EOF);

	// Free memory
	delete[] source;
	return 0;
}