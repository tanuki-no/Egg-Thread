/*!
 *
 *	\file		pool.cpp
 *	\brief		Thread pool
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <egg/thread/pool.hpp>


namespace egg
{
namespace thread
{

pool::pool(
      const std::size_t the_thread_count)
  : _stop(ATOMIC_VAR_INIT(false))
{
  for(auto i = 0; i < the_thread_count; ++i)
  {
    _worker.emplace_back(
    std::bind(&pool::job, this));
  }
}

pool::~pool() noexcept
{
  _stop.store(true);
  _condition.notify_all();

  for(std::thread& w: _worker)
    w.join();
}

void
pool::job()
{
  std::function<void()> task;
  auto check = [this]() -> const bool
  {
      return _stop.load() || !_task.empty();
  };

  while (true)
  {
    {
      std::unique_lock<std::mutex> lock(_queue_mutex);

      _condition.wait(lock, check);

      if (_stop.load() && _task.empty())
        return;

      task = std::move(_task.front());
      _task.pop();
    }

    task();
  }
}

} // End of egg::thread namespace
} // End of egg namespace

/* End of file */
