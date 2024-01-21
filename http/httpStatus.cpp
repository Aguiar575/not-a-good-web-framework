#include "httpStatus.h"

const std::string HttpStatus::OK =
    std::to_string(static_cast<int>(HttpStatusCode::OK)) + " OK";
const std::string HttpStatus::NOT_FOUND =
    std::to_string(static_cast<int>(HttpStatusCode::OK)) + " 404 NOT FOUND";

std::pair<std::string, std::string> HttpStatus::ok(){
    return makeStatusPair(std::to_string(static_cast<int>(HttpStatusCode::OK)), HttpStatus::OK);
}

std::pair<std::string, std::string> HttpStatus::notFound(){
    return makeStatusPair(std::to_string(static_cast<int>(HttpStatusCode::NOT_FOUND)), HttpStatus::NOT_FOUND);
}

const std::pair<std::string, std::string>
HttpStatus::makeStatusPair(std::string status, std::string message) {
  return std::make_pair(status, message);
}
