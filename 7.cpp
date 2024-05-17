#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <filesystem>
#include <future>

using namespace std;
namespace fs = filesystem;
using namespace filesystem;

void copyFile(const string& src, const string& dst) {
    ifstream in(src, ios::binary);
    ofstream out(dst, ios::binary);
    out << in.rdbuf();
}

void copyDir(const string& src, const string& dst) {

    create_directory(dst);

    vector<path> files, directories;

    for (const auto& entry : directory_iterator(src)) {
        if (is_regular_file(entry)) {
            files.push_back(entry.path());
        }
        else if (is_directory(entry)) {
            directories.push_back(entry.path());
        }
    }

    vector<future<void>> fileFutures, dirFutures;

    // копирка файлов асинхронно
    for (const auto& file : files) {
        string newSrc = src + "\\" + file.filename().string();
        string newDst = dst + "\\" + file.filename().string();
        cout << "Copying file " << endl << "From: " << newSrc << endl << "To: " << newDst << endl;
        fileFutures.push_back(async(launch::async, copyFile, newSrc, newDst));
    }

    // копирка директории асинхронно
    for (const auto& directory : directories) {
        string newSrc = src + "\\" + directory.filename().string();
        string newDst = dst + "\\" + directory.filename().string();
        cout << "Copying directory " << endl << "From: " << newSrc << endl << "To: " << newDst << endl;
        dirFutures.push_back(async(launch::async, copyDir, newSrc, newDst));
    }

    for (auto& future : fileFutures) {
        future.get();
    }
    for (auto& future : dirFutures) {
        future.get();
    }
}

int main() {

    cout << "\n\n-------------COPYING STARTED------------- \n\n";
    string src = "C:\\Users\\Oleg\\source\\repos\\ConsoleApplication1";
    string dst = "C:\\Users\\Oleg\\source\\repos\\copyfor7lab";


    thread t(copyDir, src, dst);
    t.join();

    cout << "\n\n-------------COPYING ENDED-------------\n\n";

    return 0;
}