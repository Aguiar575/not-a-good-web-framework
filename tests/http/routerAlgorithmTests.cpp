#include "../../http/routerAlgorithm.h"
#include "../notATestFrameworkEngine.h"

void HelloPathShouldBeFound(NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node);

    std::string searchPath = "/hello";
    int result = instance.search(searchPath, node);

    sut.assert(result == true, "hello path should be found");
  });
}

void HelloPathShouldBeNotFound(NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node);

    std::string searchPath = "lehho";
    int result = instance.search(searchPath, node);

    sut.assert(result == false, "hello path should be not found");
  });
}

void UserWithStringPathParameterShouldBeFound(
    NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/user/{name:string}", node);

    std::string searchPath = "user/john";
    int result = instance.search(searchPath, node);

    sut.assert(result == true, "john should be found");
  });
}

int main() {
  NotATestFrameworkEngine<RouterAlgorithm> sut;

  HelloPathShouldBeFound(sut);
  HelloPathShouldBeNotFound(sut);
  UserWithStringPathParameterShouldBeFound(sut);

  sut.runTests();
  return 0;
}
