#if 0
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>

//�̳߳���
class ThreadPool {
public:
	// ���캯��������ָ�������Ĺ����߳�
	explicit ThreadPool(size_t numThreads);
	// ����������ֹͣ�����߳�
	~ThreadPool();

	// Ͷ�����񵽶�����
	template<class F>
	void enqueue(F&& f);
private:
	// �����̵߳ĺ���
	void worker();

	std::vector<std::thread> workers;			//�����߳�
	std::queue<std::function<void()>> tasks;	//�������

	std::mutex queueMutex;						//����������еĻ�����
	std::condition_variable condition;			//���������������̼߳�ͨ��

	bool stop;									//ֹͣ��־
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
			// ��ס������
			std::unique_lock<std::mutex> lock(queueMutex);

			// �ȴ�������������зǿջ��߱�־λΪtrue
			condition.wait(lock, [this] {
				return !tasks.empty() || stop;
			});

			// ���ֹͣ�Ҷ���Ϊ�գ��˳�ѭ��
			if (stop && tasks.empty()) {
				return;
			}

			// �Ӷ�����ȡ����ʹ���ƶ�������С
			task = std::move(tasks.front());
			tasks.pop();
		}

		// ִ������������ִ�У����ⳤʱ���������
		task();
	}
}

// ��������ӵ�����
template<class F>
void ThreadPool::enqueue(F&& f)
{
	{
		// ��ס������
		std::unique_lock<std::mutex> lock(queueMutex);

		// ����̳߳���ֹͣ���������������
		if (stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}

		// ��������ӵ����У�����ת�������ֲ�����ֵ�����ֵ/��ֵ��
		tasks.emplace(std::forward<F>(f));
	}

	// ֪ͨһ���ȴ����߳���������
	condition.notify_one();
}

ThreadPool::~ThreadPool()
{
	{
		// ��ס������
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;	//����ֹͣλ
	}

	// ֪ͨ���еȴ����߳�
	condition.notify_all();

	// �ȴ������߳̽���
	for (std::thread& worker : workers) {
		worker.join();
	}
}

int main()
{
	ThreadPool pool(4);	//����4���̵߳��̳߳�

	// ���8������
	for (int i = 0; i < 8; i++) {
		pool.enqueue([i] {
			std::cout << "���� " << i << "���߳� "
				<< std::this_thread::get_id() << " ִ��" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		});
	}
	
	// �ȴ������������
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}
#endif

/* ��ֵ����ֵ
* ��ֵ���б�����������ȡ��ַ&�����Զ��ʹ�á���������ά�ֵ����������
* ��ֵ����ʱ���󡢲���ȡ��ַ��ֻ��ʹ��һ�Ρ��������ڶ���
*/ 

/* std::move  VS  std::forward
* move��������ת������ֵ�������ƶ����壨���ƶ��ľ�Ϊ�գ�
* forward������������ֵ��𣬱���ԭ��
*/