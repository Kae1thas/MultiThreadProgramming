#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

void sleepSortAndPrint(const  string& str) {
    // Вычисляем время сна, пропорциональное длине строки
    chrono::milliseconds sleepTime(str.length() * 200); // Множитель изменен для лучшей визуализации
    this_thread::sleep_for(sleepTime);

    // Выводим строку
    cout << str <<  endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector< thread> threads;
    vector< string> inputStrings = {
        "Кирилл",
        "Денис",
        "Яна",
        "Олег",
        "Елизавета",
        "Норик",
        "Алексей",
        "Ян",
        "Никита",
        "Ассизский"
    };

    // Сортируем строки по длине
     sort(inputStrings.begin(), inputStrings.end(), [](const  string& a, const  string& b) {
        return a.length() < b.length();
        });

    // Запускаем потоки для каждой строки
    for (const string& str : inputStrings) {
        threads.push_back( thread(sleepSortAndPrint, str));
    }

    // Дожидаемся завершения всех потоков
    for ( thread& t : threads) {
        t.join();
    }

    return 0;
}