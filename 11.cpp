#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;
int counter = 1;
void threadF() {
    for (int i = 0; i < 10; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            cout <<  "Дочерний Поток " << this_thread::get_id() << ":" << counter++ << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100)); // Явная передача управления
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    thread t(threadF);
    for (int i = 0; i < 10; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            cout << "Родительский Поток: " << this_thread::get_id() << ":" << counter++ << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100)); // Явная передача управления
    }
    t.join();
    return 0;
}
