#include "../../http/httpStatus.h"
#include "../../http/routerAlgorithm.h"
#include "../notATestFrameworkEngine.h"

#include <utility>

void HelloPathShouldBeFound(NotATestFrameworkEngine<RouterAlgorithm> &sut,
                            PathStructure *node) {
  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node, std::make_pair(HttpStatus::OK, "OK"));

    std::string searchPath = "/hello";
    PathStructure *result = instance.search(searchPath, node);

    sut.assert(result != nullptr, "hello path should be found");
    sut.assert(result->status.first == HttpStatus::OK, "status should be OK");
  });
}

void HelloPathShouldBeNotFound(NotATestFrameworkEngine<RouterAlgorithm> &sut,
                               PathStructure *node) {
  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/hello", node, std::make_pair(HttpStatus::NOT_FOUND, ""));

    std::string searchPath = "lehho";
    PathStructure *result = instance.search(searchPath, node);

    sut.assert(result == nullptr, "lehho path should be not found");
  });
}

void UserWithStringPathParameterShouldBeFound(
    NotATestFrameworkEngine<RouterAlgorithm> &sut, PathStructure *node) {

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/user/{name:string}", node, std::make_pair(HttpStatus::OK, "OK"));

    std::string searchPath = "user/john";
    PathStructure *result = instance.search(searchPath, node);

    sut.assert(result != nullptr, "john should be found");
    sut.assert(result->status.first== HttpStatus::OK, "status should be OK");
  });
}

void ThePathStructureShouldSupportMultiplePaths(
    NotATestFrameworkEngine<RouterAlgorithm> &sut, PathStructure *node) {

  sut.addTestCase([&sut, node]() {
    RouterAlgorithm instance;
    instance.insert("/user/{name:string}", node, std::make_pair(HttpStatus::OK, "OK"));
    instance.insert("/user/{age:int}", node, std::make_pair(HttpStatus::OK, "OK"));

    std::string nameSearchPath = "user/john";
    PathStructure *result = instance.search(nameSearchPath, node);
    sut.assert(result != nullptr, "john should be found in the middle of two paths");
    sut.assert(result->status.first == HttpStatus::OK, "status should be OK");

    std::string ageSearchPath = "user/123";
    result = instance.search(ageSearchPath, node);
    sut.assert(result != nullptr, "the age should be found");
    sut.assert(result->status.first == HttpStatus::OK, "status should be OK");
  });
}

int main() {
  NotATestFrameworkEngine<RouterAlgorithm> sut;
  PathStructure *node = new PathStructure();

  HelloPathShouldBeFound(sut, node);
  HelloPathShouldBeNotFound(sut, node);
  UserWithStringPathParameterShouldBeFound(sut, node);
  ThePathStructureShouldSupportMultiplePaths(sut, node);

  sut.runTests();
  delete node;
  return 0;
}
