#include <unordered_map>

class PathStructure {
public:
  std::unordered_map<char, PathStructure *> children; // Children nodes
  bool isEndOfWord; // Flag to mark the end of a word (path)
  std::vector<std::pair<std::string, std::string>>
      params; // Store parameters at each node

  PathStructure() : isEndOfWord(false) {}
};
