#if 0
#include <iostream>
#include <thread>
#include <coroutine> //C++20֧��Э��

// �򵥵�Э�̷�������
struct FireAndForgetCoroutine {
	struct promise_type {
		FireAndForgetCoroutine get_return_object() { return {}; }
		std::suspend_never initial_suspend() noexcept { return {}; } // ����ִ��
		std::suspend_never final_suspend() noexcept { return {}; }
		void unhandled_exception() { std::terminate(); }
		void return_void() {}
	};
};


// �̺߳���
void threadFunction()
{
	std::cout << "Hello from thread" << std::endl;
}

// Э�̺��� - ������ִ��
FireAndForgetCoroutine coroutineFunction()
{
	std::cout << "Hello from Coroutine" << std::endl;
	co_return; // ��Ҫ��ʽco_return
}


int main()
{
	//�����������߳�
	std::thread t(threadFunction);
	if (t.joinable()) t.join();

	//����Э��
	coroutineFunction();

	return 0;
}
#endif