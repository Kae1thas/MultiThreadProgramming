#include <iostream>
#include <cmath>
#include <vector>
#include <future>
#include <iomanip>
#include <csignal>
#include <atomic>

using namespace std;

atomic<bool> keepRunning(true);

void signalHandler(int signum)
{
    if (signum == SIGINT)
    {
        keepRunning = false;
        cout << " Received SIGINT. Exiting..." << endl;
    }
}

long double picalculation(int start, int end)
{
    long double sum = 0;
    for (int i = start; i <= end; i++) {
        sum += ((pow(-1, i)) / (2 * i + 1));
    }
    return sum;
}

void Calculation()
{
    cout << "Введите кол-во потоков : ";
    int threadcount;//число потоков
    cin >> threadcount;
    int iteration = 1000000000 / threadcount;
    long double pi = 0;
    // Создаем вектор для хранения фьючерсов
    vector<future<long double>> futures(threadcount); //асинхронное выполнение в будущем
    // Запускаем потоки и сохраняем их фьючерсы
    for (int i = 0; i < threadcount; i++) {
        int start = i * iteration;
        int end = (i == threadcount - 1) ? 1000000000 - 1 : start + iteration - 1;
        futures[i] = async(launch::async, picalculation, start, end);//он используется c future
    }

    // Ждем завершения всех потоков и накапливаем результаты
    for (auto& future : futures) {
        long double result = future.get();
        pi = pi + result;
    }
    pi = pi * 4;
    cout << setprecision(10) << pi << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Установка обработчика сигнала SIGINT
    signal(SIGINT, signalHandler);

    // Выполнение расчетов, пока программа не получит сигнал SIGINT
    while (keepRunning) {
        Calculation();
    }

    return 0;
}