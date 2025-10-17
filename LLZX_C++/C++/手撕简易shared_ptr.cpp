#if 0
//����shard_ptr����Ҫ�����乲����������
#include <cstddef> //std::size_t
#include <utility> //std::exchange, std::forward
#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class SimpleSharedPtr {
private:
	T* ptr_;//����ָ��
	std::size_t* count_;//���ü���,���䵽����

	void release() {
		if (count_) {
			if (--(*count_) == 0) {
				//�ͷ� ����ָ��Զ����ռ�У����ü���-1
				delete ptr_;
				delete count_;
			}
			ptr_ = nullptr;
			count_ = nullptr;
		}
	}

public:
	//Ĭ�Ϲ���
	SimpleSharedPtr() : ptr_(nullptr), count_(nullptr) {}
	//����ָ�빹��(��ʽ���������ʽת��)
	explicit SimpleSharedPtr(T* p) :ptr_(p) {
		if (p) {
			//�������
			count_ = new std::size_t(1);
		}
		else {
			count_ = nullptr;
		}
	}
	//��������
	SimpleSharedPtr(const SimpleSharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
		if (*count_) (*count_)++;
	}

	//�ƶ�����(���ܼ�const)
	//��һ���Ǵ���ģ���Ϊ�ƶ������ǰ�᣺����ֵת����Դ�������Ǵ���ֵת��
	/*SimpleSharedPtr(SimpleSharedPtr& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
		other.count_ = nullptr;
		other.ptr_ = nullptr;
	}*/

	//exchange(x, new_value)��move(x)������ǰ�߷���x��ֵ����x��ֵ��new_value;���߰�xת������ֵ���ã�������Դ��͵��),��Ҫ����ֶ���x���ó�new_value��
	SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)), count_(std::exchange(other.count_, nullptr)) {}


	//����
	~SimpleSharedPtr() {
		release();
	}

	// ������ֵ�����ص�������
	SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
		if (this != &other) {
			//!!!!���ͷ��Լ�
			release();

			// ���Ʊ��˵���Դ�����Ӽ���
			ptr_ = other.ptr_;
			count_ = other.count_;
			if (*count_) ++(*count_);//++��ǰ�ں�����𣺶����������ͣ�int�ȣ�������ͨ���Ὣ�����Ż�Ϊ��ͬ�Ļ������롣�������ֵ��ʹ�ã���ô������Ҫ����һ����ʱ�����Է��ؾ�ֵ��
		}
		return *this;
	}

	// �ƶ���ֵ
	SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
		if (this != &other) {
			release();
			ptr_ = std::exchange(other.ptr_, nullptr);
			count_ = std::exchange(other.count_, nullptr);
		}
		return *this;
	}

	//����
	T* get() const { return ptr_; };
	T& operator*() { assert(ptr_); return *ptr_; };
	T* operator->() { assert(ptr_); return ptr_; }
	explicit operator bool() const { return ptr_ != nullptr; }//����е����

	std::size_t use_count() const { return count_ ? *count_ : 0; }

	//�ͷŵ�ǰ����Ȩ�����ӹ���ָ��
	void reset(T* p = nullptr) {
		release();
		if (p) {
			ptr_ = p;
			count_ = new std::size_t(1);
		}
		else {
			ptr_ = nullptr;
			count_ = nullptr;
		}
	}

	void swap(SimpleSharedPtr& other) {
		std::swap(ptr_, other.ptr_);
		std::swap(count_, other.count_);
	}
};

// �򵥵�make_shared(�������ƿ��Ż�)
template<typename T, typename ... Args>
SimpleSharedPtr<T> make_simple_shared(Args&& ... args) {
	return SimpleSharedPtr<T>(new T(std::forward<Args>(args)...));
}

// ����ʾ��
struct Foo {
	int v;
	Foo(int x) : v(x) { std::cout << "Foo(" << v << ") constructed\n"; }
	~Foo() { std::cout << "Foo(" << v << ") destroyed\n"; }
};

int main() {
	{
		auto p1 = make_simple_shared<Foo>(42);
		std::cout << "p1.use_count = " << p1.use_count() << "\n"; // 1
		{
			SimpleSharedPtr<Foo> p2 = p1; // copy
			std::cout << "after copy, p1.use_count = " << p1.use_count() << ", p2.use_count = " << p2.use_count() << "\n"; // 2,2
			SimpleSharedPtr<Foo> p3 = std::move(p2); // move
			std::cout << "after move, p2.use_count = " << p2.use_count() << ", p3.use_count = " << p3.use_count() << "\n"; // 0,2
			if (p3) std::cout << "p3->v = " << p3->v << "\n"; // 42
		}
		// p2,p3 �����������ü����ص�1
		std::cout << "after inner scope, p1.use_count = " << p1.use_count() << "\n"; // 1
		p1.reset(); // �ͷŶ��� -> Foo ������
		std::cout << "after reset, p1.use_count = " << p1.use_count() << "\n"; // 0
	}

	// ���Դ���ָ�빹�첢��ֵ
	{
		SimpleSharedPtr<int> a(new int(10));
		SimpleSharedPtr<int> b;
		b = a;
		std::cout << "a.use_count = " << a.use_count() << ", *a = " << *a << "\n";
	} // int ��ɾ��

	return 0;
}

#endif