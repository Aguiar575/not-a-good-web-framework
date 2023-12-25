#include "../../http/routerAlgorithm.h"
#include "../notATestFrameworkEngine.h"
#include "../../http/httpStatus.h"

void HelloPathShouldBeFound(NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node, HttpStatus::OK);

    std::string searchPath = "/hello";
    PathStructure* result = instance.search(searchPath, node);
        
    sut.assert(result != nullptr, "hello path should be found");
    sut.assert(result->status == HttpStatus::OK, "status should be OK");
  });
}

void HelloPathShouldBeNotFound(NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node, HttpStatus::NOT_FOUND);

    std::string searchPath = "lehho";
    PathStructure* result = instance.search(searchPath, node);

    sut.assert(result == nullptr, "lehho path should be not found");
  });
}

void UserWithStringPathParameterShouldBeFound(
    NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/user/{name:string}", node, HttpStatus::OK);

    std::string searchPath = "user/john";
    PathStructure* result = instance.search(searchPath, node);

    sut.assert(result != nullptr, "john should be found");
    sut.assert(result->status == HttpStatus::OK, "status should be OK");
  });
}

void ThePathStructureShouldSupportMultiplePaths(
    NotATestFrameworkEngine<RouterAlgorithm> &sut) {

  PathStructure *node = new PathStructure();

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/user/{name:string}", node, HttpStatus::OK);
    instance.insert("/user/{age:int}", node, HttpStatus::OK);

    std::string nameSearchPath = "user/john";
    PathStructure* result = instance.search(nameSearchPath, node);
    sut.assert(result != nullptr, "john should be found");
    sut.assert(result->status == HttpStatus::OK, "status should be OK");

    std::string ageSearchPath = "user/123";
    result = instance.search(ageSearchPath, node);
    sut.assert(result != nullptr, "the age should be found");
    sut.assert(result->status == HttpStatus::OK, "status should be OK");
  });
}

int main() {
  NotATestFrameworkEngine<RouterAlgorithm> sut;

  HelloPathShouldBeFound(sut);
  HelloPathShouldBeNotFound(sut);
  UserWithStringPathParameterShouldBeFound(sut);
  ThePathStructureShouldSupportMultiplePaths(sut);

  sut.runTests();
  return 0;
}
