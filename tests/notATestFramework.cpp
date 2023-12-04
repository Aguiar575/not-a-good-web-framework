#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

std::unordered_map<std::string, std::string> headerImplementationMap;

void processCppFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    std::string line;
    
    while (std::getline(file, line)) {
        // Extract #include paths
        std::smatch match;
        if (std::regex_search(line, match, std::regex("#include\\s+\"(.+)\""))){
            std::string includedHeader = match[1];
            std::string implementationPath = includedHeader;
            // Replace .h with .cpp for implementation file
            implementationPath.replace(implementationPath.find(".h"), 2, ".cpp");

            headerImplementationMap[includedHeader] = implementationPath;
        }
    }
}

int main() {
    const std::filesystem::path currentPath = std::filesystem::current_path();
    const std::filesystem::path testFolder = currentPath / "http";
    
    for (const auto& entry : std::filesystem::directory_iterator(testFolder)) {
        if (entry.path().extension() == ".cpp") {
            std::cout << "Processing: " << entry.path().filename() << std::endl;
            processCppFile(entry.path());
        }
    }

    for (const auto& pair : headerImplementationMap) {
        std::cout << "Header: " << pair.first << " -> Implementation: " << pair.second << std::endl;
    }

    return 0;
}

