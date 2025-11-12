#if 0
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
atomic<int> counter(1);
int max_num = 10;

void printOdd() {
    while (true) {
        // 等待直到counter是奇数
        while (counter <= max_num && counter % 2 == 0) {
            this_thread::yield(); // 让出CPU时间片
        }

        if (counter > max_num) break;

        cout << "B(奇数):" << counter << endl;
        counter++;
    }
}

void printEven() {
    while (true) {
        // 等待直到counter是偶数
        while (counter <= max_num && counter % 2 == 1) {
            this_thread::yield(); // 让出CPU时间片
        }

        if (counter > max_num) break;

        cout << "A(偶数):" << counter << endl;
        counter++;
    }
}

int main() {
	thread threadA(printEven);
	thread threadB(printOdd);

	threadA.join();
	threadB.join();
	return 0;
}

#endif
/*
注意：
this_thread::yield(); // 让出CPU时间片
是一种忙等待（自旋锁）的方式，但是它是一种协作式的忙等待，它会让当前线程放弃CPU时间片，让其他线程运行，
从而减少CPU的占用。但是，它仍然在不断循环检查条件，所以本质上还是忙等待。

总结：原子操作最适合简单、独立的数据操作，在性能要求极高且等待时间很短的场景下表现出色。而对于需要复杂同步、长时间等待或保护多个相关状态的情况，传统的锁机制通常更合适。
*/
