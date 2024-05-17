#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable a;
bool isParentTurn = true; // �������� � ������������� ������
void threadF() {
    for (int i = 1; i < 11; ++i) {
        unique_lock<mutex> lock(mtx);
        a.wait(lock, [] { return !isParentTurn; }); // ����, ���� �� ������ �������� �����
        cout << "�������� �����: " << i << endl;
        isParentTurn = true; // ���������, ��� ��������� �������� ������ ���� ������������ �������
        a.notify_one(); // ������������� � ���������� � ���������� ������
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    thread t(threadF);
    for (int i = 1; i < 11; ++i) {
        unique_lock<mutex> lock(mtx);
        a.wait(lock, [] { return isParentTurn; }); // ����, ���� �� ������ ������������ �����
        cout << "������������ �����: " << i << endl;
        isParentTurn = false; // ���������, ��� ��������� �������� ������ ���� �������� �������
        a.notify_one(); // ������������� � ���������� � ���������� ������
    }
    t.join();
    return 0;
}
