#if 0
// 无锁任务队列（生产者消费者问题）
#include <atomic>
#include <iostream>
#include <thread>

//定义一个泛型无锁队列
template<typename T>
class LockFreeQueue {
private:
	//节点结构
	struct Node {
		T data;		//存储的数据
		std::atomic<Node*> next{ nullptr };	//指向下一个节点的原子指针
		explicit Node(T val) : data(val) {}	//节点构造函数
	};
	std::atomic<Node*> head;	//队列头部
	std::atomic<Node*> tail;	//队列尾部
public:
	// 构造函数
	LockFreeQueue() {
		Node* dummy = new Node(T());	//创建一个哨兵节点
		head.store(dummy, std::memory_order_relaxed);	//初始化头部
		tail.store(dummy, std::memory_order_relaxed);	//初始化尾部
	}
	// 析构函数
	~LockFreeQueue() {
		Node* node;
		while (node = head.load(std::memory_order_relaxed)) {
			head.store(node->next, std::memory_order_relaxed);
			delete node; //删除节点释放内存
		}
	}
	// 入队操作
	void push(const T& value) {
		Node* newNode = new Node(value);	//创建新节点
		Node* oldTail = tail.load(std::memory_order_relaxed);
		while (!tail.compare_exchange_weak(oldTail, newNode, 
			std::memory_order_release, std::memory_order_relaxed)) {
			oldTail = tail.load(std::memory_order_relaxed); //重载加载尾部，可以去除
		}
		// 设置新节点为尾部节点的下一个接待你
		oldTail->next.store(newNode, std::memory_order_release);
	}

	// 出队操作
	bool pop(T& value) {
		Node* oldHead = head.load(std::memory_order_acquire);
		Node* tail = this->tail.load(std::memory_order_relaxed);
		Node* next = oldHead->next.load(std::memory_order_relaxed);
		if (oldHead == tail) {
			return false; //队列为空
		}
		value = next->data;	//读取数据
		head.store(next, std::memory_order_release);	//移动头部指针到下一节点
		delete oldHead;
		return true;
	}
};

int main()
{
	LockFreeQueue<int> queue;
	std::thread producer([&]() {
		for (int i = 0; i < 100; ++i) {
			queue.push(i);//生产者线程向队列中推送数据
		}
	});

	std::thread consumer([&]() {
		int value;
		for (int i = 0; i < 100; ++i) {
			while (!queue.pop(value)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));//队列为空，等待一下
			}
			std::cout << "Command:" << value << std::endl;//消费者输出
		}
	});
	producer.join();
	consumer.join();
	return 0;
}
#endif


/* 原子操作API： store 和 load
*  存储与加载
*	std::atomic<int> atomic_var(0);
*	atomic_var.store(42, std::memory_order_relaxed);
*   int value = atomic_var.load(std::memory_order_relaxed);
* 
*	内存序（Memory Order）
*	std::memory_order_relaxed:只保证原子性，不保证执行顺序
* 
*	std::memory_order_acquire(先执行，再执行宽松的，放最前) 与 std::memory_order_release（等所有宽松的执行完，再执行，放最后）（配对使用）
* 
*	std::memory_order_seq_cst（顺序一致性）
* 
*	std::memory_order_consume（数据依赖）
* 
* 总结：	不确定时用 seq_cst（默认）
*		性能敏感且理解内存模型时用 release/acquire
*		只有计数器等简单场景用 relaxed
* 
* compare_exchange_weak(oldTail, newNode, 
*			std::memory_order_release, std::memory_order_relaxed)
* oldTail 旧值，newNode希望的新值，如果相等，就返回成功，不相等返回false，然后将oldTail自动设为newNode
*/