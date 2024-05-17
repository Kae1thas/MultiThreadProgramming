﻿#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void cleanup(void*)
{
    // Просто выводим сообщение о завершении работы
    cout << "Дочерний поток: Завершение работы..." << endl;
}
void* ThreadF(void*)
{
    cout << "Дочерний поток: Запущен..." << endl;

    // Регистрируем функцию очистки для вызова перед завершением потока
    pthread_cleanup_push(cleanup, NULL);
    sleep(5); // имитация работы
    // Выполняем очистку стека
    pthread_cleanup_pop(1);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t;
    if (pthread_create(&t, NULL, ThreadF, NULL))
    {
        cerr << "Ошибка при создании потока." << endl;
        return 1;
    }
    sleep(2); // имитация

    if (pthread_cancel(t))
    {
        cerr << "Ошибка при завершении потока." << endl;
        return 1;
    }
    cout << "Дочерний поток завершен родительским." << endl;
    if (pthread_join(t, NULL))
    {
        cerr << "Ошибка при присоединении потока." << endl;
        return 1;
    }
    cout << "Родительский поток запущен." << endl;
    return 0;
}