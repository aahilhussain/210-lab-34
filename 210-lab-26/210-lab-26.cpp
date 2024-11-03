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

template <typename Container, typename Func>
long long measure(const string& operation, Container& container, Func func) {
    auto start = high_resolution_clock::now();
    func(container);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    const int simulations = 15;
    long long results [4][3][simulations] = {0};

    for (int sim = 0; sim < simulations; ++sim){
        vector<string> vec;
        list<string> lst;
        set<string> st;

        // Reading data
        results[0][0][sim] = measure("Read    ", vec, [&](vector<string>& c){readData(c, lst, st, "codes.txt"); });

        // Sorting data
        results[1][0][sim] = measure("Sort     ", vec, [](vector<string>& c) { sort(c.begin(), c.end()); });
        results[1][1][sim] = measure("", lst, [](list<string>& c) { c.sort(); });
        results[1][2][sim] = -1;

        // Inserting data
        results[2][0][sim] = measure("Insert   ", vec, [](vector<string>& c) { c.insert(c.begin() + c.size() / 2, "TESTCODE"); });
        results[2][1][sim] = measure("", lst, [](list<string>& c) {
            auto it = c.begin();
            advance(it, c.size() / 2);
            c.insert(it, "TESTCODE");
        });
        results[2][2][sim] = measure("", st, [](set<string>& c) {c.insert("TESTCODE"); });

        // Deleting data
        results[3][0][sim] = measure("Delete   ", vec, [](vector<string>& c) { c.erase(c.begin() + c.size() / 2); });
        results[3][1][sim] = measure("", lst, [](list<string>& c) {
            auto it = c.begin();
            advance(it, c.size() / 2);
            c.erase(it);
        });
    results[3][2][sim] = measure("", st, [](set<string>& c) { c.erase("TESTCODE"); });

    long long averages[4][3] = {0};
    for (int op=0; op<4; ++op) {
        for (int container = 0;container < 3; ++container) {
            if (results[op][container][0] != -1) {
                long long sum = 0;
                for (int sim = 0; sim < simulations; ++sim) {
                    sum += results[op][container][sim];
                }
                averages[op][container] = sum/simulations;
            } else {
                averages[op][container] = 0;
            }
        }

    }

    cout << "Number of simulations: " << simulations << endl;
    cout << " Operation     Vector      List        Set" << endl;
    const char* operations[] = {"Read       ", "Sort        ", "Insert      ", "Delete"     };
    for (int op = 0; op < 4; ++op) {
        cout << operations[op];
        for(int container = 0; container < 3; ++container) {
            cout << averages[op][container] << "        ";
        }
        cout << endl;
    }


    return 0;
}