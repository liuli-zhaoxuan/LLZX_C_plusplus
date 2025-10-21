#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex m;	//������
condition_variable cv;
int countNum = 1;
int max_num = 10;

void printOdd() {
	while (true) {
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {
			return (countNum % 2 == 1 || countNum > max_num);
		});

		//��������
		if (countNum > max_num) break;

		cout << "B(����):" << countNum << endl;
		countNum++;

		lock.unlock();
		cv.notify_one();
	}
}

void printEven() {
	while (true) {
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {
			return (countNum % 2 == 0 || countNum > max_num);
			});

		//��������
		if (countNum > max_num) break;

		cout << "A(ż��):" << countNum << endl;
		countNum++;

		lock.unlock();
		cv.notify_one();
	}
}

int main() {
	thread threadA(printEven);
	thread threadB(printOdd);

	threadA.join();
	threadB.join();
	return 0;
}