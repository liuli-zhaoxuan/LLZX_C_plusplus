#if 0
#include <iostream>
#include <thread>
#include <coroutine> //C++20支持协程

// 简单的协程返回类型
struct FireAndForgetCoroutine {
	struct promise_type {
		FireAndForgetCoroutine get_return_object() { return {}; }
		std::suspend_never initial_suspend() noexcept { return {}; } // 立即执行
		std::suspend_never final_suspend() noexcept { return {}; }
		void unhandled_exception() { std::terminate(); }
		void return_void() {}
	};
};


// 线程函数
void threadFunction()
{
	std::cout << "Hello from thread" << std::endl;
}

// 协程函数 - 会立即执行
FireAndForgetCoroutine coroutineFunction()
{
	std::cout << "Hello from Coroutine" << std::endl;
	co_return; // 需要显式co_return
}


int main()
{
	//创建并启动线程
	std::thread t(threadFunction);
	if (t.joinable()) t.join();

	//启动协程
	coroutineFunction();

	return 0;
}
#endif