#pragma once

#ifndef HTTPSTATUS_H
#define HTTPSTATUS_H

#include <string>
#include <utility>

enum class HttpStatusCode { OK = 200, NOT_FOUND = 404 };

class HttpStatus {
public:
  static const std::string OK;
  static const std::string NOT_FOUND;

  static std::pair<std::string, std::string> ok();
  static std::pair<std::string, std::string> notFound();

private:
  static const std::pair<std::string, std::string>
  makeStatusPair(std::string status, std::string message);
};

#endif // HTTPSTATUS_H
