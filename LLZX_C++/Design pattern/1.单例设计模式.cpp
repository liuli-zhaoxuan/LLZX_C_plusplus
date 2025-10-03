#if 0
#include <iostream>
#include <mutex>
#include <atomic>
#include <queue>
#include <thread>
using namespace std;

/* 一个空类有构造函数吗？
 * 有的，兄弟有的
 * 默认构造、拷贝构造、拷贝复制运算符、析构
 * 在C++11之后还自动生成 移动构造、移动赋值构造
 * 一旦你为类显式定义了任何构造函数，编译器就不会再自动生成默认构造函数。
*/ 

// 定义一个单例模式的任务队列
// 饿汉模式
class TaskQueue
{
public:
	TaskQueue(const TaskQueue & t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		return m_taskQ;
	}

	void print()
	{
		cout << "我是单例对象的一个成员函数..." << endl;
	}
private:
	TaskQueue() = default;//C++11新特性
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;
	
	// 只能通过类名访问静态属性或者方法得到实例对象
	static TaskQueue* m_taskQ;//静态的成员变量是不能在类的内部初始化的
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

#if 0
// 懒汉模式 + 互斥锁双重检查锁定
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		if (m_taskQ == nullptr)
		{
			m_mutex.lock();
			if (m_taskQ == nullptr)
			{
				m_taskQ = new TaskQueue;
			}
			m_mutex.unlock();
		}
		return m_taskQ;
	}

	void print()
	{
		cout << "我是单例对象的一个成员函数..." << endl;
	}
private:
	TaskQueue() = default;//C++11新特性
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;

	// 只能通过类名访问静态属性或者方法得到实例对象
	static TaskQueue* m_taskQ;//静态的成员变量是不能在类的内部初始化的
	static mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = nullptr;
mutex TaskQueue::m_mutex;	// 类的静态成员变量需要在类外进行定义（分配存储空间）
#endif

#if 0
// 懒汉模式+互斥锁+原子变量
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		TaskQueue* task = m_taskQ.load();//加载原子变量数据，没有则指向nullptr
		if (task == nullptr)
		{
			m_mutex.lock();
			task = m_taskQ.load();//第二个线程就直接获得了值
			if (task == nullptr)
			{
				task = new TaskQueue;
				m_taskQ.store(task);
			}
			m_mutex.unlock();
		}
		return task;
	}

	void print()
	{
		cout << "我是单例对象的一个成员函数..." << endl;
	}
private:
	TaskQueue() = default;//C++11新特性
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;

	// 只能通过类名访问静态属性或者方法得到实例对象
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;
};
mutex TaskQueue::m_mutex;	// 类的静态成员变量需要在类外进行定义（分配存储空间）
atomic<TaskQueue*> TaskQueue::m_taskQ;
#endif

#if 0
// 懒汉模式+静态局部对象解决线程安全问题(Ｃ++11特性)  !!!!最优解！！！
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		static TaskQueue task;
		return &task;
	}

	void print()
	{
		cout << "我是单例对象的一个成员函数..." << endl;
	}
private:
	TaskQueue() = default;//C++11新特性
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;
};
#endif

#if 0
// 单例模式应用实战：多线程模式下的任务队列
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		return m_taskQ;
	}

	void print()
	{
		cout << "我是单例对象的一个成员函数..." << endl;
	}

	// 判断任务队列是否为空
	bool isEmpty()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_data.empty();
	}
	// 添加任务
	void addTask(int task)
	{
		lock_guard<mutex> locker(m_mutex);
		m_data.push(task);
	}
	// 删除任务
	bool popTask()
	{
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty())
		{
			return false;
		}
		m_data.pop();
		return true;
	}
	// 取出一个任务（不删除任务）
	int takeTask()
	{
		lock_guard<mutex> locker(m_mutex);
		if (m_data.empty())
		{
			return -1;
		}
		return m_data.front();
	}
private:
	TaskQueue() = default;//C++11新特性
	static TaskQueue* m_taskQ;

	// 定义任务队列
	queue<int> m_data;
	mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;


int main()
{
	//单例测试
	//TaskQueue* taskQ = TaskQueue::getInstance();
	//taskQ->print();

	// 单例模式：多线程模式下的任务队列
	TaskQueue* taskQ = TaskQueue::getInstance();
	// 生产者
	thread t1([=]()
		{
			for (int i = 0; i < 10; i++) {
				taskQ->addTask(i + 100);
				cout << "+++ push data: " << i + 100 << ", thread ID" << this_thread::get_id() << endl;
				this_thread::sleep_for(chrono::milliseconds(500));
			}
		});

	// 消费者
	thread t2([=]()
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			while (!taskQ->isEmpty()) {
				int num = taskQ->takeTask();
				cout << "+++ take data: " << num << ", thread ID：" << this_thread::get_id() << endl;
				taskQ->popTask();
				this_thread::sleep_for(chrono::milliseconds(1000));
			}
		});

	//阻塞主线程
	t1.join();
	t2.join();
	return 0;
}

#endif