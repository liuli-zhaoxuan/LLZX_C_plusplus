#if 0
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>

//线程池类
class ThreadPool {
public:
	// 构造函数：创建指定数量的工作线程
	explicit ThreadPool(size_t numThreads);
	// 析构函数：停止所有线程
	~ThreadPool();

	// 投递任务到队列中
	template<class F>
	void enqueue(F&& f);
private:
	// 工作线程的函数
	void worker();

	std::vector<std::thread> workers;			//工作线程
	std::queue<std::function<void()>> tasks;	//任务队列

	std::mutex queueMutex;						//保护任务队列的互斥锁
	std::condition_variable condition;			//条件变量，用于线程间通信

	bool stop;									//停止标志
};

ThreadPool::ThreadPool(size_t numThreads):stop(false)
{
	for (size_t i = 0; i < numThreads; i++) {
		workers.emplace_back([this] {
			this->worker();
		});
	}
}

void ThreadPool::worker()
{
	while(true) {
		std::function<void()> task;
		{
			// 锁住互斥锁
			std::unique_lock<std::mutex> lock(queueMutex);

			// 等待条件：任务队列非空或者标志位为true
			condition.wait(lock, [this] {
				return !tasks.empty() || stop;
			});

			// 如果停止且队列为空，退出循环
			if (stop && tasks.empty()) {
				return;
			}

			// 从队列中取任务，使用移动，开销小
			task = std::move(tasks.front());
			tasks.pop();
		}

		// 执行任务（在锁外执行，避免长时间持有锁）
		task();
	}
}

// 将任务添加到队列
template<class F>
void ThreadPool::enqueue(F&& f)
{
	{
		// 锁住互斥锁
		std::unique_lock<std::mutex> lock(queueMutex);

		// 如果线程池已停止，不能再添加任务
		if (stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}

		// 将任务添加到队列，完美转发，保持参数的值类别（左值/右值）
		tasks.emplace(std::forward<F>(f));
	}

	// 通知一个等待的线程有新任务
	condition.notify_one();
}

ThreadPool::~ThreadPool()
{
	{
		// 锁住互斥锁
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;	//设置停止位
	}

	// 通知所有等待的线程
	condition.notify_all();

	// 等待所有线程结束
	for (std::thread& worker : workers) {
		worker.join();
	}
}

int main()
{
	ThreadPool pool(4);	//创建4个线程的线程池

	// 添加8个任务
	for (int i = 0; i < 8; i++) {
		pool.enqueue([i] {
			std::cout << "任务 " << i << "在线程 "
				<< std::this_thread::get_id() << " 执行" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		});
	}
	
	// 等待所有任务完成
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}
#endif

/* 左值、右值
* 左值：有变量名、可以取地址&、可以多次使用、生命周期维持到作用域结束
* 右值：临时对象、不能取地址、只能使用一次、生命周期短暂
*/ 

/* std::move  VS  std::forward
* move：无条件转换成右值，启动移动语义（被移动的就为空）
* forward：有条件保持值类别，保持原样
*/