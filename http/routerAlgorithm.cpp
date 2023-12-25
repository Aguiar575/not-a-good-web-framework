#include "routerAlgorithm.h"
#include "httpStatus.h"

void RouterAlgorithm::insert(const std::string &path, PathStructure *pathTrie, 
        const std::string &status) {
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
        pathTrie->params.push_back(
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
        newNode->status = status;
        pathTrie->children[token[0]] = newNode;
      }
      pathTrie = pathTrie->children[token[0]];
    }
  }

  pathTrie->isEndOfWord = true;
}

PathStructure *RouterAlgorithm::search(const std::string &path,
                                       PathStructure *pathTrie) {
  std::istringstream iss(path);
  std::string token;

  while (std::getline(iss, token, '/')) {
    if (token.empty())
      continue;

    if (pathTrie->children.find(token[0]) == pathTrie->children.end()) {
      // Check for dynamic parameter
      bool foundParam = false;
      for (const auto &param : pathTrie->params) {
        if (validateParamType(token, param.second)) {
          //          std::cout << "Parameter: " << param.first
          //                    << ", Type: " << param.second << ", Value: " <<
          //                    token
          //                    << "\n";
          foundParam = true;
          break;
        }
      }
      if (!foundParam) {
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
