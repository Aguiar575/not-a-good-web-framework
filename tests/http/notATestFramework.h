#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <functional>
#include <vector>

template <typename T>
class NotATestFramework {
public:
    void run_tests();

    void assert(bool condition, const std::string& message);

    void add_test_case(const std::function<void()>& testCase);

private:
    std::vector<std::function<void()>> test_cases;
};

#include "notATestFramework.tpp"

#endif

