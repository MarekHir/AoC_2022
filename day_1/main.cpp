#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int main() {
    string line;
    int current = 0, number;
    list<int> sum;
    ifstream input("../day_1/input.txt");

    if (input.is_open()) {
        while (getline(input, line)) {
            if (line.length() == 0) {
                sum.push_back(current);
                current = 0;
            } else {
                try {
                    number = stoi(line);
                    current += number;
                }
                catch (const std::invalid_argument &ia) {
                    cout << "Contains a non-numerical character";
                    return -1;
                }
            }

        }
        input.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }
    sum.sort();
    current = 0;

    cout << "Richest elf carries: " << sum.back() << endl;

    for (int i = 0; i < 3; i++) {
        current += sum.back();
        sum.pop_back();
    }
    cout << "Top 3 elfs have total of: " << current << " calories" << endl;
    return 0;
}
