/*
ԭ�����ģʽ��
(1)����˼��
ԭ�����ģʽ��һ�ֶ��󴴽���ģʽ����ͨ���������ж����������µĶ��󣬶�������ʽ�ص��ù��캯��������˵��ԭ�����ģʽ����ͨ����¡���ж����������¶���
(2)�ṹ
1������ԭ���ࣨPrototype����������п�¡�����Ľӿڡ�
2������ԭ���ࣨConcrete Prototype����ʵ�ֳ���ԭ����Ŀ�¡������
3���ͻ��ˣ�Client����ͨ������ԭ�Ͷ���Ŀ�¡�����������¶���
*/

#if 0
//����:����������һ��ͼ�ο⣬������һ������ Shape ��ʾͼ�Σ�����һ�����麯�� draw() ���ڻ���ͼ�Ρ���������ϣ���ܹ��������е�ͼ�ζ����������µ�ͼ�ζ��󣬶��������¹���ͼ�ζ���
#include <iostream>
#include <string>
// ͼ�λ���
class Shape {
public:
	virtual ~Shape() {}
	virtual void draw() = 0;
	virtual Shape* clone() = 0;
};
// Բ����
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
	// ����һ��ԭ�Ͷ���
	Shape* circlePrototype = new Circle("red", 5);
	// ��¡ԭ�Ͷ����������¶���
	Shape* circle1 = circlePrototype->clone();
	Shape* circle2 = circlePrototype->clone();
	// ����ͼ��
	circle1->draw();  // Output: Drawing a circle with color red and radius 5
	circle2->draw();  // Output: Drawing a circle with color red and radius 5
	delete circlePrototype;
	delete circle1;
	delete circle2;
	return 0;
}
#endif