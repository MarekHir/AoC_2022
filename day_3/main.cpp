#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

int get_value(char c) {
    if (c > 'Z')
        return c - 'a' + 1;
    return c - 'A' + 27;
}

int main() {
    string line, first, second;
    int sum = 0, sum_badges = 0;
    size_t length = 0, pos;
    ifstream input("../day_3/input.txt");

    if (input.is_open()) {
        while (getline(input, line)) {
            length = line.length() / 2;
            for (int i = 0; i < length; i++) {
                if (line.find(line[i], length) != string::npos) {
                    if (line.find(line[i]) == i)
                        sum += get_value(line[i]);
                }
            }
            if (first.empty())
                first = line;
            else if (second.empty())
                second = line;
            else {
                for (char i: line) {
                    if (first.find(i) != string::npos && second.find(i) != string::npos) {
                        sum_badges += get_value(i);
                        break;
                    }
                }
                first.erase();
                second.erase();
            }
        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    cout << sum << endl;
    cout << sum_badges << endl;

    return 0;
}
