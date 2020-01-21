#include <iostream>
#include <egg/thread/pool.hpp>


namespace test
{

struct process
{
  std::thread::id execute(
      int i)
  {
    ++i;

    return std::this_thread::get_id();
  }
};

}

int
main(
  const int   argc,
  const char* argv[])
{
  using std::cout;
  using std::endl;
  using std::cerr;

  cout << "Checking thread pool with lambda" << endl;
  cout << "---------------------------------------------------------" << endl;

  try
  {
    egg::thread::pool tp(4);

    std::vector<std::thread::id> result;

    for (auto i = 0; i < 12; ++i)
    {
      result.push_back(
        tp.enqueue(
          [](int answer) -> std::thread::id
          {
            return std::this_thread::get_id();
          },
        i).get());
    }

    for (auto r : result)
      cout << r << endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  cout  << "---------------------------------------------------------" << endl
        << "Done." << endl << endl;

  cout << "Checking thread pool with member function" << endl;
  cout << "---------------------------------------------------------" << endl;

  try
  {
    egg::thread::pool tp(4);
    std::vector<std::thread::id> result;

    test::process p;

    for (auto i = 0; i < 12; ++i)
    {
      result.push_back(
        tp.enqueue(&test::process::execute, &p, i).get());
    }

    for (auto r : result)
      cout << r << endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  cout  << "---------------------------------------------------------" << endl
        << "Done." << endl << endl;

  return 0;
}
