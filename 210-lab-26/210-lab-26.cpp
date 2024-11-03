#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

void readData(vector<string>& vec, list<string>& lst, set<string>& st, const string& filename) {
    ifstream file(filename);
    string line;
        while (getline(file, line)) {
        vec.push_back(line);
        lst.push_back(line);
        st.insert(line);
    }
}

template <typename Container>
void measure(const string& operation, Container& container, function<void(Container&)> func) {
    auto start = high_resolution_clock::now();
    func(container);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << operation << " " << duration << " ";
}

int main() {
    vector<string> vec;
    list<string> lst;
    set<string> st;

    // Reading data
    measure("Read     ", vec, [&](vector<string>& c) { readData(c, lst, st, "codes.txt"); });
    measure("", lst, [&](list<string>& c) { /* Already read in previous measure */ });
    measure("", st, [&](set<string>& c) { /* Already read in previous measure */ });
    cout << endl;

    // Sorting data
    measure("Sort     ", vec, [](vector<string>& c) { sort(c.begin(), c.end()); });
    measure("", lst, [](list<string>& c) { c.sort(); });
    cout << -1 << " "; // Set is already sorted
    cout << endl;

    // Inserting data
    measure("Insert   ", vec, [](vector<string>& c) { c.insert(c.begin() + c.size() / 2, "TESTCODE"); });
    measure("", lst, [](list<string>& c) {
        auto it = c.begin();
        advance(it, c.size() / 2);
        c.insert(it, "TESTCODE");
    });
    measure("", st, [](set<string>& c) { c.insert("TESTCODE"); });
    cout << endl;

    // Deleting data
    measure("Delete   ", vec, [](vector<string>& c) { c.erase(c.begin() + c.size() / 2); });
    measure("", lst, [](list<string>& c) {
        auto it = c.begin();
        advance(it, c.size() / 2);
        c.erase(it);
    });
    measure("", st, [](set<string>& c) { c.erase("TESTCODE"); });
    cout << endl;

    return 0;
}