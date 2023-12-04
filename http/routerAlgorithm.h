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
  RouterAlgorithm();
  void insert(const std::string &path);
  bool search(const std::string &path);

private:
  PathStructure *root;
  bool validateParamType(const std::string &value, const std::string &expectedType);
};

#endif

