
// 单例设计模式
#include <iostream>
using namespace std;

class Singleton
{
public:
	//获取单例实例的静态方法
	static Singleton* getInstace()
	{
		static Singleton instance;//C++11保证线程安全
		return &instance;
	}

	//方法
	void doSomething()
	{
		cout << "我是一个单例对象..." << endl;
	}

	//拷贝构造函数和赋值操作符处理思路：1.在public中删除；2.在private中默认
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	//构造函数私有化,防止外部创建
	Singleton() { cout << "单例构造完毕" << endl; }
	~Singleton() { cout << "单例析构完毕" << endl; }
};

void testSingleton()
{
	cout << "==============开始单例测试==============" << endl;
	Singleton::getInstace()->doSomething();
	Singleton::getInstace()->doSomething();
}

//简单工厂
#include <memory>
// 产品接口抽象
class Shape
{
public:
	virtual void draw() = 0;//绘制接口
	virtual ~Shape() = default;
};

// 具体产品
class Circle : public Shape 
{
public:
	void draw() override { cout << "Drawing a Circle" << endl; }
};

class Rectangle : public Shape 
{
public:
	void draw() override { cout << "Drawing a Rectangle" << endl; }
};

class Triangle : public Shape
{
public:
	void draw() override { cout << "Drawing a Triangle" << endl; }
};

// 简单工厂
class ShapeFactory
{
public:
	static unique_ptr<Shape> createShape(const string& type)
	{
		if (type == "circle") return make_unique<Circle>();
		else if (type == "rectangle") return make_unique<Rectangle>();
		else if(type == "triangle") return make_unique<Triangle>();
		else {
			cout << type << "是无效的产品" << endl;
			return nullptr;
		}
	}
};

void testFactory()
{
	cout << "==============开始工厂测试==============" << endl;
	auto circle = ShapeFactory::createShape("circle");
	auto rectangle = ShapeFactory::createShape("rectangle");
	auto triangle = ShapeFactory::createShape("triangle");
	auto llzx = ShapeFactory::createShape("llzx");

	if (circle) circle->draw();
	if (rectangle) rectangle->draw();
	if (triangle) triangle->draw();
	if (llzx) llzx->draw();
}


//观察者设计模式
#include <vector>

// 观察者接口类
class Observer
{
public:
	virtual void update(const string& message) = 0;
};

// 主题类
class Subject
{
public:
	vector<Observer*> obs_;
	string message;
public:
	void notifyObservers(){ for (auto obs : obs_) obs->update(message); }
	void addObserver(Observer* obs) { obs_.push_back(obs); }
	void removeObserver(Observer* obs) 
	{ 
		for (auto it = obs_.begin(); it != obs_.end(); ++it)
		{
			if (*it == obs) 
			{
				obs_.erase(it);
				break;
			}
		}
	}
	void setMessage(const string& newMessage) { 
		message = newMessage; 
		notifyObservers();
	}
	string getMessage() const { return message; }
};

//定义两个观察者类
class ObsA :public Observer
{
	void update(const string& message) override {
		cout << "观察者A收到：" << message << endl;
	}
};

class ObsB :public Observer
{
	void update(const string& message) override {
		cout << "观察者B收到：" << message << endl;
	}
};

void testObserver()
{
	cout << "==============开始观察者测试==============" << endl;
	Subject sub;
	ObsA obA;
	ObsB obB;

	sub.addObserver(&obA);
	sub.addObserver(&obB);
	sub.setMessage("状态1发布");
	sub.setMessage("状态2发布");

	sub.removeObserver(&obB);
	sub.setMessage("状态3发布");
}

//策略设计模式
class Strategy
{
public:
	virtual void execute() = 0;
};

class StrategyA : public Strategy
{
	void execute() override { cout << "使用了策略A的方案" << endl;	}
};

class StrategyB : public Strategy
{
	void execute() override { cout << "使用了策略B的方案" << endl; }
};

class Situation
{
private:
	Strategy* strategy = nullptr;
public:
	void setStrategy(Strategy* strategy) {
		this->strategy = strategy;
	}
	void excuteStrategy() {
		if (strategy) {
			strategy->execute();
		}
	}
};

void testStrategy()
{
	cout << "==============开始策略测试==============" << endl;
	StrategyA a;
	StrategyB b;

	Situation s;
	s.setStrategy(&a);
	s.excuteStrategy();

	s.setStrategy(&b);
	s.excuteStrategy();
}

int main() {
	
	//testSingleton();
	//testFactory();
	//testObserver();
	//testStrategy();
	return 0;
}