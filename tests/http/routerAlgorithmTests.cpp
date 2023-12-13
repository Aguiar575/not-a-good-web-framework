#include "../../http/routerAlgorithm.h"
#include "../notATestFrameworkEngine.h"

void HelloPathShouldBeFound() {

  PathStructure *node = new PathStructure();
  NotATestFrameworkEngine<RouterAlgorithm> sut;

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node);

    std::string searchPath = "/hello";
    int result = instance.search(searchPath, node);

    sut.assert(result == true, "hello path should be found");
  });

  sut.runTests();
}

void HelloPathShouldBeNotFound() {

  PathStructure *node = new PathStructure();
  NotATestFrameworkEngine<RouterAlgorithm> sut;

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node);

    std::string searchPath = "lehho";
    int result = instance.search(searchPath, node);

    sut.assert(result == false, "hello path should be not found");
  });

  sut.runTests();
}

int main() {
  HelloPathShouldBeFound();
  HelloPathShouldBeNotFound();

  return 0;
}
