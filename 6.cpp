#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

void sleepSortAndPrint(const  string& str) {
    // ��������� ����� ���, ���������������� ����� ������
    chrono::milliseconds sleepTime(str.length() * 200); // ��������� ������� ��� ������ ������������
    this_thread::sleep_for(sleepTime);

    // ������� ������
    cout << str <<  endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector< thread> threads;
    vector< string> inputStrings = {
        "������",
        "�����",
        "���",
        "����",
        "���������",
        "�����",
        "�������",
        "��",
        "������",
        "���������"
    };

    // ��������� ������ �� �����
     sort(inputStrings.begin(), inputStrings.end(), [](const  string& a, const  string& b) {
        return a.length() < b.length();
        });

    // ��������� ������ ��� ������ ������
    for (const string& str : inputStrings) {
        threads.push_back( thread(sleepSortAndPrint, str));
    }

    // ���������� ���������� ���� �������
    for ( thread& t : threads) {
        t.join();
    }

    return 0;
}