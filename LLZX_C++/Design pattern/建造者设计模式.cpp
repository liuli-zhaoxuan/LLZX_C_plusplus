/*
(1)����˼��
���������ģʽ��һ�ִ��������ģʽ��ּ�ڽ�����Ĺ������������ʾ���롣��ģʽ�����𲽹������ӵĶ���ͬʱ���ֹ������̵�����ԡ�
���������ģʽ�ĺ���˼���ǽ�һ�����Ӷ���Ĺ������̷ֽ�Ϊ����򵥵Ĳ��裬ÿ��������һ������Ľ������ฺ��ʵ�֡���Щ���谴��һ����˳�򱻵��ã����չ�����һ�������Ķ���
(2)�ṹ
1����Ʒ�ࣨProduct����Ҫ�����ĸ��Ӷ���
2�����������ࣨBuilder�������崴����Ʒ���������ĳ���ӿڡ�
3�����彨�����ࣨConcrete Builder����ʵ�ֳ������߽ӿڣ�������װ�����������
4��ָ�����ࣨDirector�������������е�ָ���ߣ�����˳����ý����ߵĸ�����������������
*/

#if 0
#include <iostream>
#include <string>
// ��Ʒ��
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
// ����������
class PizzaBuilder {
public:
	virtual ~PizzaBuilder() {}
	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;
	virtual Pizza* getPizza() = 0;
};
// ���彨������A
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
// ���彨������B
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
// ָ������
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