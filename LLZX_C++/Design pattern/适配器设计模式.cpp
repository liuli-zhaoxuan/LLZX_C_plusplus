/*
(1)����˼��
���������ģʽ��Adapter Design Pattern����һ�ֽṹ�����ģʽ�����ڽ�һ����Ľӿ�ת��Ϊ��һ����Ľӿڣ�������ͻ��˵�����������ģʽ�������ݵ����ܹ�������ͨ����������һ����Ľӿ�ת��Ϊ��һ����Ľӿڣ�ʹ�����߿����޷�Эͬ������
(2)��Ҫ��ɲ���
1��Ŀ��ӿڣ�Target��������ͻ����������Ľӿ���ʽ��
2����������Adapter�������������ߵĽӿ�ת��ΪĿ��ӿڵ��ࡣ
3���������ߣ�Adaptee������Ҫ��������࣬���пͻ����޷�ֱ��ʹ�õĽӿڡ�
(3)�ص�
1���ӿ�ת����������ģʽͨ��ת���ӿڣ�ʹ�ò����ݵ����ܹ�Эͬ������
2�����������ࣺ�����ڲ��޸������������¸�����Щ�ࡣ
3���������ԣ�����������ʹ�ò�ͬ�ӿڵ���Эͬ���������Ӵ��������ԺͿ���չ�ԡ�

*/
#if 0
#include <iostream>
// Ŀ��ӿ�
class Target {
public:
	virtual void request() = 0;
};
// ����������
class Adaptee {
public:
	void specificRequest() {
		std::cout << "�������ߵ���������" << std::endl;
	}
};
// ��������
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