template <typename T>
void NotATestFrameworkEngine<T>::runTests() {
  bool failed = false;

  for (const auto &test : tests) {
    try {
      test();
    } catch (const std::exception &e) {
      failed = true;
      
      std::cout << e.what() << std::endl;
    }
  }
    
  if(!failed) {
    std::cout << "Okay" << std::endl;
  }
}

template <typename T>
void NotATestFrameworkEngine<T>::assert(bool condition, const std::string &message) {
  if (!condition) {
    throw std::runtime_error("Test Failed: " + message);
  }
}

template <typename T>
void NotATestFrameworkEngine<T>::addTestCase(const std::function<void()> &test) {
  tests.push_back(test);
}

