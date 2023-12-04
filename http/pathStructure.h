#include <unordered_map>
#include <string>

class PathStructure {
public:
  std::unordered_map<char, PathStructure *> children; // Children nodes
  bool isEndOfWord; // Flag to mark the end of a word (path)
  std::vector<std::pair<std::string, std::string>>
      params; // Store parameters at each node

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
