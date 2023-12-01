#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "pathStructure.h"

class Trie {
public:
  Trie() { root = new PathStructure(); }

  void insert(const std::string &path) {
    PathStructure *node = root;
    std::istringstream iss(path);
    std::string token;

    while (std::getline(iss, token, '/')) {
      if (token.empty())
        continue;

      if (token[0] == '{' && token.back() == '}') {
        // Dynamic parameter, e.g., "/user/{name:string}" or "/user/{id:int}"
        size_t colonPos = token.find(':');
        if (colonPos != std::string::npos) {
          // Extract parameter name and type
          node->params.push_back(
              {token.substr(1, colonPos - 1),
               token.substr(colonPos + 1, token.length() - colonPos - 2)});
        } else {
          // Only parameter name specified without type
          node->params.push_back({token.substr(1, token.length() - 2), ""});
        }
      } else {
        // Static segment, create a new node if not exists
        if (node->children.find(token[0]) == node->children.end()) {
          node->children[token[0]] = new PathStructure();
        }
        node = node->children[token[0]];
      }
    }
    node->isEndOfWord = true; // Mark the end of the path
  }

  bool search(const std::string &path) {
    PathStructure *node = root;
    std::istringstream iss(path);
    std::string token;

    while (std::getline(iss, token, '/')) {
      if (token.empty())
        continue;

      if (node->children.find(token[0]) == node->children.end()) {
        // Check for dynamic parameter
        bool foundParam = false;
        for (const auto &param : node->params) {
          if (validateParamType(token, param.second)) {
            std::cout << "Parameter: " << param.first
                      << ", Type: " << param.second << ", Value: " << token
                      << "\n";
            foundParam = true;
            break;
          }
        }
        if (!foundParam) {
          return false;
        }
      } else {
        node = node->children[token[0]];
      }
    }

    if (node != nullptr && node->isEndOfWord) {
      return true;
    } else {
      return false;
    }
  }

private:
  PathStructure *root;

  bool validateParamType(const std::string &value,
                           const std::string &expectedType) {
    if (expectedType == "int") {
      for (char c : value) {
        if (!std::isdigit(c)) {
          return false;
        }
      }
      return true;
    } else if (expectedType == "string") {
      return true;
    }
    return false;
  }
};

int main() {
  Trie trie;
  trie.insert("/hello");
  trie.insert("/user/{name:string}");
  trie.insert("/user/{id:int}");
  trie.insert("/member/{id:int}");

  std::string searchPath = "/user/john";
  if (trie.search(searchPath)) {
    std::cout << "Path " << searchPath << " found in the trie.\n";
  } else {
    std::cout << "Path " << searchPath << " not found in the trie.\n";
  }

  searchPath = "/user/123";
  if (trie.search(searchPath)) {
    std::cout << "Path " << searchPath << " found in the trie.\n";
  } else {
    std::cout << "Path " << searchPath << " not found in the trie.\n";
  }

  searchPath = "/member/123";
  if (trie.search(searchPath)) {
    std::cout << "Path " << searchPath << " found in the trie.\n";
  } else {
    std::cout << "Path " << searchPath << " not found in the trie.\n";
  }

  searchPath = "/hello";
  if (trie.search(searchPath)) {
    std::cout << "Path " << searchPath << " found in the trie.\n";
  } else {
    std::cout << "Path " << searchPath << " not found in the trie.\n";
  }

  return 0;
}
