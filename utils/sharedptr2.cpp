#include <string>
#include <fstream> // for ofstream
#include <memory>  // for shared_ptr
#include <cstdio>  // for remove()

// This example ensure that a temporary file gets removed when the
// last reference to it gets destroyed
class FileDeleter
{
private:
  std::string filename;

public:
  FileDeleter(const std::string &fn)
      : filename(fn)
  {
  }

  void operator()(std::ofstream *fp)
  {
    fp->close();                   // close file
    std::remove(filename.c_str()); // delte file
  }
};

int main()
{
  // create and open temporary file
  std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"),
                                    FileDeleter("tmpfile.txt"));

  *fp << "temp data" << std::endl;

  return 0;
}