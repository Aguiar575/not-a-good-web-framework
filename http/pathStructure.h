#include <string>
#include <unordered_map>
#include <utility>

class PathStructure {
public:
  std::unordered_map<char, PathStructure *> children;
  bool isEndOfWord;
  std::vector<std::pair<std::string, std::string>> params;
  std::pair<std::string, std::string> status;

  PathStructure() : isEndOfWord(false) {}

  ~PathStructure() {
      for (auto &child : children) {
          delete child.second;
      }
  }
  // Custom hash function for PathStructure
  size_t operator()(const PathStructure &path) const {
    return std::hash<bool>()(path.isEndOfWord) ^
           (std::hash<size_t>()(path.params.size()) << 1);
  }

  bool operator==(const PathStructure &other) const {
    return (isEndOfWord == other.isEndOfWord) && (params == other.params);
  }


  void clean() {
    children.clear();
    isEndOfWord = false;
    params.clear();
    status = std::make_pair("", "");
  }
};
