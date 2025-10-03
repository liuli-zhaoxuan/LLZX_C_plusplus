/*
(1)核心思想
建造者设计模式是一种创建型设计模式，旨在将对象的构建过程与其表示分离。该模式允许逐步构建复杂的对象，同时保持构建过程的灵活性。
建造者设计模式的核心思想是将一个复杂对象的构建过程分解为多个简单的步骤，每个步骤由一个具体的建造者类负责实现。这些步骤按照一定的顺序被调用，最终构建出一个完整的对象。
(2)结构
1）产品类（Product）：要创建的复杂对象。
2）抽象建造者类（Builder）：定义创建产品各个部件的抽象接口。
3）具体建造者类（Concrete Builder）：实现抽象建造者接口，构建和装配各个部件。
4）指导者类（Director）：构建过程中的指挥者，负责按顺序调用建造者的各个部件构建方法。
*/

#if 0
#include <iostream>
#include <string>
// 产品类
class Pizza {
public:
	void setDough(const std::string& dough) {
		m_dough = dough;
	}
	void setSauce(const std::string& sauce) {
		m_sauce = sauce;
	}
	void setTopping(const std::string& topping) {
		m_topping = topping;
	}
	void showPizza() const {
		std::cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce, and " << m_topping << " topping." << std::endl;
	}
private:
	std::string m_dough;
	std::string m_sauce;
	std::string m_topping;
};
// 抽象建造者类
class PizzaBuilder {
public:
	virtual ~PizzaBuilder() {}
	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;
	virtual Pizza* getPizza() = 0;
};
// 具体建造者类A
class HawaiianPizzaBuilder : public PizzaBuilder {
public:
	void buildDough() override {
		m_pizza->setDough("cross");
	}
	void buildSauce() override {
		m_pizza->setSauce("mild");
	}
	void buildTopping() override {
		m_pizza->setTopping("ham and pineapple");
	}
	Pizza* getPizza() override {
		return m_pizza;
	}
private:
	Pizza* m_pizza = new Pizza();
};
// 具体建造者类B
class SpicyPizzaBuilder : public PizzaBuilder {
public:
	void buildDough() override {
		m_pizza->setDough("pan baked");
	}
	void buildSauce() override {
		m_pizza->setSauce("hot");
	}
	void buildTopping() override {
		m_pizza->setTopping("pepperoni and jalapeno");
	}
	Pizza* getPizza() override {
		return m_pizza;
	}
private:
	Pizza* m_pizza = new Pizza();
};
// 指导者类
class PizzaDirector {
public:
	void setPizzaBuilder(PizzaBuilder* builder) {
		m_builder = builder;
	}
	void constructPizza() {
		m_builder->buildDough();
		m_builder->buildSauce();
		m_builder->buildTopping();
	}
private:
	PizzaBuilder* m_builder;
};
int main() {
	PizzaDirector director;
	HawaiianPizzaBuilder hawaiianBuilder;
	director.setPizzaBuilder(&hawaiianBuilder);
	director.constructPizza();
	Pizza* hawaiianPizza = hawaiianBuilder.getPizza();
	hawaiianPizza->showPizza();  // Output: Pizza with cross dough, mild sauce, and ham and pineapple topping.
	SpicyPizzaBuilder spicyBuilder;
	director.setPizzaBuilder(&spicyBuilder);
	director.constructPizza();
	Pizza* spicyPizza = spicyBuilder.getPizza();
	spicyPizza->showPizza();  // Output: Pizza with pan baked dough, hot sauce, and pepperoni and jalapeno topping.
	delete hawaiianPizza;
	delete spicyPizza;
	return 0;
}
#endif