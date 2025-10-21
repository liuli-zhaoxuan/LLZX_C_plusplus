#if 0
//weak_ptr�ļ�ʹ��
#include <iostream>
#include <memory>

class Myclass {
public:
	Myclass(int value): data(value) {
		std::cout << "MyClass ���캯��, ֵ = " << data << std::endl;
	}

	~Myclass() {
		std::cout << "MyClass ��������, ֵ = " << data << std::endl;
	}

	void print() const {
		std::cout << "��ǰֵ��" << data << std::endl;
	}

private:
	int data;
};

int main() {
	std::shared_ptr<Myclass> sharedobj = std::make_shared<Myclass>(42);
	std::weak_ptr<Myclass> weakobj = sharedobj;

	//��Ϊweak_ptr�����ƶ�����������ڣ���ֻ�ǹ۲��ߡ�������ͨ��weak_ptr���ʶ���ʱ�����뽫weak_ptr��������Ϊshared_ptr����ȷ���ڷ����ڼ���󲻻ᱻ����
	if (auto tempShared = weakobj.lock()) { // ���Ի�ȡshared_ptr
		std::cout << "������Ȼ���ڣ�";
		tempShared->print();
	}
	else {
		std::cout << "�����ѱ����٣�" << std::endl;
	}

	sharedobj.reset();

	if (auto tempShared = weakobj.lock()) { // ���Ի�ȡshared_ptr
		std::cout << "������Ȼ���ڣ�";
		tempShared->print();
	}
	else {
		std::cout << "�����ѱ����٣�" << std::endl;
	}
	return 0;
}

#endif