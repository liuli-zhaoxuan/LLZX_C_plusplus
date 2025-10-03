/*
原型设计模式：
(1)核心思想
原型设计模式是一种对象创建型模式，它通过复制现有对象来创建新的对象，而无需显式地调用构造函数。简单来说，原型设计模式就是通过克隆已有对象来创建新对象。
(2)结构
1）抽象原型类（Prototype）：定义具有克隆方法的接口。
2）具体原型类（Concrete Prototype）：实现抽象原型类的克隆方法。
3）客户端（Client）：通过调用原型对象的克隆方法来创建新对象。
*/

#if 0
//背景:假设我们有一个图形库，其中有一个基类 Shape 表示图形，它有一个纯虚函数 draw() 用于绘制图形。现在我们希望能够复制已有的图形对象来创建新的图形对象，而无需重新构造图形对象。
#include <iostream>
#include <string>
// 图形基类
class Shape {
public:
	virtual ~Shape() {}
	virtual void draw() = 0;
	virtual Shape* clone() = 0;
};
// 圆形类
class Circle : public Shape {
private:
	std::string color;
	int radius;
public:
	Circle(std::string color, int radius) : color(color), radius(radius) {}
	void draw() override {
		std::cout << "Drawing a circle with color " << color << " and radius " << radius << std::endl;
	}
	Shape* clone() override {
		return new Circle(*this);
	}
};
int main() {
	// 创建一个原型对象
	Shape* circlePrototype = new Circle("red", 5);
	// 克隆原型对象来创建新对象
	Shape* circle1 = circlePrototype->clone();
	Shape* circle2 = circlePrototype->clone();
	// 绘制图形
	circle1->draw();  // Output: Drawing a circle with color red and radius 5
	circle2->draw();  // Output: Drawing a circle with color red and radius 5
	delete circlePrototype;
	delete circle1;
	delete circle2;
	return 0;
}
#endif