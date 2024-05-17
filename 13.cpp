#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable a;
bool isParentTurn = true; // Начинаем с родительского потока
void threadF() {
    for (int i = 1; i < 11; ++i) {
        unique_lock<mutex> lock(mtx);
        a.wait(lock, [] { return !isParentTurn; }); // Ждем, пока не станет дочерний поток
        cout << "Дочерний Поток: " << i << endl;
        isParentTurn = true; // Указываем, что следующая итерация должна быть родительским потоком
        a.notify_one(); // Сигнализируем о готовности к следующему выводу
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    thread t(threadF);
    for (int i = 1; i < 11; ++i) {
        unique_lock<mutex> lock(mtx);
        a.wait(lock, [] { return isParentTurn; }); // Ждем, пока не станет родительский поток
        cout << "Родительский Поток: " << i << endl;
        isParentTurn = false; // Указываем, что следующая итерация должна быть дочерним потоком
        a.notify_one(); // Сигнализируем о готовности к следующему выводу
    }
    t.join();
    return 0;
}
