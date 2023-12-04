#include "../notATestFramework.h"

class NotATestFrameworkTests {
public:
  int add(int a, int b) { return a + b; }
};

void twoPlusFiveShouldBeTrue() {
  NotATestFramework<NotATestFrameworkTests> sut;

  sut.addTestCase([&sut]() {
    NotATestFrameworkTests instance;
    int result = instance.add(2, 3);

    sut.assert(result == 5, "2 + 3 should be 5");
  });

  sut.runTests();
}

int main() {
  twoPlusFiveShouldBeTrue();

  return 0;
}
