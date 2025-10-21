#if 0
//weak_ptr的简单使用
#include <iostream>
#include <memory>

class Myclass {
public:
	Myclass(int value): data(value) {
		std::cout << "MyClass 构造函数, 值 = " << data << std::endl;
	}

	~Myclass() {
		std::cout << "MyClass 析构函数, 值 = " << data << std::endl;
	}

	void print() const {
		std::cout << "当前值：" << data << std::endl;
	}

private:
	int data;
};

int main() {
	std::shared_ptr<Myclass> sharedobj = std::make_shared<Myclass>(42);
	std::weak_ptr<Myclass> weakobj = sharedobj;

	//因为weak_ptr不控制对象的生命周期，它只是观察者。当我们通过weak_ptr访问对象时，必须将weak_ptr“升级”为shared_ptr，以确保在访问期间对象不会被销毁
	if (auto tempShared = weakobj.lock()) { // 尝试获取shared_ptr
		std::cout << "对象仍然存在：";
		tempShared->print();
	}
	else {
		std::cout << "对象已被销毁：" << std::endl;
	}

	sharedobj.reset();

	if (auto tempShared = weakobj.lock()) { // 尝试获取shared_ptr
		std::cout << "对象仍然存在：";
		tempShared->print();
	}
	else {
		std::cout << "对象已被销毁：" << std::endl;
	}
	return 0;
}

#endif