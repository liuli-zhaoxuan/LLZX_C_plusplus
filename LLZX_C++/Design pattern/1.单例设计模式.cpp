#if 0
#include <iostream>
#include <mutex>
#include <atomic>
#include <queue>
#include <thread>
using namespace std;

/* һ�������й��캯����
 * �еģ��ֵ��е�
 * Ĭ�Ϲ��졢�������졢�������������������
 * ��C++11֮���Զ����� �ƶ����졢�ƶ���ֵ����
 * һ����Ϊ����ʽ�������κι��캯�����������Ͳ������Զ�����Ĭ�Ϲ��캯����
*/ 

// ����һ������ģʽ���������
// ����ģʽ
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
		cout << "���ǵ��������һ����Ա����..." << endl;
	}
private:
	TaskQueue() = default;//C++11������
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;
	
	// ֻ��ͨ���������ʾ�̬���Ի��߷����õ�ʵ������
	static TaskQueue* m_taskQ;//��̬�ĳ�Ա�����ǲ���������ڲ���ʼ����
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

#if 0
// ����ģʽ + ������˫�ؼ������
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
		cout << "���ǵ��������һ����Ա����..." << endl;
	}
private:
	TaskQueue() = default;//C++11������
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;

	// ֻ��ͨ���������ʾ�̬���Ի��߷����õ�ʵ������
	static TaskQueue* m_taskQ;//��̬�ĳ�Ա�����ǲ���������ڲ���ʼ����
	static mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = nullptr;
mutex TaskQueue::m_mutex;	// ��ľ�̬��Ա������Ҫ��������ж��壨����洢�ռ䣩
#endif

#if 0
// ����ģʽ+������+ԭ�ӱ���
class TaskQueue
{
public:
	TaskQueue(const TaskQueue& t) = delete;
	TaskQueue& operator=(const TaskQueue& t) = delete;

	static TaskQueue* getInstance()
	{
		TaskQueue* task = m_taskQ.load();//����ԭ�ӱ������ݣ�û����ָ��nullptr
		if (task == nullptr)
		{
			m_mutex.lock();
			task = m_taskQ.load();//�ڶ����߳̾�ֱ�ӻ����ֵ
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
		cout << "���ǵ��������һ����Ա����..." << endl;
	}
private:
	TaskQueue() = default;//C++11������
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;

	// ֻ��ͨ���������ʾ�̬���Ի��߷����õ�ʵ������
	static mutex m_mutex;
	static atomic<TaskQueue*> m_taskQ;
};
mutex TaskQueue::m_mutex;	// ��ľ�̬��Ա������Ҫ��������ж��壨����洢�ռ䣩
atomic<TaskQueue*> TaskQueue::m_taskQ;
#endif

#if 0
// ����ģʽ+��̬�ֲ��������̰߳�ȫ����(��++11����)  !!!!���Ž⣡����
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
		cout << "���ǵ��������һ����Ա����..." << endl;
	}
private:
	TaskQueue() = default;//C++11������
	//TaskQueue(const TaskQueue& t) = default;
	//TaskQueue& operator=(const TaskQueue& t) = default;
};
#endif

#if 0
// ����ģʽӦ��ʵս�����߳�ģʽ�µ��������
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
		cout << "���ǵ��������һ����Ա����..." << endl;
	}

	// �ж���������Ƿ�Ϊ��
	bool isEmpty()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_data.empty();
	}
	// �������
	void addTask(int task)
	{
		lock_guard<mutex> locker(m_mutex);
		m_data.push(task);
	}
	// ɾ������
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
	// ȡ��һ�����񣨲�ɾ������
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
	TaskQueue() = default;//C++11������
	static TaskQueue* m_taskQ;

	// �����������
	queue<int> m_data;
	mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;


int main()
{
	//��������
	//TaskQueue* taskQ = TaskQueue::getInstance();
	//taskQ->print();

	// ����ģʽ�����߳�ģʽ�µ��������
	TaskQueue* taskQ = TaskQueue::getInstance();
	// ������
	thread t1([=]()
		{
			for (int i = 0; i < 10; i++) {
				taskQ->addTask(i + 100);
				cout << "+++ push data: " << i + 100 << ", thread ID" << this_thread::get_id() << endl;
				this_thread::sleep_for(chrono::milliseconds(500));
			}
		});

	// ������
	thread t2([=]()
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			while (!taskQ->isEmpty()) {
				int num = taskQ->takeTask();
				cout << "+++ take data: " << num << ", thread ID��" << this_thread::get_id() << endl;
				taskQ->popTask();
				this_thread::sleep_for(chrono::milliseconds(1000));
			}
		});

	//�������߳�
	t1.join();
	t2.join();
	return 0;
}

#endif