/*
(1)核心思想
适配器设计模式（Adapter Design Pattern）是一种结构型设计模式，用于将一个类的接口转换为另一个类的接口，以满足客户端的需求。适配器模式允许不兼容的类能够合作，通过适配器将一个类的接口转换为另一个类的接口，使得两者可以无缝协同工作。
(2)主要组成部分
1）目标接口（Target）：定义客户端所期望的接口形式。
2）适配器（Adapter）：将被适配者的接口转换为目标接口的类。
3）被适配者（Adaptee）：需要被适配的类，具有客户端无法直接使用的接口。
(3)特点
1）接口转换：适配器模式通过转换接口，使得不兼容的类能够协同工作。
2）复用现有类：可以在不修改现有类的情况下复用这些类。
3）提高灵活性：适配器可以使得不同接口的类协同工作，增加代码的灵活性和可扩展性。

*/
#if 0
#include <iostream>
// 目标接口
class Target {
public:
	virtual void request() = 0;
};
// 被适配者类
class Adaptee {
public:
	void specificRequest() {
		std::cout << "被适配者的特殊请求" << std::endl;
	}
};
// 类适配器
class Adapter : public Target, private Adaptee {
public:
	void request() override {
		specificRequest();
	}
};
int main() {
	Target* adapter = new Adapter();
	adapter->request();
	delete adapter;
	return 0;
}
#endif