#include <utility>
#include <functional>
#include <iostream>

int main()
{
  int i = 0;

  // a pair refers to an int twice so that, finally, i has the value 2
  auto p = std::make_pair(std::ref(i), std::ref(i));
  ++p.first;
  ++p.second;

  std::cout << "i: " << i << std::endl;

  int a;

  // extract second value into c (ignore first one)
  std::tie(std::ignore, a) = p;

  std::cout << "a: " << a << std::endl;

  return 0;
}