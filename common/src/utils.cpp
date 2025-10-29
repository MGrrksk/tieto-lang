#include <common/utils.hpp>
#include <fstream>

char* readFile(const char* path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("readFile(): Failed to open a file");

    file.seekg(0, std::ios::end);
    unsigned int length = static_cast<unsigned int>(file.tellg());
    file.seekg(0, std::ios::beg);

    char* content = new char[length + 1];
    file.read(content, length);
    content[length] = '\0';

    file.close();
    return content;
}