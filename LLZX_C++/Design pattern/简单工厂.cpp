//�򵥹���ģʽ��
//����˼�룺������Ĵ������̷�װ��һ�������Ĺ������У��ͻ���ֻ��Ҫͨ������������������Ҫ�Ķ��󣬶�����Ҫֱ��ʵ����������ࡣ
//�ṹ�������ࣺ���𴴽����������࣬ͨ������һ�����߶����������ķ�������Ʒ�ࣺ�������ĳ����ɹ��������������ͻ������Ʒ����н�����

//ʹ�ó��������������ڿ���һ��ͼ�λ���Ӧ�ó�����Ҫ�����û���ѡ�񴴽���ͬ���͵�ͼ�ζ�����Բ�Σ�Circle���;��Σ�Rectangle���������ʹ�ü򵥹�����ʵ�����������
#include <iostream>
#include <string>

// ��Ʒ�� - ͼ��
class Shape {
public:
	virtual void draw() = 0;
	virtual ~Shape() = default; // ȷ������������������
};

// �����Ʒ�� - Բ��
class Circle : public Shape {
public:
	void draw() override {
		std::cout << "����Բ��" << std::endl;
	}
};
// �����Ʒ�� - ����
class Rectangle : public Shape {
public:
	void draw() override {
		std::cout << "���ƾ���" << std::endl;
	}
};

class ShapeFactory {
public:
	// �������ʹ���ͼ�ζ���
	static Shape* createShape(const std::string& type) {
		if (type == "Circle") {
			return new Circle();
		}
		else if (type == "Rectangle") {
			return new Rectangle();
		}
		else {
			return nullptr; // ���Ը�Ϊswitch��Ҳ������map��ӳ��
		}
	}
};

int main() {
	// ʹ�ü򵥹�������ͼ�ζ���
	Shape* shape1 = ShapeFactory::createShape("Circle");
	if (shape1) {
		shape1->draw();
		delete shape1;
	}
	Shape* shape2 = ShapeFactory::createShape("Rectangle");
	if (shape2) {
		shape2->draw();
		delete shape2;
	}
	Shape* shape3 = ShapeFactory::createShape("Triangle");
	if (shape3) {
		shape3->draw();
		delete shape3;
	}
	else {
		std::cout << "��Ч��ͼ������" << std::endl;
	}
	return 0;
}
