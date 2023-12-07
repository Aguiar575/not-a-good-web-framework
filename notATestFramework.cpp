#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <string>

std::list<std::string> testFileDependencies;
std::list<std::filesystem::path> testFiles;

const std::string compiler = "g++ -std=c++17 ";
const std::filesystem::path projectPath = std::filesystem::current_path();

std::filesystem::path findFile(const std::filesystem::path &basePath,
                               const std::string &fileName) {
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(basePath)) {
    if (entry.is_regular_file() && entry.path().filename() == fileName) {
      return entry.path();
    }
  }

  return std::filesystem::path();
}

void addFileToImplementationMap(std::filesystem::path &targetFile,
                                const std::string &fileExtension,
                                const std::filesystem::path &testFile) {

  targetFile.replace_extension(fileExtension);
  std::filesystem::path targetFilePathCpp =
      findFile(projectPath, targetFile.filename());

  if (!targetFilePathCpp.empty()) {
    testFileDependencies.emplace_back(targetFilePathCpp.string());
  }
}

void processCppFile(const std::filesystem::path &filePath,
                    const std::filesystem::path &projectPath) {
  std::ifstream file(filePath);
  std::string line;

  while (std::getline(file, line)) {
    // Extract #include paths
    std::smatch match;
    if (std::regex_search(line, match, std::regex("#include\\s+\"(.+)\""))) {
      std::string includedHeader = match[1];

      std::filesystem::path targetFile = includedHeader;
      targetFile = std::filesystem::weakly_canonical(targetFile);

      addFileToImplementationMap(targetFile, ".cpp", filePath);
    }
  }
}

std::string pushFilesToCommmand() {
    std::string testCommand;

    for(const auto &testFile : testFiles) {
        testCommand += testFile.string() + " ";
    }

    for (const auto &dependencie : testFileDependencies) {
        testCommand += dependencie + " ";
    }

    testCommand.insert(0, compiler);
    testCommand += "-o testExecutable";

    return testCommand;
}


int main() {
  const std::filesystem::path testFolder = projectPath / "tests" / "http";

  for (const auto &entry : std::filesystem::directory_iterator(testFolder)) {
    if (entry.path().extension() == ".cpp") {
      testFiles.emplace_back(entry.path());
    }
  }

  for (const auto &testFile : testFiles) {
    processCppFile(testFile, projectPath);
  }

  std::cout << pushFilesToCommmand() << std::endl;

  return 0;
}
