﻿#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void* threadF(void*)
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "Дочерний Поток: " << i << endl;
        usleep(200000); // имитация
    }
    pthread_exit(NULL);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    // Создаем поток(с валидацией)
    pthread_t t;
    if (pthread_create(&t, NULL, threadF, NULL) != 0)
    {
        cerr << "Ошибка при создании потока" << endl;
        return 1;
    }

    // Ждем завершения дочернего потока(с валидацией)
    if (pthread_join(t, NULL) != 0)
    {
        cerr << "Ошибка при присоединении потока" << endl;
        return 1;
    }
    for (int i = 0; i < 10; ++i)
    {
        cout << "Родительский Поток: " << i << endl;
        usleep(200000); // имитация
    }
    return 0;
}