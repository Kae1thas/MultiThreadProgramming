#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>

using namespace std;

mutex listMutex;

struct Node {
    string data;
    Node* next;

    Node(const string& str) : data(str), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void addNode(const string& str) {
        Node* newNode = new Node(str);
        lock_guard<mutex> lock(listMutex);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void printList() {
        Node* current = head;
        while (current) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

void sleepSortAndAdd(LinkedList& list, const string& str) {
    chrono::milliseconds sleepTime(str.length() * 200);
    this_thread::sleep_for(sleepTime);
    list.addNode(str);
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<thread> threads;
    LinkedList sortedList;

    vector<string> inputStrings = {
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

    sort(inputStrings.begin(), inputStrings.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
        });

    for (const string& str : inputStrings) {
        threads.push_back(thread(sleepSortAndAdd, ref(sortedList), str));
    }

    for (thread& t : threads) {
        t.join();
    }

    sortedList.printList();

    return 0;
}
