#include <tuple>
#include <iostream>
#include <complex>
#include <string>
#include <functional>
#include <vector>

using namespace std;

template <typename... Args>
void foo(const std::tuple<Args...> t) {}

std::tuple<int, int, int> foo2()
{
  return {1, 2, 3}; // ERROR - actually, no error
}

std::tuple<int, int, int> foo3()
{
  return std::make_tuple(1, 2, 3); // OK
}

int main()
{
  // create a four-element tuple
  // - elements are initialized with default value (0 for fundamental types)
  tuple<string, int, int, complex<double>> t;

  // create and initialize a tuple explicitly
  tuple<int, float, string> t1(41, 6.3, "nico");

  // "iterate" over elements:
  cout << get<0>(t1) << " "
       << get<1>(t1) << " "
       << get<2>(t1) << " "
       << endl;

  // create tuple with make_tuple()
  // - auto declares t2 with type of right-hand side
  // - thus, type of t2 is tuple
  auto t2 = make_tuple(22, 44, "nico");

  // assign second value in t2 to t1
  get<1>(t1) = get<1>(t2);

  // comparison and assignment
  // - including type converation from tuple<int, int, const char*>
  //   to tuple<int, float, string>
  if (t1 < t2) // compares value for value
  {
    t1 = t2; // OK, assigns value for value
  }

  // modify an existing value via a tuple
  std::string s;
  auto x = std::make_tuple(s);           // x is of type tuple<string>
  std::get<0>(x) = "my value";           // modifies x but not s
  auto y = std::make_tuple(std::ref(s)); // y is of type tuple<string&>, thus y refers to s
  std::get<0>(y) = "my value";           // modifies y

  // extract values of a tuple back to some other variables
  std::tuple<int, float, std::string> t3(77, 1.1, "more light");
  int i;
  float f;
  std::string s3;
  // assign values of t to i, f, and s
  std::make_tuple(std::ref(i), std::ref(f), std::ref(s3)) = t3;

  // To make the use of references in tuples even more convenient,
  // the use of tie() creates a tuple of references
  std::tuple<int, float, std::string> t4(77, 1.1, "more light");
  int i4;
  float f4;
  std::string s4;
  // assign values of t to i, f, and s
  std::tie(i4, f4, s4) = t4;

  // The use of std::ignore allows ignoring tuple elements while parsing with tie().
  // This can be used to extract tuple values partially
  std::tuple<int, float, std::string> t5(78, 1.1, "more light");
  int i5 = -1;
  std::string s5;
  // assign first and third value of t to i and s
  std::tie(i5, std::ignore, s5) = t5;

  // Tuples and Initializer Lists
  // foo(42); // ERROR: explicit conversion to tuple<> required
  foo(std::make_tuple(42)); // OK

  std::tuple<int, double> t6(42, 3.14);    // OK, old syntax
  std::tuple<int, double> t7{42, 3.14};    // OK, new syntax
  std::tuple<int, double> t8 = {42, 3.14}; // ERROR - actually, no error

  std::vector<std::tuple<int, float>> v{{1, 1.0}, {2, 2.0}}; // ERROR - actually, no error
  foo2();

  std::vector<std::tuple<int, float>> v2{std::make_tuple(1, 1.0),
                                        std::make_tuple(2, 2.0)}; // OK
  foo3();

  int n;
  auto t9 = std::tuple_cat(std::make_tuple(42, 7.7, "hello"), std::tie(n));

  return 0;
}