#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <functional>
#include <iostream>
#include <vector>

template <typename T> class NotATestFrameworkEngine {
public:
  void runTests();

  void assert(bool condition, const std::string &message);

  void addTestCase(const std::function<void()> &test);

private:
  std::vector<std::function<void()>> tests;
};

#include "notATestFrameworkEngine.tpp"

#endif
