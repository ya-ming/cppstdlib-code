#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int main()
{
  // two shared pointers represting two persons by their name
  shared_ptr<string> pNico(new string("nico"),
                           [](string *p) {  // declare our own deleter
                             cout << "delete " << *p << endl;
                           });
  shared_ptr<string> pJutta(new string("jutta"));

  // shared_ptr<string> pNico = new string("nico");             // ERROR: implicit conversion
  // shared_ptr<string> pNico{new string("nico")};              // OK
  // shared_ptr<string> pNico = make_shared<string>("nico");    // OK
  // shared_ptr<string> pJutta = make_shared<string>("jutta");  // OK

  shared_ptr<string> pNico4;
  // pNico4 = new string("nico");       // ERROR: no assignment for ordinary pointers
  pNico4.reset(new string("nico")); // OK: have to use reset()

  // capitalize person names
  (*pNico)[0] = 'N';
  pJutta->replace(0, 1, "J");

  // put them multiple times in a container
  vector<shared_ptr<string>> whoMadeCoffee;
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pNico);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pNico);

  // print all elements
  for (auto ptr : whoMadeCoffee)
  {
    cout << *ptr << " ";
  }
  cout << endl;

  // overwrte a name again
  *pNico = "Nicolai";

  // print all elements again
  for (auto ptr : whoMadeCoffee)
  {
    cout << *ptr << " ";
  }
  cout << endl;

  // print some internal data
  cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;

  pNico = nullptr;          // pNico does not refer to the string any longer
  whoMadeCoffee.resize(2);  // all copies of the string in pNico are destroyed

  return 0;
}