#include "../notATestFrameworkEngine.h"

class NotATestFrameworkEngineTests {
public:
  int add(int a, int b) { return a + b; }
};

void twoPlusFiveShouldBeTrue() {
  NotATestFrameworkEngine<NotATestFrameworkEngineTests> sut;

  sut.addTestCase([&sut]() {
    NotATestFrameworkEngineTests instance;
    int result = instance.add(2, 3);

    sut.assert(result == 5, "2 + 3 should be 5");
  });

  sut.runTests();
}

int main() {
  twoPlusFiveShouldBeTrue();

  return 0;
}
