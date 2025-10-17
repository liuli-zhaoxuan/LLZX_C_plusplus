#if 0
//简易shard_ptr：主要体现其共享管理的作用
#include <cstddef> //std::size_t
#include <utility> //std::exchange, std::forward
#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class SimpleSharedPtr {
private:
	T* ptr_;//对象指针
	std::size_t* count_;//引用计数,分配到堆上

	void release() {
		if (count_) {
			if (--(*count_) == 0) {
				//释放 智能指针对对象的占有，引用计数-1
				delete ptr_;
				delete count_;
			}
			ptr_ = nullptr;
			count_ = nullptr;
		}
	}

public:
	//默认构造
	SimpleSharedPtr() : ptr_(nullptr), count_(nullptr) {}
	//从裸指针构造(现式构造避免隐式转换)
	explicit SimpleSharedPtr(T* p) :ptr_(p) {
		if (p) {
			//对象存在
			count_ = new std::size_t(1);
		}
		else {
			count_ = nullptr;
		}
	}
	//拷贝构造
	SimpleSharedPtr(const SimpleSharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
		if (*count_) (*count_)++;
	}

	//移动构造(不能加const)
	//第一段是错误的，因为移动语义的前提：将右值转移资源，而不是从左值转移
	/*SimpleSharedPtr(SimpleSharedPtr& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
		other.count_ = nullptr;
		other.ptr_ = nullptr;
	}*/

	//exchange(x, new_value)和move(x)的区别：前者返回x旧值，把x赋值成new_value;后者把x转换成右值引用（允许资源被偷走),需要配合手动将x设置成new_value。
	SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)), count_(std::exchange(other.count_, nullptr)) {}


	//析构
	~SimpleSharedPtr() {
		release();
	}

	// 拷贝赋值，返回的是引用
	SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
		if (this != &other) {
			//!!!!先释放自己
			release();

			// 复制别人的资源并增加计数
			ptr_ = other.ptr_;
			count_ = other.count_;
			if (*count_) ++(*count_);//++在前在后的区别：对于内置类型（int等）编译器通常会将两者优化为相同的机器代码。如果返回值被使用，那么后置需要保存一个临时副本以返回旧值。
		}
		return *this;
	}

	// 移动赋值
	SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
		if (this != &other) {
			release();
			ptr_ = std::exchange(other.ptr_, nullptr);
			count_ = std::exchange(other.count_, nullptr);
		}
		return *this;
	}

	//访问
	T* get() const { return ptr_; };
	T& operator*() { assert(ptr_); return *ptr_; };
	T* operator->() { assert(ptr_); return ptr_; }
	explicit operator bool() const { return ptr_ != nullptr; }//这个有点奇怪

	std::size_t use_count() const { return count_ ? *count_ : 0; }

	//释放当前所有权，并接管新指针
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

// 简单的make_shared(不做控制块优化)
template<typename T, typename ... Args>
SimpleSharedPtr<T> make_simple_shared(Args&& ... args) {
	return SimpleSharedPtr<T>(new T(std::forward<Args>(args)...));
}

// 测试示例
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
		// p2,p3 出作用域，引用计数回到1
		std::cout << "after inner scope, p1.use_count = " << p1.use_count() << "\n"; // 1
		p1.reset(); // 释放对象 -> Foo 被销毁
		std::cout << "after reset, p1.use_count = " << p1.use_count() << "\n"; // 0
	}

	// 测试从裸指针构造并赋值
	{
		SimpleSharedPtr<int> a(new int(10));
		SimpleSharedPtr<int> b;
		b = a;
		std::cout << "a.use_count = " << a.use_count() << ", *a = " << *a << "\n";
	} // int 被删除

	return 0;
}

#endif