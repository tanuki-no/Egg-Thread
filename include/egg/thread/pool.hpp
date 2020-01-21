/*!
 *	\file		pool.hpp
 *	\brief		Simple thread pool
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		20/01/2020
 *	\version	1.0
 */

#ifndef EGG_THREAD_POOL
#define EGG_THREAD_POOL

#include <queue>
#include <vector>
#include <functional>
#include <system_error>

#include <atomic>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>

#include <egg/common.hpp>


namespace egg
{
namespace thread
{

struct EGG_PUBLIC pool
{

  pool() noexcept;

  pool(
      const std::size_t the_thread_count);

 ~pool() noexcept;

  pool(const pool&) = delete;
  pool& operator=(const pool&) = delete;

  pool(pool&&) = delete;
  pool& operator=(pool&&) = delete;

  template<class F, class... Args>
  std::future<typename std::result_of<F(Args...)>::type>
  enqueue(
      F&&       f,
      Args&&... args);

private:

  typedef std::vector<std::thread>            thread_vector;
  typedef std::queue< std::function<void()> > task_queue;

private:

  EGG_PRIVATE void job();

private:

  thread_vector           _worker;

  task_queue              _task;
  std::mutex              _queue_mutex;

  std::condition_variable _condition;

  std::atomic_bool        _stop;  
};

template<class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type>
pool::enqueue(
    F&&       f,
    Args&&... args)
{
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task =
    std::make_shared
    <
      std::packaged_task<return_type()>
    >(
      std::bind(
        std::forward<F>(f),
        std::forward<Args>(args)...)
     );

  std::future<return_type> res = task->get_future();

  // don't allow enqueueing after stopping the pool
  if(_stop.load())
    throw std::system_error(
        std::make_error_code(std::errc::io_error),
        "Enqueue on stopped thread_pool");

  if (!_stop.load())
  {
    std::unique_lock<std::mutex> lock(_queue_mutex);
    _task.emplace([task](){ (*task)(); });
  }

  _condition.notify_one();

  return res;
}

} // End of egg::thread namespace
} // End of egg namespace

#endif // EGG_THREAD_POOL

/* End of file */
