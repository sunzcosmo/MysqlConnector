#include "Utils.h"

namespace utils {

std::vector<std::string> &split(
    const std::string &str,
    char delim,
    std::vector<std::string> &elems)
{
  std::stringstream strs(str);
  std::string item;
  while(std::getline(strs, item, delim))
  {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &str, char delim)
{
  std::vector<std::string> elems;
  split(str, delim, elems);
  return elems;
}

template <class Type>
Type string2num(const std::string str)
{
  std::istringstream iss(str);
  Type num;
  iss >> num;
  return num;
}

};
