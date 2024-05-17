#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

int widgetsProduced = 0;

int MAX_WIDGETS = 10;
int MAX_A = 5;
int MAX_B = 5;
int MAX_C = 5;

void makeA() {
    unique_lock<mutex> lck(mtx);
    for (int i = 0; i < MAX_A; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Detail A is made\n";
        cv.notify_all();
    }
}

void makeB() {
    unique_lock<mutex> lck(mtx);
    for (int i = 0; i < MAX_B; ++i) {
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Detail B is made\n";
        cv.notify_all();
    }
}

void makeC() {
    unique_lock<mutex> lck(mtx);
    for (int i = 0; i < MAX_C; ++i) {
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Detail C is made\n";
        cv.notify_all();
    }
}

void assembleWidget() {
    unique_lock<mutex> lck(mtx);
    while (widgetsProduced < MAX_WIDGETS) {
        cv.wait(lck, [] { return MAX_A > 0 && MAX_B > 0 && MAX_C > 0; });
        if (MAX_A > 0 && MAX_B > 0 && MAX_C > 0) {
            cout << "Assembling widget\n";
            this_thread::sleep_for(chrono::seconds(1)); // Simulating assembly time
            MAX_A--;
            MAX_B--;
            MAX_C--;
            widgetsProduced++;
            cout << "Widget assembled\n";
        }
    }
}

int main() {
    thread t1(makeA);
    thread t2(makeB);
    thread t3(makeC);
    thread t4(assembleWidget);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
