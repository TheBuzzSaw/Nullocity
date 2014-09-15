#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <vector>

namespace SDL2TK
{
    template<typename T> constexpr T Convert(const void* block)
    {
        return *reinterpret_cast<const T*>(block);
    }

    std::string FileToString(const char* path);
    std::vector<char> GetFileContent(const char* path);
}

#endif
