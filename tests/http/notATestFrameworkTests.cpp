#include "notATestFramework.h"

class NotATestFrameworkTests {
public:
    int add(int a, int b) {
        return a + b;
    }
};

void testing_multiplication() {
    NotATestFramework<NotATestFrameworkTests> tester;

    tester.add_test_case([&tester]() {
        NotATestFrameworkTests instance;
        int result = instance.add(2, 3);
        tester.assert(result == 5, "2 + 3 should be 5");
    });

    tester.run_tests();
}

int main() {
    testing_multiplication();

    return 0;
}

