#ifndef ROUTER_ALGORITHM_H
#define ROUTER_ALGORITHM_H

#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "pathStructure.h"

class RouterAlgorithm {
public:
  void insert(const std::string &path, PathStructure *pathTrie);
  bool search(const std::string &path, PathStructure *pathTrie);

private:
  bool validateParamType(const std::string &value, const std::string &expectedType);
};

#endif

