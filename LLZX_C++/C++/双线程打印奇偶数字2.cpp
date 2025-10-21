#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
atomic<int> counter(1);
int max_num = 10;

void printOdd() {
    while (true) {
        // �ȴ�ֱ��counter������
        while (counter <= max_num && counter % 2 == 0) {
            this_thread::yield(); // �ó�CPUʱ��Ƭ
        }

        if (counter > max_num) break;

        cout << "B(����):" << counter << endl;
        counter++;
    }
}

void printEven() {
    while (true) {
        // �ȴ�ֱ��counter��ż��
        while (counter <= max_num && counter % 2 == 1) {
            this_thread::yield(); // �ó�CPUʱ��Ƭ
        }

        if (counter > max_num) break;

        cout << "A(ż��):" << counter << endl;
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


/*
ע�⣺
this_thread::yield(); // �ó�CPUʱ��Ƭ
��һ��æ�ȴ������������ķ�ʽ����������һ��Э��ʽ��æ�ȴ��������õ�ǰ�̷߳���CPUʱ��Ƭ���������߳����У�
�Ӷ�����CPU��ռ�á����ǣ�����Ȼ�ڲ���ѭ��������������Ա����ϻ���æ�ȴ���

�ܽ᣺ԭ�Ӳ������ʺϼ򵥡����������ݲ�����������Ҫ�󼫸��ҵȴ�ʱ��̵ܶĳ����±��ֳ�ɫ����������Ҫ����ͬ������ʱ��ȴ��򱣻�������״̬���������ͳ��������ͨ�������ʡ�
*/
