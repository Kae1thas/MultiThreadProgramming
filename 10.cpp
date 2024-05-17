#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    const int number_of_philosophers = 5;

    //�����
    struct Forks
    {
    public:
        Forks() { ; }
        mutex mu;
    };

    auto eat = [](Forks& left_fork, Forks& right_fork, int philosopher_number) {
        unique_lock<mutex> llock(left_fork.mu);//����� ����� 
        unique_lock< mutex> rlock(right_fork.mu);//������ �����

        cout << "������� " << philosopher_number << " ���..." << endl;

        chrono::milliseconds timeout(1500);
        this_thread::sleep_for(timeout);

        cout << "������� " << philosopher_number << " �������� ���� � ������..." << endl;
        };

    // ������ ����� � ���������
    Forks forks[number_of_philosophers];
    thread philosopher[number_of_philosophers];

    // �������� �������� ������
    for (int i = 0; i < number_of_philosophers; ++i) {
        auto philosopher_number = i + 1;
        cout << "������� " << philosopher_number << " ������.." << endl;
        auto previous_fork_index = (number_of_philosophers + (i - 1)) % number_of_philosophers;
        philosopher[i] = thread(eat, ref(forks[i]), ref(forks[previous_fork_index]), philosopher_number);
    }

    for (auto& ph : philosopher) {
        ph.join();
    }
}