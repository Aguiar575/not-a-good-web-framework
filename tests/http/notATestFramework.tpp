template <typename T>
void NotATestFramework<T>::run_tests() {
  for (const auto &test_case : test_cases) {
    test_case();
  }
  std::cout << "Okay" << std::endl;
}

template <typename T>
void NotATestFramework<T>::assert(bool condition, const std::string &message) {
  if (!condition) {
    std::cout << "Failed: " << message << std::endl;
  }
}

template <typename T>
void NotATestFramework<T>::add_test_case(const std::function<void()> &test_case) {
  test_cases.push_back(test_case);
}
