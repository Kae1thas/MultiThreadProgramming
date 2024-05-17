﻿#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
void* ThreadF(void*)
{
    cout << "Дочерний поток запущен..." << endl;
    sleep(5); // имитация
    pthread_exit(NULL);
}

int main()
{
    pthread_t t;

    if (pthread_create(&t, NULL, ThreadF, NULL))
    {
        cerr << "Error: Ошибка при создании потока." << endl;
        return 1;
    }

    // Ожидание 2 секунд
    sleep(2); // имитация
    if (pthread_cancel(t))
    {
        cerr << "Error: Ошибка при завершении потока." << endl;
        return 1;
    }
    cout << "Дочерний поток завершен родительским." << endl;

    if (pthread_join(t, NULL))
    {
        cerr << "Error: Ошибка при присоединении потока." << endl;
        return 1;
    }
    cout << "Родительский поток запущен." << endl;
    return 0;
}