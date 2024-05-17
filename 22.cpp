#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <sys/stat.h>
#include <pthread.h>
#include <chrono>
#include <signal.h>
#include <condition_variable>
using namespace std;

mutex printM;
void print(string str) {
    printM.lock();

    cout << str << endl;

    printM.unlock();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string text;
    const int number_of_philosophers = 5;

    struct Forks {
    public:
        Forks() : is_l_available(true), is_r_available(true) {}
        mutex mu;
        condition_variable l_cond, r_cond;
        bool is_l_available;
        bool is_r_available;
    };

    auto eat = [](Forks& l_fork, Forks& r_fork, int philosopher_number) {
        unique_lock<mutex> lock(l_fork.mu);

        l_fork.l_cond.wait(lock, [&] { return l_fork.is_l_available; });

        int r_fork_index = (number_of_philosophers + (philosopher_number - 1)) % number_of_philosophers;
        {
            unique_lock<mutex> r_lock(r_fork.mu);
            r_fork.l_cond.wait(lock, [&] { return r_fork.is_r_available; });

            print("Философ " + to_string(philosopher_number) + " ест...");

            chrono::milliseconds timeout(1500);
            this_thread::sleep_for(timeout);
            print("Философ " + to_string(philosopher_number) + " закончил есть и думает...");

            l_fork.is_l_available = true;
            l_fork.l_cond.notify_one();

            r_fork.is_r_available = true;
            r_fork.r_cond.notify_one();
        }
        };


    Forks forks[number_of_philosophers];
    thread philosopher[number_of_philosophers];

    for (int i = 0; i < number_of_philosophers; ++i) {
        auto philosopher_number = i + 1;
        print("Философ " + to_string(philosopher_number) + " думает...");

        int previous_fork_index = (number_of_philosophers + (i - 1)) % number_of_philosophers;
        philosopher[i] = thread(eat, ref(forks[i]), ref(forks[previous_fork_index]), philosopher_number);
    }

    for (auto& ph : philosopher) {
        ph.join();
    }

    return 0;
}
