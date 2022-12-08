#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <sstream>
#include <queue>

using namespace std;

int main() {
    int count = 0, unique_len = 14;
    string line;
    ifstream input("../day_6/input.txt");
    list<char> margin, test_margin;

    if (input.is_open()) {
        while (getline(input, line)) {
            for (char c: line) {
                count++;

                if (margin.size() == unique_len)
                    margin.pop_back();
                margin.push_front(c);
                bool end = true;
                for (char cc: margin) {
                    for (char ccc: test_margin) {
                        if (cc == ccc)
                            end = false;
                    }
                    test_margin.push_front(cc);
                }
                test_margin.clear();
                if (end && margin.size() == unique_len) {
                    cout << "end ";
                    break;
                }
            }
            cout << count << endl;
            margin.clear();
            count = 0;

        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    return 0;
}
