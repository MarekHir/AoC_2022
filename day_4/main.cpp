#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>

using namespace std;

int get_value(char c) {
    if (c > 'Z')
        return c - 'a' + 1;
    return c - 'A' + 27;
}

int main() {
    string line, pair, number;
    int ints[4], i = 0, sum_first = 0, sum_second = 0;
    ifstream input("../day_4/input.txt");
    stringstream ss, sss;

    if (input.is_open()) {
        while (getline(input, line)) {
            ss.str(line);
            while (getline(ss, pair, ',')) {
                sss.str(pair);
                while (getline(sss, number, '-')) {
                    ints[i] = stoi(number);
                    i++;
                }
                sss.clear();
            }
            ss.clear();
            if (ints[0] <= ints[2] && ints[1] >= ints[3] || ints[0] >= ints[2] && ints[1] <= ints[3]) {
                sum_first++;
            }
            if (ints[0] <= ints[3] && ints[1] >= ints[2]) {
                sum_second++;
            }
            i = 0;
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << sum_first << endl;
    cout << sum_second << endl;

    return 0;
}
