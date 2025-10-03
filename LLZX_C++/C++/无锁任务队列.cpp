#if 0
// ����������У����������������⣩
#include <atomic>
#include <iostream>
#include <thread>

//����һ��������������
template<typename T>
class LockFreeQueue {
private:
	//�ڵ�ṹ
	struct Node {
		T data;		//�洢������
		std::atomic<Node*> next{ nullptr };	//ָ����һ���ڵ��ԭ��ָ��
		explicit Node(T val) : data(val) {}	//�ڵ㹹�캯��
	};
	std::atomic<Node*> head;	//����ͷ��
	std::atomic<Node*> tail;	//����β��
public:
	// ���캯��
	LockFreeQueue() {
		Node* dummy = new Node(T());	//����һ���ڱ��ڵ�
		head.store(dummy, std::memory_order_relaxed);	//��ʼ��ͷ��
		tail.store(dummy, std::memory_order_relaxed);	//��ʼ��β��
	}
	// ��������
	~LockFreeQueue() {
		Node* node;
		while (node = head.load(std::memory_order_relaxed)) {
			head.store(node->next, std::memory_order_relaxed);
			delete node; //ɾ���ڵ��ͷ��ڴ�
		}
	}
	// ��Ӳ���
	void push(const T& value) {
		Node* newNode = new Node(value);	//�����½ڵ�
		Node* oldTail = tail.load(std::memory_order_relaxed);
		while (!tail.compare_exchange_weak(oldTail, newNode, 
			std::memory_order_release, std::memory_order_relaxed)) {
			oldTail = tail.load(std::memory_order_relaxed); //���ؼ���β��������ȥ��
		}
		// �����½ڵ�Ϊβ���ڵ����һ���Ӵ���
		oldTail->next.store(newNode, std::memory_order_release);
	}

	// ���Ӳ���
	bool pop(T& value) {
		Node* oldHead = head.load(std::memory_order_acquire);
		Node* tail = this->tail.load(std::memory_order_relaxed);
		Node* next = oldHead->next.load(std::memory_order_relaxed);
		if (oldHead == tail) {
			return false; //����Ϊ��
		}
		value = next->data;	//��ȡ����
		head.store(next, std::memory_order_release);	//�ƶ�ͷ��ָ�뵽��һ�ڵ�
		delete oldHead;
		return true;
	}
};

int main()
{
	LockFreeQueue<int> queue;
	std::thread producer([&]() {
		for (int i = 0; i < 100; ++i) {
			queue.push(i);//�������߳����������������
		}
	});

	std::thread consumer([&]() {
		int value;
		for (int i = 0; i < 100; ++i) {
			while (!queue.pop(value)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));//����Ϊ�գ��ȴ�һ��
			}
			std::cout << "Command:" << value << std::endl;//���������
		}
	});
	producer.join();
	consumer.join();
	return 0;
}
#endif


/* ԭ�Ӳ���API�� store �� load
*  �洢�����
*	std::atomic<int> atomic_var(0);
*	atomic_var.store(42, std::memory_order_relaxed);
*   int value = atomic_var.load(std::memory_order_relaxed);
* 
*	�ڴ���Memory Order��
*	std::memory_order_relaxed:ֻ��֤ԭ���ԣ�����ִ֤��˳��
* 
*	std::memory_order_acquire(��ִ�У���ִ�п��ɵģ�����ǰ) �� std::memory_order_release�������п��ɵ�ִ���꣬��ִ�У�����󣩣����ʹ�ã�
* 
*	std::memory_order_seq_cst��˳��һ���ԣ�
* 
*	std::memory_order_consume������������
* 
* �ܽ᣺	��ȷ��ʱ�� seq_cst��Ĭ�ϣ�
*		��������������ڴ�ģ��ʱ�� release/acquire
*		ֻ�м������ȼ򵥳����� relaxed
* 
* compare_exchange_weak(oldTail, newNode, 
*			std::memory_order_release, std::memory_order_relaxed)
* oldTail ��ֵ��newNodeϣ������ֵ�������ȣ��ͷ��سɹ�������ȷ���false��Ȼ��oldTail�Զ���ΪnewNode
*/