/*
* 策略设计模式（Strategy Design Pattern）是一种行为型设计模式，它定义了一系列算法，并将每个算法封装到具体的策略类中，使得它们可以互相替换。通过使用策略模式，可以在运行时动态地选择算法，而不需要修改调用算法的代码。
(1)核心思想
策略模式通过将算法的定义和使用分离，使得算法可以在不同的上下文中复用，同时可以在运行时根据需求选择不同的算法实现。
(2)组成部分
策略（Strategy）：策略的抽象类或接口，定义了算法的公共接口。
具体策略（Concrete Strategy）：策略的具体实现类，实现了算法的具体逻辑。
上下文（Context）：使用策略的对象，它持有一个策略对象，并在需要时调用策略的方法。
*/

#if 0
#include <iostream>
// 策略抽象类
class Strategy {
public:
	virtual void execute() = 0;
};
// 具体策略类A
class ConcreteStrategyA : public Strategy {
public:
	void execute() override {
		std::cout << "使用策略A执行算法" << std::endl;
	}
};
// 具体策略类B
class ConcreteStrategyB : public Strategy {
public:
	void execute() override {
		std::cout << "使用策略B执行算法" << std::endl;
	}
};
// 上下文类
class Context {
private:
	Strategy* strategy;
public:
	void setStrategy(Strategy* strategy) {
		this->strategy = strategy;
	}
	void executeStrategy() {
		if (strategy) {
			strategy->execute();
		}
	}
};
int main() {
	Context context;
	// 使用策略A执行算法
	ConcreteStrategyA strategyA;
	context.setStrategy(&strategyA);
	context.executeStrategy();
	// 使用策略B执行算法
	ConcreteStrategyB strategyB;
	context.setStrategy(&strategyB);
	context.executeStrategy();
	return 0;
}
#endif
