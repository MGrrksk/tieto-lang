#pragma once

// This function returns entire content of a file under the given path.
// It allocates memory, therefore manual freeing of returned data is required.
char* readFile(const char* path);