#if 1
#include <iostream>

using namespace std;

//定义回调函数
typedef void (*CallbackFunction) (int);

//自己的功能函数，接受一个回调函数作为参数
void performAction(int value, CallbackFunction callback) {
	//在某些条件下调用回调
	if (value > 0) {
		callback(value);
	}
}

//回调函数具体实现
void myCallbackFunction(int num) {
	cout << "Callback called with value:" << num << endl;
}

int main() {
	int num = 5;
	performAction(num, myCallbackFunction);
	return 0;
}
#endif