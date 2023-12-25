#include <string>
#include <unordered_map>

class PathStructure {
public:
  std::unordered_map<char, PathStructure *> children;
  bool isEndOfWord;
  std::vector<std::pair<std::string, std::string>> params;
  std::string status;

  PathStructure() : isEndOfWord(false) {}

  // Custom hash function for PathStructure
  size_t operator()(const PathStructure &path) const {
    return std::hash<bool>()(path.isEndOfWord) ^
           (std::hash<size_t>()(path.params.size()) << 1);
  }

  bool operator==(const PathStructure &other) const {
    return (isEndOfWord == other.isEndOfWord) && (params == other.params);
  }
};
