#ifndef SUN_MYSQL_CONNECTOR_UTILS_H_
#define SUN_MYSQL_CONNECTOR_UTILS_H_
#include <sstream>
#include <vector>
#include <string>

namespace utils {
  std::vector<std::string> &split(const std::string &, char, std::vector<std::string> &);
  
  std::vector<std::string> split(const std::string &str, char delim);
  
  template <class Type>
  Type string2num(const std::string);
};

#endif  //SUN_MYSQL_CONNCTOR_UTILS_H_
