#include <lexer.hpp>
#include <parser.hpp>
#include <ast-viewer.hpp>
#include <common/utils.hpp>
#include <cstdio>

int main() {
	// Load file's content
	// TODO: take path from CLI args
	char* source = readFile("test.tiet");

	// Configure tools
	Lexer lexer{};
	lexer.configure(source);
	PoolAllocator pool{};
	Parser parser(&lexer, &pool);

	// Parse code
	Expr* expr = parser.parse();
	ASTViewer viewer;
	expr->accept(&viewer);

	// Free memory
	delete[] source;
	return 0;
}