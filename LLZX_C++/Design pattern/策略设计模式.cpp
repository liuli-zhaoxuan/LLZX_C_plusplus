/*
* �������ģʽ��Strategy Design Pattern����һ����Ϊ�����ģʽ����������һϵ���㷨������ÿ���㷨��װ������Ĳ������У�ʹ�����ǿ��Ի����滻��ͨ��ʹ�ò���ģʽ������������ʱ��̬��ѡ���㷨��������Ҫ�޸ĵ����㷨�Ĵ��롣
(1)����˼��
����ģʽͨ�����㷨�Ķ����ʹ�÷��룬ʹ���㷨�����ڲ�ͬ���������и��ã�ͬʱ����������ʱ��������ѡ��ͬ���㷨ʵ�֡�
(2)��ɲ���
���ԣ�Strategy�������Եĳ������ӿڣ��������㷨�Ĺ����ӿڡ�
������ԣ�Concrete Strategy�������Եľ���ʵ���࣬ʵ�����㷨�ľ����߼���
�����ģ�Context����ʹ�ò��ԵĶ���������һ�����Զ��󣬲�����Ҫʱ���ò��Եķ�����
*/

#if 0
#include <iostream>
// ���Գ�����
class Strategy {
public:
	virtual void execute() = 0;
};
// ���������A
class ConcreteStrategyA : public Strategy {
public:
	void execute() override {
		std::cout << "ʹ�ò���Aִ���㷨" << std::endl;
	}
};
// ���������B
class ConcreteStrategyB : public Strategy {
public:
	void execute() override {
		std::cout << "ʹ�ò���Bִ���㷨" << std::endl;
	}
};
// ��������
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
	// ʹ�ò���Aִ���㷨
	ConcreteStrategyA strategyA;
	context.setStrategy(&strategyA);
	context.executeStrategy();
	// ʹ�ò���Bִ���㷨
	ConcreteStrategyB strategyB;
	context.setStrategy(&strategyB);
	context.executeStrategy();
	return 0;
}
#endif
