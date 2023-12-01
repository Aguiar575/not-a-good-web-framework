#pragma once

#include <string>

class HttpStatus {
public:
  static const std::string OK;
  static const std::string NOT_FOUND;

  HttpStatus() = delete;
};
