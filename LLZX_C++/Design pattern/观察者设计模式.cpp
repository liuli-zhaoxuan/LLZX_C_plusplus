/*
(1)��Ҫ��ɲ���
���⣨Subject�������۲�Ķ�����ά��һ���۲����б����ṩ��ӡ�ɾ����֪ͨ�۲��ߵķ�����
�۲��ߣ�Observer����һ���������ӿڣ�������һ��������������֪ͨ�ķ�����
����۲��ߣ�Concrete Observer�����۲��ߵľ���ʵ���࣬ʵ���˽���֪ͨ��������Ӧ����ķ�����
(2)�ص�
ʵ���˶���֮�������ϡ�
���Զ�̬����Ӻ��Ƴ��۲��ߡ�
�۲��ߺ�����֮��Ľ���ͨ���ӿڽ��У�������ϵͳ������ԺͿ���չ�ԡ�
*/

#if 0
#include <iostream>
#include <vector>
class Observer;
// ���������
class Subject {
public:
	virtual void attach(Observer* observer) = 0;
	virtual void detach(Observer* observer) = 0;
	virtual void notify() = 0;
};
// �۲��߳�����
class Observer {
public:
	virtual void update() = 0;
};
// ����۲�����A
class ConcreteObserverA : public Observer {
public:
	void update() override {
		std::cout << "����۲���A�յ�֪ͨ��������Ӧ" << std::endl;
	}
};
// ����۲�����B
class ConcreteObserverB : public Observer {
public:
	void update() override {
		std::cout << "����۲���B�յ�֪ͨ��������Ӧ" << std::endl;
	}
};
// ����������
class ConcreteSubject : public Subject {
private:
	std::vector<Observer*> observers;
public:
	void attach(Observer* observer) override {
		observers.push_back(observer);
	}
	void detach(Observer* observer) override {
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == observer) {
				observers.erase(it);
				break;
			}
		}
	}
	void notify() override {
		for (auto observer : observers) {
			observer->update();
		}
	}
};
int main() {
	ConcreteSubject subject;
	Observer* observerA = new ConcreteObserverA();
	Observer* observerB = new ConcreteObserverB();
	subject.attach(observerA);
	subject.attach(observerB);
	subject.notify(); // ���������۲���A�յ�֪ͨ��������Ӧ������۲���B�յ�֪ͨ��������Ӧ
	subject.detach(observerA);
	subject.notify(); // ���������۲���B�յ�֪ͨ��������Ӧ
	delete observerA;
	delete observerB;
	return 0;
}
#endif