#include "routerAlgorithm.h"
#include "httpStatus.h"
#include <string>

void RouterAlgorithm::insert(
    const std::string &path, PathStructure *pathTrie,
    const std::pair<std::string, std::string> &status) {

  std::istringstream iss(path);
  std::string token;
  std::vector<std::pair<std::string, std::string>> params;

  while (std::getline(iss, token, '/')) {
    if (token.empty())
      continue;

    if (token[0] == '{' && token.back() == '}') {
      // Dynamic parameter, e.g., "/user/{name:string}" or "/user/{id:int}"
      size_t colonPos = token.find(':');
      if (colonPos != std::string::npos) {
        // Extract parameter name and type
        params.push_back(
            {token.substr(1, colonPos - 1),
             token.substr(colonPos + 1, token.length() - colonPos - 2)});
      } else {
        // Only parameter name specified without type
        pathTrie->params.push_back({token.substr(1, token.length() - 2), ""});
      }
    } else {
      // Static segment, create a new node if not exists
      if (pathTrie->children.find(token[0]) == pathTrie->children.end()) {
        PathStructure *newNode = new PathStructure();
        pathTrie->children[token[0]] = newNode;
      }
      pathTrie = pathTrie->children[token[0]];
    }
  }

  // Add the other parameters only in the end of the word
  pathTrie->params = params;
  pathTrie->status = status;
  pathTrie->isEndOfWord = true;
}

void RouterAlgorithm::insert(const std::string &path, PathStructure *pathTrie,
                             const std::pair<std::string, std::string> &status,
                             std::string message) {
  insert(path, pathTrie, status);
  pathTrie->message = message;
}

PathStructure *RouterAlgorithm::search(const std::string &path,
                                       PathStructure *pathTrie) {
  std::istringstream iss(path);
  std::string token;

  while (std::getline(iss, token, '/')) {
    if (token.empty())
      continue;

    if (pathTrie->children.find(token[0]) == pathTrie->children.end()) {
      if (!pathTrie->isEndOfWord) {
        return nullptr;
      }
    } else {
      pathTrie = pathTrie->children[token[0]];
    }
  }

  if (pathTrie != nullptr && pathTrie->isEndOfWord) {
    return pathTrie;
  } else {
    return nullptr;
  }
}

bool RouterAlgorithm::validateParamType(const std::string &value,
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
