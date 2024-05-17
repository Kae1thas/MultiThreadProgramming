﻿#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

// Структура для передачи параметров в поток
struct ThreadParams
{
    int t;
    vector<string> messages;
};
// Функция, которую будут исполнять потоки
void* threadF(void* arg)
{
    ThreadParams* params = (ThreadParams*)arg;
    int t = params->t;
    vector<string> messages = params->messages;

    cout << "Поток " << t << ":\n";
    for (const string& message : messages) {
        cout << message << endl;
    }
    pthread_exit(NULL);
}
int main()
{
    // Создаем вектор последовательностей строк для каждого потока
    vector<vector<string>> allMessages = {
        {"Сообщение 1 из потока 1", "Сообщение 2 из потока 1", "Сообщение 3 из потока 1"},
        {"Сообщение 1 из потока 2", "Сообщение 2 из потока 2", "Сообщение 3 из потока 2"},
        {"Сообщение 1 из потока 3", "Сообщение 2 из потока 3", "Сообщение 3 из потока 3"},
        {"Сообщение 1 из потока 4", "Сообщение 2 из потока 4", "Сообщение 3 из потока 4"}
    };
    // Создаем массив идентификаторов потоков
    pthread_t threads[4];
    // Создаем массив параметров для каждого потока
    ThreadParams params[4];
    // Создаем и запускаем каждый поток(валидация)
    for (int i = 0; i < 4; ++i)
    {
        params[i].t = i + 1;
        usleep(200000); // имитация
        params[i].messages = allMessages[i];
        if (pthread_create(&threads[i], NULL, threadF, (void*)&params[i]) != 0)
        {
            cerr << "Ошибка: невозможно создать поток " << i + 1 << endl;
            return 1;
        }
    }
    // Ждем завершения каждого потока(валидация)
    for (int i = 0; i < 4; ++i)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            cerr << "Ошибка при присоединении потока " << i + 1 << endl;
            return 1;
        }
    }
    return 0;
}
