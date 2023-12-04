template <typename T>
void NotATestFrameworkEngine<T>::runTests() {
  for (const auto &test : tests) {
    test();
  }
  std::cout << "Okay" << std::endl;
}

template <typename T>
void NotATestFrameworkEngine<T>::assert(bool condition, const std::string &message) {
  if (!condition) {
    std::cout << "Failed: " << message << std::endl;
  }
}

template <typename T>
void NotATestFrameworkEngine<T>::addTestCase(const std::function<void()> &test) {
  tests.push_back(test);
}
