#include <algorithm>
#include <array>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>

const std::string compiler = "g++ -std=c++17 ";
const std::filesystem::path projectPath = std::filesystem::current_path();
const std::filesystem::path testFolder = projectPath / "tests" / "http";
const std::filesystem::path buildTestFolder = projectPath / "build" / "tests";

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

std::string mapTestDependencies(std::filesystem::path &targetFile,
                                const std::string &fileExtension,
                                const std::filesystem::path &testFile) {

  targetFile.replace_extension(fileExtension);
  std::filesystem::path targetFilePathCpp =
      findFile(projectPath, targetFile.filename());

  return targetFilePathCpp.string();
}

std::list<std::string>
getTestDependencies(const std::filesystem::path &filePath,
                    const std::filesystem::path &projectPath) {

  std::list<std::string> testFileDependencies;
  std::ifstream file(filePath);
  std::string line;

  while (std::getline(file, line)) {
    // Extract #include paths
    std::smatch match;
    if (std::regex_search(line, match, std::regex("#include\\s+\"(.+)\""))) {
      std::string includedHeader = match[1];

      std::filesystem::path targetFile = includedHeader;
      targetFile = std::filesystem::weakly_canonical(targetFile);

      testFileDependencies.emplace_back(
          mapTestDependencies(targetFile, ".cpp", filePath));
    }
  }

  return testFileDependencies;
}

std::string
generateCompilationCommmand(const std::filesystem::path &testFileName,
                            std::list<std::string> &testFileDependencies) {
  std::string compileCommand = testFileName;

  for (const auto &dependencie : testFileDependencies) {
    compileCommand += dependencie + " ";
  }

  compileCommand.insert(0, compiler);
  compileCommand += "-o " + buildTestFolder.string() + "/" + testFileName.filename().string();

  return compileCommand;
}

std::string executeCommandAndGetOutput(const std::filesystem::path &command) {
  std::array<char, 128> buffer;
  std::stringstream result;

  // Use popen to execute the command and capture the output
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    std::cerr << "Error executing command: " << command << std::endl;
    return "";
  }

  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    result << buffer.data();
  }

  pclose(pipe);

  return command.filename().string() + ": " + result.str();
}

void executeTestsInDirectory(const std::string &directoryPath) {
  for (const auto &entry : std::filesystem::directory_iterator(directoryPath)) {
    if (entry.is_regular_file()) {
      std::filesystem::path executablePath = entry.path();
      std::cout << executeCommandAndGetOutput(executablePath);
    }
  }
}

int main() {
  std::filesystem::create_directories(buildTestFolder);

  for (const auto &entry : std::filesystem::directory_iterator(testFolder)) {
    if (entry.path().extension() == ".cpp") {
      std::list<std::string> dependencies =
          getTestDependencies(entry.path(), projectPath);

      std::string command =
          generateCompilationCommmand(entry.path(), dependencies);

      int compileResult = std::system(command.c_str());
      if (compileResult != 0) {
        std::cerr << "Compilation failed." << std::endl;
      }
    }
  }

  executeTestsInDirectory(buildTestFolder);

  return 0;
}
