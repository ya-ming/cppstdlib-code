// Misusing Shared Pointer

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person : public enable_shared_from_this<Person>
{
public:
  string name;
  shared_ptr<Person> mother;
  shared_ptr<Person> father;
  vector<weak_ptr<Person>> kids;

  Person(const string &n,
         shared_ptr<Person> m = nullptr,
         shared_ptr<Person> f = nullptr)
      : name(n), mother(m), father(f)
  {
  }

  void setParentsAndTheirKidsWrongWay(
      shared_ptr<Person> m = nullptr,
      shared_ptr<Person> f = nullptr)
  {
    mother = m;
    father = f;
    // this results in double free
    /*
      delete nico
      delete nico
      free(): double free detected in tcache 2
     */
    if (m != nullptr)
    {
      m->kids.push_back(shared_ptr<Person>(this));
    }
    if (f != nullptr)
    {
      f->kids.push_back(shared_ptr<Person>(this));
    }
  }

  void setParentsAndTheirKidsCorrectWay(
      shared_ptr<Person> m = nullptr,
      shared_ptr<Person> f = nullptr)
  {
    mother = m;
    father = f;
    if (m != nullptr)
    {
      m->kids.push_back(shared_from_this());
    }
    if (f != nullptr)
    {
      f->kids.push_back(shared_from_this());
    }
  }

  ~Person()
  {
    cout << "delete " << name << endl;
  }
};

shared_ptr<Person> initFamilyWrong(const string &name)
{
  shared_ptr<Person> mom(new Person(name + "'s mom"));
  shared_ptr<Person> dad(new Person(name + "'s dad"));
  shared_ptr<Person> kid(new Person(name));

  kid->setParentsAndTheirKidsWrongWay(mom, dad);
  return kid;
}

shared_ptr<Person> initFamilyCorrect(const string &name)
{
  shared_ptr<Person> mom(new Person(name + "'s mom"));
  shared_ptr<Person> dad(new Person(name + "'s dad"));
  shared_ptr<Person> kid(new Person(name));

  kid->setParentsAndTheirKidsCorrectWay(mom, dad);
  return kid;
}

int main()
{
  int *ptr = new int;
  shared_ptr<int> sp1(ptr);
  shared_ptr<int> sp2(ptr); // ERROR: two shared pointers manage allocated int

  cout << sp1.use_count() << endl;
  cout << sp2.use_count() << endl;

  sp1 = nullptr;
  // sp2 = nullptr; // free(): double free detected in tcache 2

  // shared_ptr<Person> p = initFamilyWrong("nico");
  shared_ptr<Person> p = initFamilyCorrect("nico");

  cout << "nico's family exists" << endl;
  cout << "- nico is shared " << p.use_count() << " times" << endl;
  cout << "- name of 1st kid of nico's mom: "
       << p->mother->kids[0].lock()->name << endl;

  // p = initFamilyWrong("jim");
  p = initFamilyCorrect("jim");
  cout << "jim's family exists" << endl;

  return 0;
}