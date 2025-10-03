/*
抽象工厂设计
核心思想：
提供了一种创建一系列相关或相互依赖对象的接口，而无需指定其具体类。
通过定义一个抽象工厂接口，声明一组用于创建不同产品族的抽象方法，每个具体的工厂类实现这个接口，并负责创建特定的产品族。
核心思想是通过创建一组相关的产品，而不是单个产品。它提供了一种封装对象创建的方式，使得客户端可以从具体实现中解耦。

结构：
1）抽象产品接口（Abstract Product）：定义产品的接口。
2）具体产品类（Concrete Product）：实现抽象产品接口。
3）抽象工厂接口（Abstract Factory）：声明一组创建不同产品的方法。
4）具体工厂类（Concrete Factory）：实现抽象工厂接口，负责创建具体产品。

*/

#if 0
// 背景：假设你正在开发一个图形绘制应用程序，需要根据用户的选择创建不同类型的图形对象，如按钮（Button）和文本框（Textbox）。你可以使用抽象工厂模式来实现这个场景。
#include <iostream>
// 抽象产品接口 - 按钮
class Button {
public:
	virtual void render() = 0;
	virtual ~Button() = default;
};
// 具体产品类 - Windows按钮
class WindowsButton : public Button {
public:
	void render() override {
		std::cout << "Rendering a Windows button." << std::endl;
	}
};
// 具体产品类 - Mac按钮
class MacButton : public Button {
public:
	void render() override {
		std::cout << "Rendering a Mac button." << std::endl;
	}
};
// 抽象产品接口 - 文本框
class Textbox {
public:
	virtual void render() = 0;
	virtual ~Textbox() = default;
};
// 具体产品类 - Windows文本框
class WindowsTextbox : public Textbox {
public:
	void render() override {
		std::cout << "Rendering a Windows textbox." << std::endl;
	}
};
// 具体产品类 - Mac文本框
class MacTextbox : public Textbox {
public:
	void render() override {
		std::cout << "Rendering a Mac textbox." << std::endl;
	}
};
// 抽象工厂接口
class GUIFactory {
public:
	virtual Button* createButton() = 0;
	virtual Textbox* createTextbox() = 0;
	virtual ~GUIFactory() = default;
};
// 具体工厂类 - Windows工厂
class WindowsFactory : public GUIFactory {
public:
	Button* createButton() override {
		return new WindowsButton();
	}
	Textbox* createTextbox() override {
		return new WindowsTextbox();
	}
};
// 具体工厂类 - Mac工厂
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
	// 创建一个Windows风格的工厂
	GUIFactory* windowsFactory = new WindowsFactory();
	// 创建一个Windows风格的按钮
	Button* windowsButton = windowsFactory->createButton();
	// 渲染按钮
	windowsButton->render();  // Output: Rendering a Windows button.
	// 创建一个Windows风格的文本框
	Textbox* windowsTextbox = windowsFactory->createTextbox();
	// 渲染文本框
	windowsTextbox->render();  // Output: Rendering a Windows textbox.
	// 创建一个Mac风格的工厂
	GUIFactory* macFactory = new MacFactory();
	// 创建一个Mac风格的按钮
	Button* macButton = macFactory->createButton();
	// 渲染按钮
	macButton->render();  // Output: Rendering a Mac button.
	// 创建一个Mac风格的文本框
	Textbox* macTextbox = macFactory->createTextbox();
	// 渲染文本框
	macTextbox->render();  // Output: Rendering a Mac textbox.
	// 清理资源
	delete windowsFactory;
	delete windowsButton;
	delete windowsTextbox;
	delete macFactory;
	delete macButton;
	delete macTextbox;
	return 0;
}

//抽象工厂与简单工厂的区别：工厂模式负责创建一种产品，而抽象工厂模式负责创建一整套相关的产品族。
#endif