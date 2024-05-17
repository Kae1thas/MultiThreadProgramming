﻿#include <iostream>
#include <thread>

using namespace std;
void threadF()
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "Дочерний Поток: " << i << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    thread t(threadF);
    for (int i = 0; i < 10; ++i)
    {
        cout << "Родительский Поток: " << i << endl;
    }
    t.join(); //Присоединение Дочернего потока после Родительского
    return 0;
}