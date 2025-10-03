/*
���󹤳����
����˼�룺
�ṩ��һ�ִ���һϵ����ػ��໥��������Ľӿڣ�������ָ��������ࡣ
ͨ������һ�����󹤳��ӿڣ�����һ�����ڴ�����ͬ��Ʒ��ĳ��󷽷���ÿ������Ĺ�����ʵ������ӿڣ������𴴽��ض��Ĳ�Ʒ�塣
����˼����ͨ������һ����صĲ�Ʒ�������ǵ�����Ʒ�����ṩ��һ�ַ�װ���󴴽��ķ�ʽ��ʹ�ÿͻ��˿��ԴӾ���ʵ���н��

�ṹ��
1�������Ʒ�ӿڣ�Abstract Product���������Ʒ�Ľӿڡ�
2�������Ʒ�ࣨConcrete Product����ʵ�ֳ����Ʒ�ӿڡ�
3�����󹤳��ӿڣ�Abstract Factory��������һ�鴴����ͬ��Ʒ�ķ�����
4�����幤���ࣨConcrete Factory����ʵ�ֳ��󹤳��ӿڣ����𴴽������Ʒ��

*/

#if 0
// ���������������ڿ���һ��ͼ�λ���Ӧ�ó�����Ҫ�����û���ѡ�񴴽���ͬ���͵�ͼ�ζ����簴ť��Button�����ı���Textbox���������ʹ�ó��󹤳�ģʽ��ʵ�����������
#include <iostream>
// �����Ʒ�ӿ� - ��ť
class Button {
public:
	virtual void render() = 0;
	virtual ~Button() = default;
};
// �����Ʒ�� - Windows��ť
class WindowsButton : public Button {
public:
	void render() override {
		std::cout << "Rendering a Windows button." << std::endl;
	}
};
// �����Ʒ�� - Mac��ť
class MacButton : public Button {
public:
	void render() override {
		std::cout << "Rendering a Mac button." << std::endl;
	}
};
// �����Ʒ�ӿ� - �ı���
class Textbox {
public:
	virtual void render() = 0;
	virtual ~Textbox() = default;
};
// �����Ʒ�� - Windows�ı���
class WindowsTextbox : public Textbox {
public:
	void render() override {
		std::cout << "Rendering a Windows textbox." << std::endl;
	}
};
// �����Ʒ�� - Mac�ı���
class MacTextbox : public Textbox {
public:
	void render() override {
		std::cout << "Rendering a Mac textbox." << std::endl;
	}
};
// ���󹤳��ӿ�
class GUIFactory {
public:
	virtual Button* createButton() = 0;
	virtual Textbox* createTextbox() = 0;
	virtual ~GUIFactory() = default;
};
// ���幤���� - Windows����
class WindowsFactory : public GUIFactory {
public:
	Button* createButton() override {
		return new WindowsButton();
	}
	Textbox* createTextbox() override {
		return new WindowsTextbox();
	}
};
// ���幤���� - Mac����
class MacFactory : public GUIFactory {
public:
	Button* createButton() override {
		return new MacButton();
	}
	Textbox* createTextbox() override {
		return new MacTextbox();
	}
};
int main() {
	// ����һ��Windows���Ĺ���
	GUIFactory* windowsFactory = new WindowsFactory();
	// ����һ��Windows���İ�ť
	Button* windowsButton = windowsFactory->createButton();
	// ��Ⱦ��ť
	windowsButton->render();  // Output: Rendering a Windows button.
	// ����һ��Windows�����ı���
	Textbox* windowsTextbox = windowsFactory->createTextbox();
	// ��Ⱦ�ı���
	windowsTextbox->render();  // Output: Rendering a Windows textbox.
	// ����һ��Mac���Ĺ���
	GUIFactory* macFactory = new MacFactory();
	// ����һ��Mac���İ�ť
	Button* macButton = macFactory->createButton();
	// ��Ⱦ��ť
	macButton->render();  // Output: Rendering a Mac button.
	// ����һ��Mac�����ı���
	Textbox* macTextbox = macFactory->createTextbox();
	// ��Ⱦ�ı���
	macTextbox->render();  // Output: Rendering a Mac textbox.
	// ������Դ
	delete windowsFactory;
	delete windowsButton;
	delete windowsTextbox;
	delete macFactory;
	delete macButton;
	delete macTextbox;
	return 0;
}

//���󹤳���򵥹��������𣺹���ģʽ���𴴽�һ�ֲ�Ʒ�������󹤳�ģʽ���𴴽�һ������صĲ�Ʒ�塣
#endif