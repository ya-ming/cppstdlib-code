#include <iostream>
#include <utility>
#include <tuple>

using namespace std;

class Foo
{
public:
  Foo(tuple<int, float>)
  {
    cout << "Foo::Foo(tuple)" << endl;
  }

  template <typename... Args>
  Foo(Args... args)
  {
    cout << "Foo::Foo(args...)" << endl;
  }
};

int main()
{
  // create tuple t
  tuple<int, float> t(1, 2.22);
  cout << "[" << get<0>(t) << ", " << get<1>(t) << "]" << endl;

  pair<int, float> p0(42, 3.14);
  cout << "[" << get<0>(p0) << ", " << get<1>(p0) << "]" << endl;

  typedef pair<int, float> IntFloatPair;
  cout << tuple_size<pair<int, float>>::value << endl;      // yields 2
  std::tuple_element<0,IntFloatPair>::type first = get<0>(p0);
  std::tuple_element<1,IntFloatPair>::type second = get<1>(p0);
  cout << "[" << first << ", " << second << "]" << endl;

  // pass the tuple as a whole to the constructor of Foo
  pair<int, Foo> p1(42, t);

  // pass the elements of the tuple to the constructor of Foo
  pair<int, Foo> p2(piecewise_construct, make_tuple(42), t);

  return 0;
}