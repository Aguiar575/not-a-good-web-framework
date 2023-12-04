
#include "../notATestFrameworkEngine.h"
#include "../../http/routerAlgorithm.h"

void HelloPathShouldBeFound() {
  NotATestFrameworkEngine<RouterAlgorithm> sut;

  sut.addTestCase([&sut]() {
    RouterAlgorithm instance;
    instance.insert("/hello");

    std::string searchPath = "/hello";
    int result = instance.search(searchPath);

    sut.assert(result == true, "hello path should be found");
  });

  sut.runTests();
}

int main() {
  HelloPathShouldBeFound();

  return 0;
}