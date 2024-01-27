#ifndef ROUTER_ALGORITHM_H
#define ROUTER_ALGORITHM_H

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "pathStructure.h"

class RouterAlgorithm {
public:
  void insert(const std::string &path, PathStructure *pathTrie,
              const std::pair<std::string, std::string> &status);
  void insert(const std::string &path, PathStructure *pathTrie,
              const std::pair<std::string, std::string> &status,
              std::string message);
  PathStructure *search(const std::string &path, PathStructure *pathTrie);

private:
  bool validateParamType(const std::string &value,
                         const std::string &expectedType);
};

#endif
